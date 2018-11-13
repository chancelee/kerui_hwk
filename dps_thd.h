#ifndef DPS_THD_H
#define DPS_THD_H

#include <QObject>
#include <QRunnable>
#include <QTime>
#include <QSharedPointer>

#include "settings.h"
#include "net_tools.h"

struct Client_Session;

//每个被控端上线后的处理线程
class Dps_Thd:public QObject, public QRunnable
{
    Q_OBJECT

public:
    Dps_Thd(Client_Session* p_cs);
    ~Dps_Thd();

public:
    virtual void run();

public:
    int ifs_dps(Data_Head* p_head, char* p_data);            //分发处理接口

public:
    bool check_data_head(char* p_buf);

public:
    int send_online();   //发送上线数据包
    int recv_func();     //接收客户端数据

public:
    int ifs_heart();                //心跳包的处理函数
    int ifs_online(char* p_data);   //上线包的处理函数

    int ifs_cmd(unsigned char c_cmd_id, char *p_data, int n_data_size);
    int ifs_scr(unsigned char c_cmd_id, char *p_data, int n_data_size);

public:
    void setB_stop_recv(bool b_stop_recv);

signals:
    void sin_online(Line_Data* p_data);

    void sin_create_dlg(Client_Session* p_cs, int type);
    void sin_recv_data(Client_Session* p_cs, int type, QByteArray buf);

private:
    Client_Session* m_p_cs;

private:
    bool m_b_stop_recv;

};

#endif // DPS_THD_H
