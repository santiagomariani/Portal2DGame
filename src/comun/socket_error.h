
#ifndef SOCKET_ERROR_H
#define SOCKET_ERROR_H

#include <stdexcept>

class SocketError : public std::runtime_error {
public:
    explicit SocketError(const char* error) : runtime_error(error) {}
};

#endif //SOCKET_ERROR_H
