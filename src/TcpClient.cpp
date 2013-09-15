#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "TcpClient.h"
#include "Log.h"

TcpClient::TcpClient() :
	m_sock(-1)
	,m_address("")
	,m_port(0)
{
	//ctor
}

TcpClient::~TcpClient()
{
	//dtor
}

bool TcpClient::checkPort(const std::string &address , const int port)
{
	struct hostent *he;
	struct in_addr **addr_list;

	m_log.str("");

	if(m_sock == -1)
	{
		if((m_sock = socket(AF_INET , SOCK_STREAM , 0)) == -1)
		{
			return false;
		}
	}

	if((he = gethostbyname(address.c_str())) == NULL)
	{
		m_log<<"Failed to resolve hostname\n";
		return false;
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for(int i = 0; addr_list[i] != NULL; i++)
	{
		m_server.sin_addr = *addr_list[i];
		break;
	}

	m_server.sin_family = AF_INET;
	m_server.sin_port = htons(port);

	if(::connect(m_sock , (struct sockaddr *)&m_server , sizeof(m_server)) < 0)
	{
		m_log<<"connect failed. Error: " << strerror(errno)<<std::endl;
		return false;
	}

	::close(m_sock);
	return true;
}

bool TcpClient::close()
{
	::close(m_sock);
	return true;
}

bool TcpClient::connect(const std::string &address , const int port)
{
	struct hostent *he;
	struct in_addr **addr_list;

	m_log.str("");

	if(m_sock == -1)
	{
		if((m_sock = socket(AF_INET , SOCK_STREAM , 0)) == -1)
		{
			return false;
		}
	}

	if((he = gethostbyname(address.c_str())) == NULL)
	{
		m_log<<"Failed to resolve hostname\n";
		return false;
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for(int i = 0; addr_list[i] != NULL; i++)
	{
		m_server.sin_addr = *addr_list[i];
		break;
	}

	m_server.sin_family = AF_INET;
	m_server.sin_port = htons(port);

	if(::connect(m_sock , (struct sockaddr *)&m_server , sizeof(m_server)) < 0)
	{
		m_log<<"connect failed. Error: " << strerror(errno)<<std::endl;
		return false;
	}

	return true;
}

bool TcpClient::write(const void *buf, size_t sz)
{
    size_t ret;
    ret = ::send(m_sock, buf, sz, 0);
    //Log::debug("send: %d",ret);
    return ret == sz;
}

size_t TcpClient::read(void **buf, size_t sz)
{
    size_t ret = ::recv(m_sock, *buf, sz, 0);
    //Log::debug("recv: %d",ret);
    return ret;
}


