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
/**
 * Clase que encapsula lógica la salida de video
 * Se recomienda modularizar aun más esta clase, reforzando RAII
 */
class FormatoSalida {
public:
    FormatoSalida() = default;
    FormatoSalida(ContextoFormato& context, const std::string& filename);
    ~FormatoSalida();
    // Escribe un frame a disco. Utiliza `swsContext` para convertir
    // de RGB24 a YUV420p
    void writeFrame(const char* data, SwsContext* swsContext);
    // Cierra el stream de video
    void close();

private:
    // Inicializa frame
    void initFrame();
    // Inicializa contexto de codec
    void codecContextInit(AVCodec* codec);
    ContextoFormato* context;
    AVOutputFormat* avOutputFormat;
    AVStream* video_avstream;
    AVCodecContext* codecContext;
    int currentPts;
    FILE* outputFile;
    AVFrame* frame;
    AVPacket* pkt;
};
#endif
