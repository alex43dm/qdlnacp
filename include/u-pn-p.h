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

#include <upnp/upnp.h>
#include <upnp/upnptools.h>
#include <upnp/ixml.h>

#include <mutex>

#include "device-list.h"
#include "include/Container.h"
#include "Config.h"

class UPnP
{
	public:
		UPnP();
		~UPnP();
		operator UpnpClient_Handle() const { return CtrlPnt; }
		DeviceList* NetScan(int );

		bool getMedia(Container* parent);
		void buildPlaylist( Container* parent );
		bool getItem( Container* parent);
		long id;
		Item* found;
		void SetAvi(void);
		bool SaveConfig();

		IXML_Document* SendAction(std::string id, ServiceType st, const char* actionName, int count, ...);
		DOMString getSrvVar( std::string srvName, ServiceType stype, std::string varName);
		//int Send( const char* url, const char* ServiceType, const char* DevUDN, IXML_Document* Action, IXML_Document** Resp);
		//int GetVar( const char* url, const char* VarName, DOMString* StVarVal);
	protected:

	private:
        void initialize();
        UpnpClient_Handle  CtrlPnt;
        static int Callback( Upnp_EventType eventType, void* event, void* pCookie );
        DeviceList* deviceList;
        std::mutex _mutex;
        Config *cfg;
};

#endif // _U_PN_P_H_
