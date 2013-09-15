#include "Log.h"
#include "UPnP_CP.h"

UPnP_CP::UPnP_CP() :
	UPnP(),
	syncTrackTimeSec(20),
	m_render(NULL),
	m_server(NULL),
	m_startTimer(false)
{
	//start();
}

UPnP_CP::~UPnP_CP()
{
	//dtor
}

bool UPnP_CP::SetRenderer(const std::string &id)
{
	if(m_render)
	{
		m_render->unSubscribe();
	}

	m_render = (UPnP_MediaRenderer *)deviceList->getRenderByfriendlyName(id.c_str());

	if(m_render)
	{
		m_render->subscribe();
		m_render->InitInfo();
		//UPnP_MediaRenderer::onEvent = onRenderEvent;
		if(m_render->TransportState == "PLAYING")
        {
            m_position = m_render->Position;
            m_startTimer = true;
        }
        SaveConfig();
		return true;
	}

	return false;
}

bool UPnP_CP::SetServer(const std::string &id)
{
	if(m_server)
	{
		m_server->unSubscribe();
	}

	m_server = (UPnP_MediaServer *)deviceList->getServerByfriendlyName(id.c_str());

	if(m_server)
	{
	    SaveConfig();
		return m_server->subscribe();
	}

	return false;
}

Container* UPnP_CP::next(const std::string &itm)
{
	return m_server->nextFolder(itm);
}

bool UPnP_CP::startScan(int timeOut = 5)
{
	lock();
	bool ret = NetScan(timeOut);
	//SaveConfig();
	return ret;
	unlock();
}

bool UPnP_CP::PlayListAdd(const std::string &id)
{
	if(!m_render) return false;

	m_render->PlayListAdd(m_server->FindById(id));
	return true;
}

bool UPnP_CP::PlayFromList(const std::string &id)
{
	if(!m_render) return false;

    m_position = 0;
    m_startTimer = true;

	return m_render->Play(id);
}

bool UPnP_CP::Play()
{
	if(!m_render) return false;

    if(m_render->isPaused())
    {
        m_render->Play();
        //m_position = 0;
        //m_position = m_render->getPositionInfo();
        m_startTimer = true;
        return true;
    }else if(m_render->isStoped())
    {
        m_render->Play();
        m_position = 0;
        m_startTimer = true;
        return true;
    }
    else
    {
        m_render->Pause();
        m_position++;
        m_startTimer = false;
    }

    return false;
}

bool UPnP_CP::SetTrack(const std::string &id)
{
    if(!m_render) return false;

    m_render->SetTrack(id);
    m_position = 0;
    m_startTimer = true;
    return true;
}

bool UPnP_CP::Stop()
{
	if(!m_render) return false;

    m_startTimer = false;
	m_position = 0;

	m_render->Stop();
	return true;
}

bool UPnP_CP::Pause()
{
	if(!m_render) return false;

	m_render->Pause();
	return true;
}

bool UPnP_CP::Next()
{
	if(!m_render) return false;

    m_position = 0;
    m_startTimer = true;

	m_render->Next();
	return true;
}

bool UPnP_CP::Prev()
{
	if(!m_render) return false;

    m_position = 0;
    m_startTimer = true;

	m_render->Prev();
	return true;
}

bool UPnP_CP::VolSet(int vol)
{
    if(!m_render) return false;

    char str[3];
    std::string v;

    memset(str,0,sizeof(str));
    int num = sprintf(str, "%3d", vol);
    v.assign(str, num);

    return m_render->setVol(v);
}

bool UPnP_CP::Seek(int val)
{
    if(!m_render) return false;

    m_render->Seek(val);
    m_position = val;
    return true;
}

void UPnP_CP::Sleep(int timeOut)
{
    int i = 0;
    while( i < timeOut)
    {
        sleep(1);

        if(m_startTimer)
        {
            //Log::debug("timerFinish pos: %d len %d", m_position, m_render->TrackLengthSec);
            if(m_position < m_render->TrackLengthSec)
            {
                //track time sync
                if(m_position!= 1 && (m_position % syncTrackTimeSec) == 0)
                {
                    m_position = m_render->getPositionInfo();
                    /*
                    unsigned int pos = m_render->getPositionInfo();

                    if(pos < m_position) continue;

                    while(pos > m_position)
                    {
                       m_position++;
                       timerTick();
                    }*/
                }
                m_position++;
                timerTick();
            }
            else
            {
                m_startTimer = false;

                Next();
                Log::debug("timerFinish pos: %d len %d", m_position, m_render->TrackLengthSec);
                timerFinish();
            }
        }
        i++;
    }
}

void *UPnP_CP::threadLoop()
{
	while(!fExit)
	{
		lock();
		UPnP::NetScan(TINEOUT);
		Sleep(TINEOUT);
		deviceList->fetchInfo();
		unlock();

		if(m_addedDev)
		{
			Log::debug("new devices found, dev list size: %d", deviceList->Size());
			onDeviceAdd();
			m_addedDev=false;
		}

		if(m_removedDev)
		{
			Log::debug("devices removed, dev list size: %d", deviceList->Size());
			onDeviceRemove();
			m_removedDev=false;
		}

		//onScanStop();
		Sleep(timeOutScan);
		//onScanStart();
	}

	return 0;
}
