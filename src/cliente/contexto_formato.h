#ifndef CONTEXTOFORMATO_H
#define CONTEXTOFORMATO_H

#include <string>

class AVFormatContext;
class ContextoFormato {
private:
    AVFormatContext *pFormatCtx;

public:
    ContextoFormato();
    ~ContextoFormato();
};
#endif //CONTEXTOFORMATO_H
