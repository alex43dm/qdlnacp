#ifndef ICON_H
#define ICON_H

#include <stdint.h>
#include <string>

class Icon
{
    public:
        std::string width;
        std::string height;
        std::string depth;
        std::string url;
        std::string mimetype;
        uint8_t *data;
        size_t length;

        Icon();
        Icon(size_t);
        virtual ~Icon();
        int write(const char* pdata, size_t n);
        bool save(const std::string &fileName);
        int widthInt(){return atoi(width.c_str());};
        int heightInt(){return atoi(height.c_str());};

    protected:

    private:
};

#endif // ICON_H
