#ifndef OUTPUTFORMAT_H
#define OUTPUTFORMAT_H

#include <string>

class AVCodec;
class AVFrame;
class AVPacket;
class AVOutputFormat;
class AVStream;
class AVCodecContext;
class ContextoFormato;
class SwsContext;

class FormatoSalida {
private:
    // Inicializa frame.
    void iniciarMarco();
    // Inicializa contexto de codec.
    void iniciarContextoCodec(AVCodec *codec);
    void codificar(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt,
                   FILE *outfile);
    AVOutputFormat* av_formato_salida;
    AVStream* video_avstream;
    AVCodecContext* contexto_codec;
    int current_pts;
    FILE* archivo_salida;
    AVFrame* frame;
    AVPacket* pkt;
    int ancho;
    int alto;

public:
    FormatoSalida(const std::string &nombre_archivo,
            int ancho,
            int alto);
    // Escribe un frame a disco. Utiliza 'swsContext' para convertir
    // de RGB24 a YUV420p.
    void escribirMarco(const char *data, SwsContext *ctx);
    // Cierra el stream de video.
    void cerrar();
    ~FormatoSalida();
};

#endif //OUTPUTFORMAT_H
