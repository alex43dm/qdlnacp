#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#include <QObject>
#include "u-pn-p.h"

class ScanThread : public QObject
{
    Q_OBJECT
public:
    explicit ScanThread();
    ~ScanThread();

public slots:
    void process();
    void sendMes();

signals:
    void finished();
    void error(QString err);
    void info(QString err);
    void clear();
private:
    UPnP* u;
};

#endif // SCANTHREAD_H
