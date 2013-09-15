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
#include <string.h>
#include <algorithm>
#include <iostream>


#include "DeviceList.h"
#include "Log.h"

DeviceList::DeviceList()
{
	m_list = new std::vector<Device *>();
	len = 0;
}

DeviceList::~DeviceList()
{
	for(unsigned int i = 0; i < m_list->size(); i++)
	{
		delete(*m_list)[i];
	}

	delete m_list;
}



bool DeviceList::addDevice(Device* s, bool scan)
{
	if(scan)
	{
		s->fetchInfo();
	}

	m_list->push_back(s);
	//len++;
	return true;
}

Device* DeviceList::getDevice(std::string id)
{
	Device* result = 0;

	for(unsigned int i = 0; i < m_list->size(); i++)
	{
		if(id == (*m_list)[i]->getId())
		{
			result = (*m_list)[i];
			break;
		}
	}

	return result;
}

Device* DeviceList::getDevice(unsigned int id)
{
	if( id < m_list->size())
	{
        return (*m_list)[id];
	}

	return NULL;
}

void DeviceList::removeDevice(const char* id)
{
	Device* device = getDevice(id);

	if(!device) return;

	std::vector<Device*>::iterator it;

	for(it = m_list->begin(); it != m_list->end(); it++)
	{
		if(*it == device)
		{
			m_list->erase(it);
			delete device;
			break;
		}
	}
}

void DeviceList::replaceDevice(Device* d)
{
	for(unsigned int i = 0; i < m_list->size(); i++)
	{
		if(d->_DeviceId == (*m_list)[i]->_DeviceId)
		{
			(*m_list)[i] = d;
			break;
		}
	}
}

Device* DeviceList::getDeviceByID(const char* id)
{
	for(unsigned int i = 0; i < m_list->size(); i++)
	{
		if((*m_list)[i]->compareId(std::string(id)))
		{
			return (*m_list)[i];
		}
	}
	return NULL;
}

bool DeviceList::isDeviceByID(const char* id)
{
    //Log::debug("check id: (%s)",id);
   	for(unsigned int i = 0; i < m_list->size(); i++)
	{
		if(((*m_list)[i])->compareId(std::string(id)))
		{
			return true;
		}
	}

	return false;
}

Device* DeviceList::getDeviceBySid(const char* sid)
{
	Device* device = 0;

	for(unsigned int i = 0; i < m_list->size(); i++)
	{
		if((*m_list)[i]->getServicebySid(sid))
		{
			device = (*m_list)[i];
			break;
		}
	}

	return device;
}

Device* DeviceList::getDeviceByfriendlyName(const char* name, ServiceType t)
{
	Device* device = 0;

	for(unsigned int i = 0; i < m_list->size(); i++)
	{
		if((*m_list)[i]->comparefriendlyName(name) && (*m_list)[i]->getType() == t)
		{
			device = (*m_list)[i];
			break;
		}
	}

	return device;
}

Device* DeviceList::getRenderByfriendlyName(const char* name)
{
	return getDeviceByfriendlyName(name, AVTransport);
}

Device* DeviceList::getServerByfriendlyName(const char* name)
{
    return getDeviceByfriendlyName(name, ContentDirectory);
}

std::vector<Device *> *DeviceList::getList(void)
{
	return m_list;
}

void DeviceList::fetchInfo()
{
	for(unsigned int i = 0; i < m_list->size(); i++)
	{
		(*m_list)[i]->fetchInfo();
	}
}
