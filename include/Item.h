#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

class Container;

class Item
{
public:
    std::string upnpClass;
    std::string artist;
    std::string album;
    std::string originalTrackNumber;
    std::string date;
    std::string description;
    std::string size;
    std::string protocolInfo;
    std::string duration;
    std::string bitrate;
    std::string sampleFrequency;
    std::string nrAudioChannels;
    std::string res;
    std::string all;

    Item( Container* parent, const char* objectID, const char* title, const char* resource );
    Item( const Item&);
    const char* getObjectID() const;
    const char* getTitle() const;
    const std::string getStr() const;
    const char* getResource() const;
    Container* getParent() const;
    int duration2sec(void);
    std::string playListPath(void);

private:
    Container* _parent;
    std::string _objectID;
    std::string _title;
    std::string _resource;
};

#endif // ITEM_H
