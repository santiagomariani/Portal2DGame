#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
    private:
        std::thread thread;
    public:
        Thread();
        // Se lanza el hilo y se ejecuta el metodo run.
        void start();
        void join();
        // Cada objeto activo que herede de Thread debera decidir como
        // terminar.
        virtual void terminar() = 0;
        // Cada objeto activo que herede de Thread debera hacer todo en el
        //  metodo run.
        virtual void run() = 0;
        virtual ~Thread();
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        Thread(Thread&& other);
        Thread& operator=(Thread&& other);
};


#endif //THREAD_H
