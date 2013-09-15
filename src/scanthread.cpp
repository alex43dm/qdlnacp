#include "scanthread.h"
#ifdef DEBUG
#include <QDebug>
#endif

#include "u-pn-p.h"


ScanThread::ScanThread()
{
    u = new UPnP();
}

ScanThread::~ScanThread()
{

}

void ScanThread::sendMes()
{
    /*
    u->SendAction("MediaTomb",
                  ContentDirectory,
                  "Browse"
                  ,2
                  ,"ObjectID", "0");*/
}

void ScanThread::process()
{
#ifdef DEBUG
    qDebug("thread run");
#endif

    //scan
    //DeviceList *dl = u->NetScan(5);
    //sleep(5);
    //u->SaveConfig();
    //set avi
    u->SetAvi();
/*
    for(;;)
    {
        sleep(5);
        emit clear();
        std::vector<Device *> l = dl->getList();
        for ( unsigned int i = 0; i < l.size(); i++ )
        {
            std::string ret = l[i]->getDevInfo();
            emit info(QString::fromUtf8(ret.c_str()));
        }
    }
    */
#ifdef DEBUG
        qDebug("thread exit");
#endif
    emit finished();
}
