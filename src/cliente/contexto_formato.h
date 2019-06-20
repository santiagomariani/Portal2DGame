#ifndef FORMATCONTEXT_H
#define FORMATCONTEXT_H
#include <string>

class AVFormatContext;
class ContextoFormato {
public:
    ContextoFormato();
    ~ContextoFormato();
    AVFormatContext* getContext() const;
private:
    AVFormatContext *pFormatCtx;
};
#endif
