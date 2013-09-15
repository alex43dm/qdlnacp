#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include <upnp/ixml.h>

#include "DeviceList.h"

class Config
{
public:
    std::string port;
    std::string ip;
    std::string UpnpMaxContentLength;

    Config(std::string fName, DeviceList** dl, UpnpClient_Handle _cph);
    bool SaveFile(DeviceList* dl);
    bool CreateFile(std::string fName, DeviceList* dl);
    static std::string xmlGetChildElementValue( IXML_Element* parent, const  std::string tagName );
    static std::string xmlGetChildElement( IXML_Element* parent, const char* tagName );
    static std::string xmlGetChildElementAttr( IXML_Element* parent, const char* tagName, const char* attrName );
    std::string GetXml(DeviceList* dl);
    virtual ~Config();
protected:
private:
    IXML_Node* setVal(std::string name, std::string val, IXML_Document* doc);
    bool fileExists( std::string fileName);
    std::string fileName;
};

#endif // CONFIG_H
