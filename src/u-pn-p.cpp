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
//#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include <sstream>

#include "u-pn-p.h"
#include "device-list.h"
#include "xmltools.h"

UPnP::UPnP()
{
    initialize();
}

UPnP::~UPnP()
{
    UpnpFinish();
}

void UPnP::initialize()
{
    int res;
    res = UpnpInit( 0, 0 );
    if( res != UPNP_E_SUCCESS )
    {
        std::cerr<< "UpnpInit error: " << UpnpGetErrorMessage( res )  <<std::endl;
        return;
    }

    deviceList = new DeviceList();
    cfg = new Config("config.xml", &deviceList);

    res = UpnpRegisterClient(Callback, this, &CtrlPnt);
    if( res != UPNP_E_SUCCESS )
    {
        std::cerr<< "UpnpRegisterClient error: " << UpnpGetErrorMessage( res )  <<std::endl;
    }
    res = UpnpSetMaxContentLength( 262144 );
    if( res != UPNP_E_SUCCESS )
    {
        std::cerr<< "UpnpSetMaxContentLength error: " << UpnpGetErrorMessage( res )  <<std::endl;
    }
}
bool UPnP::SaveConfig()
{
    return cfg->SaveFile(deviceList);
}

int UPnP::Callback( Upnp_EventType eventType, void* event, void* pCookie )
{
    UPnP *c = (UPnP *)pCookie;

    switch( eventType )
    {
    case UPNP_DISCOVERY_ADVERTISEMENT_ALIVE:
    case UPNP_DISCOVERY_SEARCH_RESULT:
    {
        Upnp_Discovery* e = (struct Upnp_Discovery*)event;
        /*
        fprintf( stderr,"get: UPNP_DISCOVERY_SEARCH_RESULT\nid:\t%s\nType:\t%s\nServiceType:\t%s\nVer:\t%s\nLocation:\t%s\n\n"
                 ,e->DeviceId, e->DeviceType, e->ServiceType,
                 e->ServiceVer, e->Location);
*/
        Device* d = new Device(e);
        //std::cerr<<"create device"<<std::endl;
        c->deviceList->addDevice ( d, true );



//        fprintf( stderr,"%s", d->getInfo ());
    }
    break;

    case UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE:
    {
        fprintf( stderr,"get: UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE\n");
        //struct Upnp_Discovery* discovery = ( struct Upnp_Discovery* )event;
        //dl->deviceList->removeDevice( discovery->DeviceId );
    }
    break;

    case UPNP_EVENT_RECEIVED:
    {
        fprintf( stderr,"get: UPNP_EVENT_RECEIVED\n");
        //Upnp_Event* e = ( Upnp_Event* )event;
        //Device* device = dl->deviceList->getDeviceByID( e->Sid );
        //if ( device ) device->fetchContents();
    }
    break;

    case UPNP_EVENT_AUTORENEWAL_FAILED:
    case UPNP_EVENT_SUBSCRIPTION_EXPIRED:
    {
        fprintf( stderr,"get: UPNP_EVENT_SUBSCRIPTION_EXPIRED\n");
        //Upnp_Event_Subscribe* e = ( Upnp_Event_Subscribe* )event;
        //Device* device = dl->deviceList->getDeviceByID( e->Sid );
        //if ( device ) device->subscribeToContentDirectory();
    }
    break;

    default:
        fprintf( stderr,"%s:%d: DEBUG: UNHANDLED EVENT ( TYPE=%d )\n", __FILE__, __LINE__, eventType );
        break;
    }

    return UPNP_E_SUCCESS;
}


const char* ALL_DEVICE_TYPES = "upnp:rootdevice";
const char* MEDIASERVERS = "urn:schemas-upnp-org:device:MediaServer:1";
const char* MEDIARENDERERS = "urn:schemas-upnp-org:device:MediaRenderer:1";
//const char* CONTENT_DIRECTORY_SERVICE_TYPE = "urn:schemas-upnp-org:service:ContentDirectory:1";

