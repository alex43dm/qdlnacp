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

#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>
#include <map>
#include <ctime>

#include <upnp/upnp.h>
#include <upnp/ixml.h>

#include "include/Service.h"

class Device
{
	public:
		std::string _DeviceId;
		std::string _DeviceType;
		std::string _ServiceType;
		std::string _ServiceVer;
		std::string _Location;
		std::string _contentDirectoryControlURL;
		std::string _Os;
		std::string _IP;
		std::time_t _Time;
		std::string _baseURL;
		std::string _deviceType;
		std::string _UDN;
		std::string _friendlyName;

		Device();
		Device(const Upnp_Discovery* d);
		~Device();
		const char* getId() const;
		bool compareId( const char* id );
		bool compareDev( Device* d );
		bool comparefriendlyName( const char* name);
		bool fetchContents(void);
		bool subscribeToContentDirectory(void);
		std::string getDevInfo(void);
		const char * getfriendlyName(void);
		const char * getServiceType(void);
        std::map<ServiceType,Service*> services;
        void fetchInfo(void);
        IXML_Node* Dev2Xml( IXML_Document* doc );

	protected:

	private:
		std::string urlMarch(const std::string u);
        //std::vector<Service*> services;
        char *buf;
        IXML_Node* setVal(std::string name, std::string val, IXML_Document* doc);
};

#endif // _DEVICE_H_
