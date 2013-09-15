#include "Thread.h"

Thread::Thread() :
    fExit(false)
{
    m_mtx = new pthread_mutex_t;
	pthread_mutex_init(m_mtx, NULL);
    m_cond = new pthread_cond_t;
	pthread_cond_init(m_cond, NULL);
}
//###########################################################################
Thread::~Thread()
{
    pthread_mutex_destroy(m_mtx);
    pthread_cond_destroy(m_cond);
    delete m_cond;
    delete m_mtx;
    pthread_exit(NULL);
}
//###########################################################################
bool Thread::start()
{
    pthread_create(&m_threadId, NULL, internalThreadFunc, this);
    return true;
}
//###########################################################################
void Thread::waitExit()
{
      (void) pthread_join(m_threadId, NULL);
}
//###########################################################################
void Thread::lock(bool getSignal)
{
    pthread_mutex_lock(m_mtx);
    if(getSignal)
        pthread_cond_wait(m_cond, m_mtx);
}
//###########################################################################
void Thread::unlock(bool sendSignal)
{
    if(sendSignal)
        pthread_cond_signal(m_cond);
    pthread_mutex_unlock(m_mtx);
}
