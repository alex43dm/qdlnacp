#ifndef UPNP_CP_H
#define UPNP_CP_H

#include "UPnP.h"
#include "Thread.h"
#include "UPnP_MediaRenderer.h"
#include "UPnP_MediaServer.h"
#include "Timer.h"

#define TINEOUT 3

class UPnP_CP : public UPnP, public Thread
{
    public:
        int timeOutScan;
        int syncTrackTimeSec;

        UPnP_CP();
        virtual ~UPnP_CP();
        //init
        bool init(){return UPnP::init();};
        //scan(can lock)
        bool startScan(int);
        //set render & server
        bool SetRenderer(const std::string &id);
        bool SetServer(const std::string &id);
        inline bool isRenderSet(){return m_render != NULL;}
        inline bool isServerSet(){return m_server != NULL;}
        //content
        Container* setRoot(){ m_server->startRoot(); return m_server->pointer;};
        Container* next(const std::string &itm);
        bool isRoot(){return m_server->isRoot();};
        bool PlayListAdd(const std::string &id);
        //media
        inline bool isPlay(){ return m_render? m_render->isPlayed() : false;}
        inline std::string TracName()const {return m_render ? m_render->CurrentTrack : "";}
        inline int TrackDuration(){return m_render ? m_render->TrackLengthSec : 0;}
        inline int TracPosition(){return m_render ? m_position : 0;}
        bool SetTrack(const std::string &id);
        bool Play();
        bool PlayFromList(const std::string &id);
        bool Stop();
        bool Pause();
        bool Next();
        bool Prev();
        int VolGet(){return m_render ? m_render->Volume : 0;};
        bool VolSet(int);
        bool Seek(int val);
        //scan loop
        void *threadLoop();
    protected:
        virtual bool onScanStart(){return true;};
        virtual bool onScanStop(){return true;};
        virtual bool onDeviceAdd(){return true;};
        virtual void onDeviceRemove(){};

        virtual void timerTick(){};
        virtual void timerFinish(){};

        static void onRenderEvent(){};
    private:
        UPnP_MediaRenderer *m_render;
        UPnP_MediaServer *m_server;
        bool m_startTimer;
        unsigned int m_position;

        void Sleep(int timeOut);
};

#endif // UPNP_CP_H
