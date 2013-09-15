#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "Icon.h"

Icon::Icon() :
    data(NULL),
    length(0)
{
}

Icon::~Icon()
{
    if(data)
        free(data);
}

int Icon::write(const char* pdata, size_t n)
{
    length = n;
    data = (uint8_t *)malloc(length);
    memcpy(data, pdata, length);
    return n;
}

bool Icon::save(const std::string &fileName)
{
    int fd;

    unlink(fileName.c_str());
    fd = ::open(fileName.c_str(),O_RDWR|O_CREAT,0640);
    if(fd < 0)
    {
        return false;
    }
    ::write(fd, data, length);
    ::close(fd);

    return true;
}
