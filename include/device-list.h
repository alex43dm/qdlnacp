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

#ifndef _DEVICE_LIST_H_
#define _DEVICE_LIST_H_

#include <vector>
#include <mutex>

#include "device.h"

class DeviceList
{
	public:
		DeviceList();
		~DeviceList();

		bool addDevice(  Device* s , bool scan);
		void removeDevice( const char* id );
		Device* getDeviceByID( const char* id );
		Device* getDeviceByfriendlyName( const char* name );
		Device* getDevice( std::string id );
		std::vector<Device *> getList( void );
	protected:

	private:
        std::mutex _mutex;
		std::vector<Device *> _list;
};

#endif // _DEVICE_LIST_H_
