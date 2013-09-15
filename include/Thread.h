#ifndef THREAD_H
#define THREAD_H

extern "C"{
    #include <pthread.h>
}

static pthread_mutex_t g_mtx01;

class Thread
{
    public:
        Thread();
        virtual ~Thread();

        bool start();
        bool stop(bool toUnlock=false){ fExit = true; if(toUnlock) pthread_cond_signal(m_cond); return true;};
        void waitExit();
        void lock(bool getSignal = false);
        void unlock(bool sendSignal = false);
        static void glock(){pthread_mutex_lock(&g_mtx01);};
        static void gunlock(){pthread_mutex_unlock(&g_mtx01);};
    protected:
        bool             fExit;
        virtual void *threadLoop() = 0;
        pthread_t        m_threadId;

    private:
        pthread_mutex_t *m_mtx;
        pthread_cond_t  *m_cond;

        static void * internalThreadFunc(void *th) {((Thread *)th)->threadLoop(); return NULL;}
};

#endif // THREAD_H
