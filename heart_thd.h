#ifndef HEART_THD_H
#define HEART_THD_H

#include <QObject>
#include <QRunnable>
#include <QMap>
#include <QSharedPointer>
#include <winsock2.h>
#include "client_session.h"

//检测被控端心跳 掉线的线程
class Heart_thd:public QObject, public QRunnable
{
    Q_OBJECT

public:
    Heart_thd(QMap<SOCKET, Client_Session*>* cs_map);

public:
    virtual void run();

public:
    int check_heart();

signals:
    void sin_dis_conn(Client_Session* p_cs);  //发送掉线信号

private:
    QMap<SOCKET, Client_Session*>* m_cs_map;

private:
    bool m_b_stop_check;
};

#endif // HEART_THD_H
