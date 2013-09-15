#ifndef SERVICE_H
#define SERVICE_H

#include <string.h>
#include <string>

#include <upnp/ixml.h>

enum ServiceType
{
    AVTransport,
    ConnectionManager,
    ContentDirectory,
    MediaRenderer,
    MediaServer,
    RenderingControl,
    ScheduledRecording,
    X_MS_MediaReceiverRegistrar,
    Unknown
};

class Service
{
public:
	Upnp_SID Sid;
    std::string SCPDUrl;
    std::string serviceTypeUrn;
    std::string eventSubURL;
    std::string controlURL;
    ServiceType serviceType;

    Service();
    static const std::string toString( int enumVal );
    static bool isLeagal(std::string serviceTypeUrn);

	Service (Service* srv)
	{
		this->SCPDUrl = srv->SCPDUrl;
		this->serviceTypeUrn = srv->serviceTypeUrn;
		this->eventSubURL = srv->eventSubURL;
		this->controlURL = srv->controlURL;
		this->serviceType = srv->serviceType;
    }

	const Service operator=(Service& srv) const
	{
		srv.SCPDUrl = this->SCPDUrl;
		srv.serviceTypeUrn = this->serviceTypeUrn;
		srv.eventSubURL = this->eventSubURL;
		srv.controlURL = this->controlURL;
		srv.serviceType = this->serviceType;
        return srv;
    }

	bool operator==(const char* sid) const
	{
    	return memcmp( Sid, sid, 44) == 0 ? true : false;
	}

    ~Service();

protected:
private:
    std::string getUrl(const char* baseUrl, const char* urlR);
};

#endif // SERVICE_H