DeviceList* UPnP::NetScan(int waitSec)
{
    int res;

    res = UpnpSearchAsync( CtrlPnt, waitSec, MEDIASERVERS, this );
    if( res != UPNP_E_SUCCESS )
    {
        std::cerr<<"UpnpSearchAsync error: "<<UpnpGetErrorMessage( res )<<std::endl;
    }

    res = UpnpSearchAsync( CtrlPnt, waitSec, MEDIARENDERERS, this );
    if( res != UPNP_E_SUCCESS )
    {
        std::cerr<<"UpnpSearchAsync error: "<<UpnpGetErrorMessage( res )<<std::endl;
    }
    return deviceList;

/*
    res = UpnpSearchAsync( CtrlPnt, waitSec, ALL_DEVICE_TYPES, this );
    if( res != UPNP_E_SUCCESS )
    {
        std::cerr<<"UpnpSearchAsync error: "<<UpnpGetErrorMessage( res )<<std::endl;
    }*/
    return deviceList;

}
/*
int UPnP::Send( const char* id, const char* url, IXML_Document* Action, IXML_Document** Resp)
{
    Device* d = cookie->deviceList->getDeviceByID(id);
    return UpnpSendAction( cookie.clientHandle, url, d->getServiceType(), d->getId(), Action, Resp );
}

int UPnP::GetVar( const char* url, const char* VarName, DOMString* StVarVal)
{
    Device* d = cookie->deviceList->getDeviceByID(id);
    return UpnpGetServiceVarStatus( cookie.clientHandle,  url, VarName, StVarVal );
}
*/

DOMString UPnP::getSrvVar( std::string srvId, ServiceType stype, std::string varName)
{
    Device* d = deviceList->getDevice( srvId );
    if( d == 0 )
    {
        fprintf(stderr, "device: %s not found\n", srvId.c_str());
        return 0;
    }

    Service *s = d->services[stype];
    if( s == 0 )
    {
        fprintf(stderr, "service: %d not found\n", stype);
        return 0;
    }

    int ret;
    DOMString response;
    ret = UpnpGetServiceVarStatus( CtrlPnt,   s->controlURL.c_str(),   varName.c_str(),  &response );
    if (ret != UPNP_E_SUCCESS)
    {
        std::cerr<<"Unable get var: "<< varName<<" return: "<< ret<<" ("<<UpnpGetErrorMessage(ret)<<")\nsrv id: "<<srvId<<"\ncontrol url: "<<s->controlURL<<std::endl;
        return NULL;
    }
    return response;
}

IXML_Document *UPnP::SendAction( std::string id, ServiceType st, const char* _actionName, int count, ...)
{
    // Send an action to the control url specified.
    //Returns the response as a IXML document or NULL for failure
    int ret, n;
    va_list va;
    IXML_Document *action = NULL, *response = NULL;
    char* actionName = strdup( _actionName );

    Device* d = deviceList->getDeviceByID(id.c_str());
    if( d == 0 )
    {
        std::cerr<<"\ndevice: "<<id<<" not found\n";
        return 0;
    }

    Service *s = d->services[st];
    if( s == 0 )
    {
        fprintf(stderr, "service: %d not found\n", st);
        return 0;
    }

    std::cerr << "send to: "<<id<<"\naction: "<<actionName<<"\n";

    // Create action
    action = UpnpMakeAction(actionName, s->serviceTypeUrn.c_str(), 0, NULL);

    // Add argument to action
    va_start(va, count);
    for (n = 0; n < count; n++)
    {
        char *arg_name, *arg_val;
        arg_name = va_arg(va, char*);
        arg_val  = va_arg(va, char*);
        std::cerr << arg_name<< " : " << arg_val<<"\n";
        ret = UpnpAddToAction(&action, actionName, s->serviceTypeUrn.c_str(), arg_name, arg_val);
        if ( ret != UPNP_E_SUCCESS )
        {
            fprintf(stderr,"Unable add to action: %s (%s)\n", arg_name, arg_val);
        }
    }
    va_end(va);

    // Send action
    ret = UpnpSendAction(CtrlPnt, s->controlURL.c_str(), s->serviceTypeUrn.c_str(), 0, action, &response);

    // Free action
    if (action)   ixmlDocument_free(action);

    if (ret != UPNP_E_SUCCESS)
    {
        std::cerr << " error";
        fprintf(stderr,"Unable to send action: %d (%s)\nAction: %s\nurl: %s\nDevUDN: %s\n", ret, UpnpGetErrorMessage(ret), actionName, s->controlURL.c_str(), s->serviceTypeUrn.c_str());
        if (response) ixmlDocument_free(response);
        return NULL;
    }
    else
    {
        std::cerr << " ok";
    }
    std::cerr << std::endl;
    return response;
}

