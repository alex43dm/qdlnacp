#ifndef _UPnP_MediaServer_H_
#define _UPnP_MediaServer_H_

#include <fstream>

#include "UPnP.h"

class UPnP_MediaServer : public Device
{
public:
    std::string *id;
    Item *found;
    Container* pointer;

    UPnP_MediaServer();
    UPnP_MediaServer(Device *d);
    void startRoot();
    Container *nextFolder(const std::string &id);
    bool isRoot(){return pointer == root;};

    Item* FindById(std::string Id);
    Item* FindById(Container *c, std::string Id);
    bool Search(std::string str);
    void GetSearchCapabilities();
    void GetSystemUpdateID();
    void GetSortCapabilities();
    void upnpEventReceived( Upnp_Event* );
    Container *getMediaByID(std::string id);
    bool subscribe();
    bool unSubscribe();
    ~UPnP_MediaServer();
protected:
private:
    Container* root;

    bool getItem( Container* parent);
    void buildPlaylist( Container* parent );
    bool getMedia(Container* parent);
    IXML_Document* parseBrowseResult( IXML_Document* doc );
};

#endif // _UPnP_MediaServer_H_
