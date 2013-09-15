#include "include/Container.h"


Container::Container(Container* parent, const char* objectID, const char* title) :
	_isLoaded(false),
	_parent(parent),
	_objectID(objectID),
	_title(title)
{
}

Container::~Container()
{
	for(unsigned int i = 0; i < _containers.size(); i++)
	{
		delete _containers[i];
	}

	for(unsigned int i = 0; i < _items.size(); i++)
	{
		delete _items[i];
	}
}

void Container::addItem(Item* item)
{
	_items.push_back(item);
	_isLoaded = true;
}

void Container::addContainer(Container* container)
{
	_containers.push_back(container);
	_isLoaded = true;
}

const char* Container::getObjectID() const
{
	return _objectID.c_str();
}

const char* Container::getTitle() const
{
	return _title.c_str();
}

const std::string Container::getStr() const
{
	return artist.size() ? artist + "-" + _title : _title;
}

unsigned int Container::getNumItems() const
{
	return _items.size();
}

unsigned int Container::getNumContainers() const
{
	return _containers.size();
}

Item* Container::getItem(unsigned int i) const
{
	if(i < _items.size()) return _items[i];

	return 0;
}

Container* Container::getContainer(unsigned int i) const
{
	if(i < _containers.size()) return _containers[i];

	return 0;
}

