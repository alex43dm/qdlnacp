#include "Log.h"

extern char *__progname;

Log::Log(int facility)
{
	facility_ = facility;
	priority_ = LOG_DEBUG;
	openlog(__progname, LOG_PID, facility_);
}

Log::~Log()
{
	closelog();
}
