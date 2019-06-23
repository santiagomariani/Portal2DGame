#include "formato_salida.h"
#include "contexto_formato.h"

#include <cstdio>
#include <string>
#include <stdexcept>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

FormatoSalida::FormatoSalida(const std::string& nombre_archivo,
                           int ancho,
                           int alto) :
                           ancho(ancho),
                           alto(alto) {
    this->frame = av_frame_alloc();
    if (!frame) {
        throw std::runtime_error("No se pudo reservar memoria para frame.");
    }
    this->pkt = av_packet_alloc();
    this->av_formato_salida = av_guess_format(NULL, nombre_archivo.c_str(),
            NULL);
    if (!this->av_formato_salida) {
        this->av_formato_salida = av_guess_format("mpeg", NULL, NULL);
    }
    if (!this->av_formato_salida) {
        throw std::runtime_error("No se encontró formato de salida.");
    }
    this->av_formato_salida->video_codec = AV_CODEC_ID_H264;
    AVCodec *codec = avcodec_find_encoder(
            this->av_formato_salida->video_codec);
    if (!codec) {
        throw std::runtime_error("No se pudo instanciar codec.");
    }
    iniciarContextoCodec(codec);
    this->archivo_salida = fopen(nombre_archivo.c_str(), "wb");
    iniciarMarco();
}

void FormatoSalida::codificar(AVCodecContext *enc_ctx,
        AVFrame *frame, AVPacket *pkt, FILE *outfile) {
    int ret = avcodec_send_frame(enc_ctx, frame);
    if (ret < 0) {
        throw std::runtime_error("Error al enviar frame.");
    }
    while (ret >= 0) {
        ret = avcodec_receive_packet(enc_ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            throw std::runtime_error("Error al codificar.");
        }
        fwrite(pkt->data, 1, pkt->size, outfile);
        av_packet_unref(pkt);
    }
}

void FormatoSalida::cerrar() {
    codificar(this->contexto_codec, NULL, this->pkt, this->archivo_salida);
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    fwrite(endcode, 1, sizeof(endcode), this->archivo_salida);
}

void FormatoSalida::iniciarMarco() {
    this->frame->format = this->contexto_codec->pix_fmt;
    this->frame->width  = this->contexto_codec->width;
    this->frame->height = this->contexto_codec->height;

    av_frame_get_buffer(this->frame, 0);
    this->current_pts = 0;
}

void FormatoSalida::escribirMarco(const char *data, SwsContext *ctx) {
    const u_int8_t* tmp = (const u_int8_t*) data;
    int aux = ancho * 3;
    sws_scale(ctx, &tmp, &aux, 0, frame->height, frame->data,
            frame->linesize);
    frame->pts = current_pts;
    current_pts++;
    codificar(this->contexto_codec, frame, pkt, this->archivo_salida);
}

void FormatoSalida::iniciarContextoCodec(AVCodec *codec) {
    this->contexto_codec = avcodec_alloc_context3(codec);
    this->contexto_codec->width = ancho;
    this->contexto_codec->height = alto;
    this->contexto_codec->time_base = {1,25};
    this->contexto_codec->framerate = {25,1};
    this->contexto_codec->pix_fmt = AV_PIX_FMT_YUV420P;
    this->contexto_codec->gop_size = 10;
    this->contexto_codec->max_b_frames = 2;
    if (codec->id == AV_CODEC_ID_H264) {
        this->contexto_codec->profile = FF_PROFILE_H264_BASELINE;
        av_opt_set(this->contexto_codec->priv_data, "preset", "slow", 0);
    }
    avcodec_open2(this->contexto_codec, codec, NULL);
}

FormatoSalida::~FormatoSalida() {
    avcodec_close(this->contexto_codec);
    avcodec_free_context(&this->contexto_codec);
    av_packet_free(&pkt);
    av_frame_free(&frame);
    fclose(this->archivo_salida);
}
