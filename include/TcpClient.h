#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <string>
#include <sstream>

#include<netdb.h>

class TcpClient
{
public:
	TcpClient();
	virtual ~TcpClient();
	bool checkPort(const std::string &address , const int port);
	inline const std::string error(){return m_log.str();};
	bool close();
	bool connect(const std::string &address , const int port);
	bool write(const void *buf, size_t sz);
	size_t read(void **buf, size_t sz);
protected:
private:
	int m_sock;
	std::string m_address;
	int m_port;
	struct sockaddr_in m_server;
	std::stringstream m_log;
};

#endif // TCPCLIENT_H
