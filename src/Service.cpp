#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <upnp/upnp.h>
#include <upnp/upnptools.h>

#include "include/Service.h"
#include "xmltools.h"

Service::Service()
{
	bzero(Sid,sizeof(Sid));
}

std::string Service::getUrl(const char* baseURL, const char* urlR)
{
    char* url;

     url = ( char* )malloc( strlen( baseURL ) + strlen( urlR ) );

     sprintf(url,"%s%s", baseURL, urlR);

/*
    if ( url )
    {
        char* s1 = strdup( baseURL );
        char* s2 = strdup( urlR );

        if ( UpnpResolveURL( s1, s2, url ) == UPNP_E_SUCCESS )
        {
            fprintf(stderr,"Error resolver url: %s %s\n", s1, s2);
        }
        free( s1 );
        free( s2 );
        //free( url );
    }
*/
    return url;
}

const std::string Service::toString( int enumVal )
{
    switch( enumVal )
    {
    case AVTransport:
        return "AVTransport";
    case ConnectionManager:
        return "ConnectionManager";
    case ContentDirectory:
        return "ContentDirectory" ;
    case MediaRenderer:
        return "MediaRenderer" ;
    case MediaServer:
        return "MediaServer" ;
    case RenderingControl:
        return "RenderingControl" ;
    case ScheduledRecording:
        return "ScheduledRecording" ;
    case X_MS_MediaReceiverRegistrar:
        return "X_MS_MediaReceiverRegistrar" ;
    default:
        return "Not recognized..";
    }
}

bool Service::isLeagal(std::string serviceTypeUrn)
{
    for( int i = AVTransport; i != X_MS_MediaReceiverRegistrar; ++i)
    {
        if(serviceTypeUrn.find(toString(i)) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}

Service::~Service()
{
	/*
    if(SCPDUrl)free((void*)SCPDUrl);
    if(serviceTypeUrn)free((void*)serviceTypeUrn);
    if(eventSubURL)free((void*)eventSubURL);
    if(controlURL)free((void*)controlURL);
		*/
}
