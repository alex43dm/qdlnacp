#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>

#include "Icon.h"
#include "TcpClient.h"

class HttpClient : public TcpClient
{
public:
    typedef std::string::size_type size_type;
    char *data;
    size_t length;

	HttpClient();
	virtual ~HttpClient();

	bool get(const std::string &, int, Icon *);
protected:
private:
    size_t bufSize;
    char *buf;
    size_t ret;
    size_t imageSize;

    bool headersParce();
};

#endif // HTTPCLIENT_H
