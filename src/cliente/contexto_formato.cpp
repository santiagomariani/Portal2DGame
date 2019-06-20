#include "contexto_formato.h"
#include <stdexcept>
#include <string>
extern "C" {
#include <libavformat/avformat.h>
}

ContextoFormato::ContextoFormato() {
    this->pFormatCtx = avformat_alloc_context();
}

ContextoFormato::~ContextoFormato() {
    avformat_free_context(this->pFormatCtx);
}

AVFormatContext * ContextoFormato::getContext() const {
    return this->pFormatCtx;
}
