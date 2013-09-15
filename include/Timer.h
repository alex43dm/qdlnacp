#ifndef TIMER_H
#define TIMER_H

#include "Thread.h"

class Timer : public Thread
{
    public:
        Timer(int val = 0);
        virtual ~Timer();
        void setPeriod(int val){sec = val;};
        virtual void tick(){};
        virtual void finish(){};
    protected:
        virtual void *threadLoop();
    private:
        int sec;
};

#endif // TIMER_H