bool UPnP::getMedia(Container* parent)
{
    IXML_Document * getInfo =
        SendAction("uuid:69294598-58cd-4167-8c35-0944227dc806",
                   ContentDirectory, "Browse", 6, "ObjectID", parent->getObjectID(),
                   "BrowseFlag", "BrowseDirectChildren",
                   "Filter", "*.avi",
                   "StartingIndex", "0",
                   "RequestedCount", "0",
                   "SortCriteria", "");

    IXML_Document* result = parseBrowseResult( getInfo );
    if (getInfo)   ixmlDocument_free(getInfo);

    IXML_NodeList* containerNodeList = ixmlDocument_getElementsByTagName( result, "container" );
    if ( containerNodeList )
    {
        for ( unsigned int i = 0; i < ixmlNodeList_length( containerNodeList ); i++ )
        {
            IXML_Element* containerElement = ( IXML_Element* )ixmlNodeList_item( containerNodeList, i );

            const char* objectID = ixmlElement_getAttribute( containerElement, "id" );
            if ( !objectID ) continue;

            const char* childCountStr = ixmlElement_getAttribute( containerElement, "childCount" );
            if ( !childCountStr ) continue;
            int childCount = atoi( childCountStr );

            const char* title = xml_getChildElementValue( containerElement, "dc:title" );
            if ( !title ) continue;

            const char* resource = xml_getChildElementValue( containerElement, "res" );

            if ( resource && childCount < 1 )
            {
                Item* item = new Item( parent, objectID, title, resource );
                parent->addItem( item );
            }
            else
            {
                Container* container = new Container( parent, objectID, title );
                //fprintf(stderr,"objectID: %s title: %s\n", objectID, title);
                parent->addContainer( container );
                //recursion
                if ( childCount > 0 ) getMedia( container );
            }
        }
        ixmlNodeList_free( containerNodeList );
    }


    IXML_NodeList* itemNodeList = ixmlDocument_getElementsByTagName( result, "item" );
    if ( itemNodeList )
    {
        for ( unsigned int i = 0; i < ixmlNodeList_length( itemNodeList ); i++ )
        {
            IXML_Element* itemElement = ( IXML_Element* )ixmlNodeList_item( itemNodeList, i );

            const char* objectID = ixmlElement_getAttribute( itemElement, "id" );
            if ( !objectID ) continue;

            const char* title = xml_getChildElementValue( itemElement, "dc:title" );
            if ( !title ) continue;

            const char* resource = xml_getChildElementValue( itemElement, "res" );
            if ( !resource ) continue;

            //fprintf(stderr,"objectID: %s title: %s resource: %s\n", objectID, title, resource);

            Item* item = new Item( parent, objectID, title, resource );
            parent->addItem( item );
        }

        ixmlNodeList_free( itemNodeList );
    }

    ixmlDocument_free( result );

    return true;
}

void UPnP::buildPlaylist( Container* parent )
{
    for ( unsigned int i = 0; i < parent->getNumContainers(); i++ )
    {
        Container* container = parent->getContainer( i );
        //recursion
        buildPlaylist( container );
    }
    /*
        for ( unsigned int i = 0; i < parent->getNumItems(); i++ )
        {
            Item* item = parent->getItem( i );
        }*/
}

bool UPnP::getItem( Container* parent)
{
    for ( unsigned int i = 0; i < parent->getNumContainers(); i++ )
    {
        Container* container = parent->getContainer( i );
        //recursion
        if( getItem( container) )
        {
            return true;
        }
    }

    for ( unsigned int i = 0; i < parent->getNumItems(); i++ )
    {
        Item* item = parent->getItem( i );
        if( item->compareId(id))
        {
            found = item;
            return true;
        }
    }
    return false;
}

