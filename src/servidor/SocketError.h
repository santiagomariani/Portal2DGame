//
// Created by santi on 01/05/19.
//

#ifndef SOCKETERROR_H
#define SOCKETERROR_H

#include <stdexcept>

class SocketError : public std::runtime_error {
public:
    explicit SocketError(const char* error) : runtime_error(error) {}
};

#endif //SOCKETERROR_H
