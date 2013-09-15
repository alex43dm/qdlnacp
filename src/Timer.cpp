#include <unistd.h>

#include "Timer.h"

Timer::Timer(int s) :
    Thread(),
    sec(s)
{
    //ctor
}

Timer::~Timer()
{
    //dtor
}

void *Timer::threadLoop()
{
    int i = 0;
    while( i < sec)
    {
        sleep(1);
        tick();
        i++;
    }
    finish();
    return NULL;
}