void UPnP::SetAvi(void)
{
    IXML_Document * getInfo;
    std::string xbmcId = "uuid:d0af2356-627b-5afa-29cc-5ad192c41abe";

    Device* d = deviceList->getDeviceByID(xbmcId.c_str());
    if( d == 0 )
    {
        std::cerr<<"\ndevice: "<<xbmcId<<" not found\n";
        return;
    }

    Service *s = d->services[AVTransport];
    if( s == 0 )
    {
        fprintf(stderr, "service: %d not found\n", AVTransport);
        return;
    }
    Upnp_SID SubsId;
    int timeOut = 20;
    int ret = UpnpSubscribe( CtrlPnt,  s->eventSubURL.c_str(),  &timeOut,   SubsId);
    if (ret != UPNP_E_SUCCESS)
    {
        std::cerr<<"\nerror UpnpSubscribe\n"<<s->eventSubURL<<std::endl;
    }

    //std::string xbmcId = "uuid:69294598-58cd-4167-8c35-0944227dc806";
    /*
    Container* root = new Container( 0, "0", "MediaTomb" );
    getMedia(root);

    id =  4752;
    getItem(root);
    if( found == NULL )
    {
        std::cerr<< "Not found id: " << id <<std::endl;
        return;
    }

    //DOMString xml = getSrvVar( aviName, AVTransport, "AVTransportURIMetaData");
    Container* p = found->getParent();
std::ostringstream meta;
meta <<"<DIDL-Lite xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\">\
<item id=\""<<found->getResource()<<"\" \
parentID=\""<<p->getObjectID()<<"\" \
restricted=\"0\">\
<dc:title>"<<found->getTitle()<<"</dc:title>\
<dc:date></dc:date>\
<upnp:class>object.item.imageItem</upnp:class>\
<dc:creator></dc:creator>\
<upnp:genre></upnp:genre>\
<upnp:artist></upnp:artist>\
<upnp:album></upnp:album>\
<res protocolInfo=\"file-get:*:*:*:DLNA.ORG_OP=01;DLNA.ORG_CI=0;DLNA.ORG_FLAGS=00000000001000000000000000000000\" protection=\"\" tokenType=\"0\" bitrate=\"0\" duration=\"\" \
size=\"126650368\" colorDepth=\"0\" ifoFileURI=\"\" resolution=\"\">"<<found->getResource()<<"</res>\
</item>\
</DIDL-Lite>";

std::cerr << meta.str();

std::cerr << "send SetAVTransportURI: ";
    getInfo =
        SendAction(xbmcId.c_str(), AVTransport, "SetAVTransportURI", 3,
                   "InstanceID", "0",
                   "CurrentURI", (const char *)found->getResource(),
                   "CurrentURIMetaData", meta.str().c_str());

                   if( getInfo == NULL)
                   {
                       std::cerr<<"error";
                   }
                   else
                   {
                       std::cerr << "ok";
                   }
*/
std::cerr<<std::endl;
/*
    std::cerr << "send SetPlayMode: ";
    getInfo = SendAction(xbmcId.c_str(), AVTransport, "SetPlayMode",  2, "InstanceID", "0", "NewPlayMode", "NORMAL");

                   ifl( getInfo == NULL)
                   {
                       std::cerr<<"error";
                   }
                   else
                   {
                       std::cerr << "ok";
                   }
std::cerr<<std::endl;*/


    std::cerr << "send GetCurrentTransportActions: ";
    getInfo = SendAction(xbmcId.c_str(), AVTransport, "GetCurrentTransportActions",  1, "InstanceID", "0");

                   if( getInfo == NULL)
                   {
                       std::cerr<<"error";
                   }
                   else
                   {
                       std::cerr << "ok";
                   }

    std::cerr << "send Play: ";
    getInfo = SendAction(xbmcId.c_str(), AVTransport, "Play",  2, "InstanceID", "0", "Speed", "1");

                   if( getInfo == NULL)
                   {
                       std::cerr<<"error";
                   }
                   else
                   {
                       std::cerr << "ok";
                   }
                   std::cerr<<std::endl;

}
