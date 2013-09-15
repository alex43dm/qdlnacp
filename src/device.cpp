/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gupnp
 * Copyright (C) Unknown 2013 <alex@gentooS>
	 *
 * gupnp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
	 *
 * gupnp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <sstream>

//#include <regex>

#include "device.h"
#include "xmltools.h"
#include "include/Uri.h"

Device::Device( )
{
}

Device::Device( const Upnp_Discovery* d )
{
    _DeviceId = d->DeviceId;
    _DeviceType = d->DeviceType;
    _ServiceType = d->ServiceType;
    _ServiceVer = d->ServiceVer;
    _Location = d->Location;
    _Os = d->Os;

    char buffer[INET6_ADDRSTRLEN];
    getnameinfo((struct sockaddr*)&d->DestAddr, sizeof(d->DestAddr), buffer, sizeof(buffer), 0, 0, NI_NUMERICHOST);
    _IP = buffer;
    _Time = time(NULL);

    Uri u = Uri::Parse(_Location);
    _baseURL = u.Protocol+"://"+u.Host+":"+u.Port;

   //fetchInfo();
   /*
    if( Service::isLeagal(_DeviceType.c_str()) )
    {
    }*/
}

void Device::fetchInfo(void)
{
    IXML_Document *doc = 0;
    int res;
    res = UpnpDownloadXmlDoc( _Location.c_str(), &doc );
    if ( res != UPNP_E_SUCCESS )
    {
        return;
    }
    // Try to extract baseURL
    /*
    IXML_NodeList* urlList = ixmlDocument_getElementsByTagName( doc, "baseURL" );
    if ( urlList )
    {
        if ( IXML_Node* urlNode = ixmlNodeList_item( urlList, 0 ) )
        {
            IXML_Node* textNode = ixmlNode_getFirstChild( urlNode );
            if ( textNode ) _baseURL = ixmlNode_getNodeValue( textNode );
        }
        ixmlNodeList_free( urlList );
    }
*/
    // Get devices
    IXML_NodeList* deviceList = ixmlDocument_getElementsByTagName( doc, "device" );
    if ( deviceList )
    {
        for ( unsigned int i = 0; i < ixmlNodeList_length( deviceList ); i++ )
        {
            IXML_Element* deviceElement = ( IXML_Element* )ixmlNodeList_item( deviceList, i );

            _deviceType = xml_getChildElementValue( deviceElement, "deviceType");
#ifdef DEBUG
            if ( _deviceType.empty() )
            {
                fprintf(stderr, "%s:%d: no deviceType!",__FILE__, __LINE__ );
            }
#endif

            _UDN = xml_getChildElementValue( deviceElement, "UDN" );
#ifdef DEBUG
            if ( _UDN.empty() )
            {
                fprintf( stderr, "%s:%d: no UDN!", __FILE__, __LINE__ );
            }
#endif

            _friendlyName = xml_getChildElementValue( deviceElement, "friendlyName" );
#ifdef DEBUG
            if ( _friendlyName.empty() )
            {
                fprintf( stderr, "%s:%d: no friendlyName!", __FILE__, __LINE__ );
            }
#endif
            IXML_NodeList* serviceList = ixmlElement_getElementsByTagName( deviceElement, "service" );
            if ( serviceList )
            {
                for ( unsigned int j = 0; j < ixmlNodeList_length( serviceList ); j++ )
                {
                    IXML_Element* serviceElement = ( IXML_Element* )ixmlNodeList_item( serviceList, j );
                    Service *s = new Service(serviceElement, _baseURL.c_str());
                    services.insert ( std::pair<ServiceType,Service*>(s->serviceType,s) );
                    //services.push_back( new Service(serviceElement) );
                }
            }
        }
        ixmlNodeList_free( deviceList );
    }
}

std::string Device::urlMarch(const std::string u)
{
    //int SCHEMA = 2, DOMAIN = 3, PORT = 5, PATH = 6, FILE = 8, QUERYSTRING = 9, HASH = 12
    /*
    regex e ("^((http[s]?):\/)?\/?([^:\/\s]+)(:([^\/]*))?((\/\w+)*\/)([\w\-\.]+[^#?\s]+)(\?([^#]*))?(#(.*))?$");
    smatch sm;

    :regex_match ( u.cbegin(), u.cend(), sm, e);
    return sm[2] + sm[3] + sm[5];
    */
    return u;//std::string("",0);
}

Device::~Device()
{
}

const char* Device::getId() const
{
    const char* s = _DeviceId.c_str();
    return s;
}

const char * Device::getfriendlyName(void)
{
    const char* s = _friendlyName.c_str();
    return s;
}

const char* Device::getServiceType(void)
{
    const char* s = _ServiceType.c_str();
    return s;
}

