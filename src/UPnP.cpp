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
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>

#include "UPnP.h"
#include "Log.h"
#include "UPnP_MediaRenderer.h"
#include "UPnP_MediaServer.h"
#include "xmltools.h"

UPnP::UPnP() :
	m_removedDev(false),
	isInited(false)
{
//    init();
}

UPnP::~UPnP()
{
	UpnpFinish();
}

bool UPnP::init()
{
	int res;

	if((res = UpnpInit(0, 0)) != UPNP_E_SUCCESS)
	{
		Log::err("UpnpInit error: %s",UpnpGetErrorMessage(res));
		return false;
	}

	if((res = UpnpRegisterClient(Callback, this, &CtrlPnt)) != UPNP_E_SUCCESS)
	{
		Log::err("UpnpRegisterClient error: %s",UpnpGetErrorMessage(res));
		return false;
	}

	deviceList = new DeviceList();
	cfg = new Config("config.xml", &deviceList, CtrlPnt);

	if((res = UpnpSetMaxContentLength(atoi(cfg->UpnpMaxContentLength.c_str()))) != UPNP_E_SUCCESS)
	{
		Log::err("UpnpSetMaxContentLength error: %s",UpnpGetErrorMessage(res));
		return false;
	}

	isInited = true;
	return isInited;
}

bool UPnP::SaveConfig()
{
	return cfg->SaveFile(deviceList);
}

int UPnP::Callback(Upnp_EventType eventType, void* event, void* pCookie)
{
	UPnP *c = (UPnP *)pCookie;

	switch(eventType)
	{
	case UPNP_DISCOVERY_ADVERTISEMENT_ALIVE:
	{
		Upnp_Discovery* e = (struct Upnp_Discovery*)event;
		Log::debug("UPNP_DISCOVERY_ADVERTISEMENT_ALIVE: Id: %s Type: %s",e->DeviceId, e->DeviceType);
	}

	case UPNP_DISCOVERY_SEARCH_RESULT:
	{

		Upnp_Discovery* e = (struct Upnp_Discovery*)event;
		//Log::debug("UPNP_DISCOVERY_SEARCH_RESULT: type: (%s)",e->DeviceId);

//	    c->ilock();
	    bool ret = c->deviceList->isDeviceByID(e->DeviceId);
		if(!ret)
		{
		    Device *d = new Device(e);
			d->ctrlPnt = c->CtrlPnt;

			switch(d->getType())
			{
                case AVTransport:
                    c->deviceList->addDevice(new UPnP_MediaRenderer(d), false);
                    delete d;
                    break;

                case ContentDirectory:
                    c->deviceList->addDevice(new UPnP_MediaServer(d), false);
                    delete d;
                    break;

                default:
                    //c->deviceList->addDevice(d, false);
                    //or
                    delete d;
                    break;
			}
            Log::debug("UPNP_DISCOVERY_SEARCH_RESULT: add dev type: %s", e->DeviceType);
			c->m_addedDev = true;
		}
//		c->iunlock();
	}
	break;

	case UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE:
	{
		Upnp_Discovery* e = (struct Upnp_Discovery*)event;
		Log::debug("UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE: Id: %s Type: %s ServiceType: %s Ver:%s Location: %s",
		           e->DeviceId, e->DeviceType, e->ServiceType, e->ServiceVer, e->Location);

		if(!c->deviceList->isDeviceByID(e->DeviceId))
		{
			c->deviceList->removeDevice(e->DeviceId);
			c->m_removedDev = true;
		}
	}
	break;

	case UPNP_EVENT_RECEIVED:
	{
		Upnp_Event* e = (Upnp_Event*)event;
		//Log::debug("UPNP_EVENT_RECEIVED: Sid: %s EventKey: %s ChangedVariables: %s", e->Sid, e->EventKey ,ixmlDocumenttoString(e->ChangedVariables));
		Log::debug("UPNP_EVENT_RECEIVED: Sid: %s EventKey: %d", e->Sid, e->EventKey);

		if(c->deviceList)
		{
			Device* device = c->deviceList->getDeviceBySid(e->Sid);

			if(device)
			{
				device->upnpEventReceived(e);
			}
		}
	}
	break;

	case UPNP_EVENT_AUTORENEWAL_FAILED:
	case UPNP_EVENT_SUBSCRIPTION_EXPIRED:
	{
		Upnp_Event_Subscribe* e = (Upnp_Event_Subscribe*)event;
		Log::debug("UPNP_EVENT_SUBSCRIPTION_EXPIRED: Sid: %s EventKey: %s ChangedVariables: %s", e->Sid);
		/*        if(c->deviceList)
		        {
		            Device* device = c->deviceList->getDeviceBySid( e->Sid );
		        }*/
	}
	break;

	default:
		//Log::debug("UNHANDLED EVENT");
		break;
	}

	return UPNP_E_SUCCESS;
}

bool UPnP::NetScan(int waitSec)
{
	int res;
	m_addedDev = false;
	res = UpnpSearchAsync(CtrlPnt, waitSec, MEDIASERVERS, this);

	if(res != UPNP_E_SUCCESS)
	{
		Log::err("UpnpSearchAsync error: %s",UpnpGetErrorMessage(res));
	}

	res = UpnpSearchAsync(CtrlPnt, waitSec, MEDIARENDERERS, this);

	if(res != UPNP_E_SUCCESS)
	{
		Log::err("UpnpSearchAsync error: %s", UpnpGetErrorMessage(res));
	}

	//wait
	return true;//cfg->GetXml(deviceList);
	/*
	    res = UpnpSearchAsync( CtrlPnt, waitSec, ALL_DEVICE_TYPES, this );
	    if( res != UPNP_E_SUCCESS )
	    {
	        std::cerr<<"UpnpSearchAsync error: "<<UpnpGetErrorMessage( res )<<std::endl;
	    }
	        return deviceList;

	    */
}
