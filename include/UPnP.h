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

#ifndef _U_PN_P_H_
#define _U_PN_P_H_

#include <string>
#include <map>

extern "C"{
    #include <upnp/upnp.h>
    #include <upnp/upnptools.h>
    #include <upnp/ixml.h>
}

#include "DeviceList.h"
#include "Container.h"
#include "Config.h"

#define ALL_DEVICE_TYPES "upnp:rootdevice"
#define MEDIASERVERS "urn:schemas-upnp-org:device:MediaServer:1"
#define MEDIARENDERERS "urn:schemas-upnp-org:device:MediaRenderer:1"
#define CONTENT_DIRECTORY_SERVICE_TYPE "urn:schemas-upnp-org:service:ContentDirectory:1"

class UPnP
{
	public:
		UPnP();
		~UPnP();
		operator UpnpClient_Handle() const { return CtrlPnt; }
		bool NetScan(int );
		bool SaveConfig();
        bool init();
	protected:
//	    void ilock(){pthread_mutex_lock(&m_mtx);};
//	    void iunlock(){pthread_mutex_unlock(&m_mtx);};

	    bool m_addedDev;
	    bool m_removedDev;
	    DeviceList* deviceList;
        UpnpClient_Handle  CtrlPnt;

	private:
	    bool isInited;
        static int Callback( Upnp_EventType eventType, void* event, void* pCookie );
        Config *cfg;
};

#endif // _U_PN_P_H_
