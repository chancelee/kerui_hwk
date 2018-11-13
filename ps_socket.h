#ifndef PS_SOCKET_H
#define PS_SOCKET_H

#include <QThread>
#include <QThreadPool>

#include "heart_thd.h"

class PS_M_Wnd;

class Ps_Socket:public QThread
{
    Q_OBJECT

public:
    Ps_Socket(int n_port);
    ~Ps_Socket();

public:
    virtual void run();

public:
    int init();
    int begin_listen();
    int accept_func();

public:
    Client_Session *get_cs(SOCKET h_soeket);

public:
    void setB_stop_listen(bool value);
    void setP_thd_pool(QThreadPool* p_thd_pool);
    void set_wnd_this(PS_M_Wnd* wnd_this);

public:
    void cs_remove(SOCKET h_socket);

private:
    int m_n_port;          //监听的端口
    bool m_b_stop_listen;  //停止监听的哨兵值

private:  //连接线程信号和主窗口槽函数
    void conn_this(Dps_Thd* p_dps_thd);

private:
    QMap<SOCKET, Client_Session*>* m_client_map;

private:
    SOCKET m_l_sock;       //监听的socket

private:
    QThreadPool* m_p_thd_pool;
    Heart_thd* m_heart_thd;

private:
    PS_M_Wnd* m_wnd_this;
};

#endif // PS_SOCKET_H
