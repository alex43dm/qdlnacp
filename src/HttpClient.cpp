#include <stdlib.h>
#include <string.h>

#include "HttpClient.h"
#include "Log.h"

HttpClient::HttpClient() :
	TcpClient(),
	bufSize(1024*1024)
{
	buf = (char*)malloc(bufSize);
}

HttpClient::~HttpClient()
{
	free(buf);
}

bool HttpClient::get(const std::string &host, int port, Icon *ic)
{
	if(connect(host, port))
	{
		bzero(buf,bufSize);
		snprintf(buf, bufSize, "GET %s HTTP/1.0\r\n\r\n", ic->url.c_str());
		write(buf,strnlen(buf, bufSize));

		bzero(buf,bufSize);
		ret = read((void**)&buf,bufSize);

		if(ret > 0 && headersParce())
		{
		    int b;
            char *p = buf+ret;

            b =  read((void**)&p,bufSize);
            ret += b;

		    while(ret != imageSize && b != 0)
            {
                char *p = buf+ret;
                b =  read((void**)&p,bufSize);
                ret += b;
            }
			//cut the image
			ic->length = imageSize;
			ic->write((const char *)(buf + ret - imageSize), imageSize);
		}

		close();
	}

	return true;
}

bool HttpClient::headersParce()
{
	imageSize = 0;
	const std::string ContentLength("Content-Length: ");
	const std::string p = buf;
	const std::string sheader = p.substr(0, p.find("\r\n\r\n"));
	//Log::debug("header: %s",sheader.c_str());
	const std::string  http = p.substr(0, sheader.find("\r\n"));

	if(http.find("200") == std::string::npos)
	{
		Log::err("Http error: %s",http.c_str());
		return false;
	}

	size_type iLengthBegin = sheader.find(ContentLength) + ContentLength.size();
	size_type iLengthEnd = sheader.find("\r\n", iLengthBegin);
	const std::string cl = sheader.substr(iLengthBegin,iLengthEnd-iLengthBegin);
	imageSize = atoi(cl.c_str());

  	if(imageSize >bufSize)
    {
        Log::warn("Image size(%d) too huge buffer size(%d). Ignore it.",imageSize, bufSize);
        return false;
    }

	return true;
}
