#ifndef _UPnP_MediaRenderer_H_
#define _UPnP_MediaRenderer_H_

#include <vector>

#include "UPnP.h"
#include "Timer.h"


/*
"STOPPED"
"PLAYING"
"TRANSITIONING"
"PAUSED_PLAYBACK"
"PAUSED_RECORDING"
"RECORDING"
"NO_MEDIA_PRESENT"
*/

class UPnP_MediaRenderer : public Device
{
public:
    bool isSet;
    unsigned int Volume;
    unsigned int Position;
    unsigned int TrackLengthSec;
    std::string TransportState;
    std::string NumberOfTracks;
    std::string CurrentTrack;
    std::string CurrentTrackDuration;
    std::string CurrentMediaDuration;

    UPnP_MediaRenderer();
    UPnP_MediaRenderer(Device *d);
    bool subscribe();
    bool unSubscribe();
    bool InitInfo();
    void SetUrl();
    bool SetTrack(const std::string &id);
    //std::string GetCurTrackName() const;
    inline bool isPaused(){ return TransportState == "PAUSED_PLAYBACK";}
    inline bool isPlayed(){ return TransportState == "PLAYING";}
    inline bool isStoped(){ return TransportState == "STOPPED";}
    bool Play();
    bool Play(const std::string &id);
    bool Pause();
    bool Stop();
    bool Next();
    bool Prev();
    bool Mute();
    bool setVol(const std::string &);
    unsigned int getVol();
    unsigned int getPositionInfo();
    bool Seek(int);

    virtual ~UPnP_MediaRenderer();
    void upnpEventReceived( Upnp_Event* );
    void PlayListAdd(Item* i);
    void PlayListClear();
    void PlayList2M3U(std::string fName);

    static void onEvent(){};
protected:
private:
    std::vector<Item*> playlist;
    unsigned int currentPlay;
    const char* InstanceID;

    std::string xmlGetChildElementAttrValue( IXML_Element* parent,  const std::string tagName, const std::string attrName );
    void getUrls(void);
    unsigned int timeToSeconds(const std::string &str);
};

#endif // _UPnP_MediaRenderer_H_
