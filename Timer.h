//
// Created by santi on 18/05/19.
//

#ifndef TP4_TIMER_H
#define TP4_TIMER_H


class Timer {
private:
    uint32_t startTicks;
    uint32_t pausedTicks;
    bool paused;
    bool started;
public:
    Timer();
    void start();
    void stop();
    void pause();
    void unPause();
    uint32_t getTicks();
    ~Timer() = default;
};


#endif //TP4_TIMER_H