bool Device::compareId( const char* id )
{
    return ( strncmp( getId(), id, sizeof( Upnp_SID ) ) == 0 );
}

bool Device::compareDev( Device* d )
{
    return ( _DeviceId == d->getId() );
}

bool Device::comparefriendlyName( const char* name)
{
    return ( strncmp( getfriendlyName(), name,  strlen(name)) == 0 );
}

std::string Device::getDevInfo(void)
{

//return NULL;


    return "DeviceId:\t" + _DeviceId
    +"\nDeviceType:\t"+_DeviceType
    +"\nServiceType:\t"+_ServiceType
    +"\nServiceVer:\t"+_ServiceVer
    +"\nLocation:\t"+_Location
    +"\nOs:\t"+_Os
    +"\nIp:\t"+_IP
    //+"\nDate:\t"+ctime(&_Time)
    +"\nbaseURL:\t"+_baseURL
    +"\ndeviceType:\t"+_deviceType
    +"\nUDN:\t"+_UDN
    +"\nfriendlyName:\t"+_friendlyName+"\n";

    /*
    sprintf(buf,"DeviceId:\t%s\nDeviceType:\t%s\nServiceType:\t%s\nServiceVer:\t%s\nLocation:\t%s\nOs:\t%s\nIp:\t%s\nDate:\t%sbaseURL:\t%s\ndeviceType:\t%s\nUDN:\t%s\nfriendlyName:\t%s\n",
            _DeviceId.c_str(),
            _DeviceType.c_str(),
            _ServiceType.c_str(),
            _ServiceVer.c_str(),
            _Location.c_str(),
            _Os.c_str(),
            _IP.c_str(),
            ctime(&_Time),
            _baseURL.c_str(),
            _deviceType.c_str(),
            _UDN.c_str(),
            _friendlyName.c_str());
    return buf;
    */
}

bool Device::fetchContents(void)
{
    return true;
}

bool Device::subscribeToContentDirectory(void)
{
    return true;
}


IXML_Node* Device::setVal(std::string name, std::string val, IXML_Document* doc)
{
    IXML_Element *el = ixmlDocument_createElement(doc, name.c_str());
    IXML_Element *v = ixmlDocument_createElement(doc, val.c_str());
    (&v->n)->nodeType = eTEXT_NODE;
    ixmlNode_setNodeValue(&v->n,val.c_str());
    ixmlNode_appendChild( &el->n, &v->n );
    return &el->n;
}

IXML_Node* Device::Dev2Xml( IXML_Document* doc )
{

    IXML_Element *dev = ixmlDocument_createElement(doc, "dev");

    ixmlNode_appendChild( &dev->n, setVal("DeviceId",  _DeviceId, doc));
    ixmlNode_appendChild( &dev->n, setVal("DeviceType",  _DeviceType, doc));
    ixmlNode_appendChild( &dev->n, setVal("ServiceType",  _ServiceType, doc));
    ixmlNode_appendChild( &dev->n, setVal("ServiceVer",  _ServiceVer, doc));
    ixmlNode_appendChild( &dev->n, setVal("Location",  _Location, doc));
    ixmlNode_appendChild( &dev->n, setVal("Os",  _Os, doc));
    ixmlNode_appendChild( &dev->n, setVal("IP",  _IP, doc));
    ixmlNode_appendChild( &dev->n, setVal("baseURL",  _baseURL, doc));
    ixmlNode_appendChild( &dev->n, setVal("deviceType",  _deviceType, doc));
    ixmlNode_appendChild( &dev->n, setVal("UDN",  _UDN, doc));
    ixmlNode_appendChild( &dev->n, setVal("friendlyName",  _friendlyName, doc));


    IXML_Element *Services = ixmlDocument_createElement(doc, "Services");

    for ( auto it=services.begin(); it!=services.end(); ++it)
    {
        Service* s= (*it).second;
        IXML_Element *srv = ixmlDocument_createElement(doc, "Service");

        std::stringstream str;
        str << s->serviceType;
        ixmlNode_appendChild( &srv->n, setVal("serviceType",  str.str(), doc));
        ixmlNode_appendChild( &srv->n, setVal("SCPDUrl",  s->SCPDUrl, doc));
        ixmlNode_appendChild( &srv->n, setVal("serviceTypeUrn",  s->serviceTypeUrn, doc));
        ixmlNode_appendChild( &srv->n, setVal("eventSubURL",  s->eventSubURL, doc));
        ixmlNode_appendChild( &srv->n, setVal("controlURL",  s->controlURL, doc));

        ixmlNode_appendChild( &Services->n, &srv->n);
    }

    ixmlNode_appendChild( &dev->n, &Services->n);

    return &dev->n;
}
