#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <vector>

#include "include/Item.h"

class Container
{
public:
    std::string artist;
    std::string album;

    Container( Container* parent, const char* objectID, const char* title );
    ~Container();

    void addItem( Item* item );
    void addContainer( Container* container );

    const char* getObjectID() const;
    const char* getTitle() const;
    Container *getParent() const{ return _parent;};
    const std::string getStr() const;

    unsigned int getNumItems() const;
    unsigned int getNumContainers() const;

    Item* getItem( unsigned int i ) const;
    Container* getContainer( unsigned int i ) const;
    inline bool isLoaded()const{return _isLoaded;};

private:
    bool _isLoaded;
    Container* _parent;

    std::string _objectID;
    std::string _title;
    std::vector<Item*> _items;
    std::vector<Container*> _containers;
};

#endif // CONTAINER_H
