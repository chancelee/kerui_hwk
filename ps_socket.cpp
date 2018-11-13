#include <QDebug>
//#include "ps_socket.h"
//#include "settings.h"
#include "ps_m_wnd.h"

#define SOCK_VER 2

Ps_Socket::Ps_Socket(int n_port)
{
    this->m_n_port = n_port;
    this->m_l_sock = 0;

    this->m_p_thd_pool = 0;
    this->m_b_stop_listen = false;

    this->init();
    this->begin_listen();

    this->m_client_map = new QMap<SOCKET, Client_Session*>;
}

Ps_Socket::~Ps_Socket()
{

}

//单独开线程来接收新连接
void Ps_Socket::run()
{
    if(0 == this->m_p_thd_pool)
    {
        return;
    }

    this->m_p_thd_pool->start(this->m_heart_thd);
    this->accept_func();

}

//初始化建立socket
int Ps_Socket::init()
{
    //---------------初始化环境--------------------------
    int n_ret = 0;
    WSADATA wd = { 0 };

    n_ret = WSAStartup(MAKEWORD(SOCK_VER, 0), &wd);

    //初始化出错
    if (0 != n_ret)
    {
        return -1;
    }

    //当前版本不符合
    if (SOCK_VER != LOBYTE(wd.wVersion))
    {
        return -2;
    }

    //--------------建立socket-------------------
    SOCKET new_socket = 0;
    new_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //创建socket 失败 我的哥
    if (INVALID_SOCKET == new_socket)
    {
        new_socket = 0;
        WSACleanup();
        return -3;
    }

    this->m_l_sock = new_socket;

    return 0;
}

//绑定指定端口并监听
int Ps_Socket::begin_listen()
{
    int n_ret = 0;
    //--------------------bind---------------------------
    //建立结构体接收返回值
    sockaddr_in ser_addr = { 0 };

    ser_addr.sin_family = AF_INET;        //INTRL协议
    ser_addr.sin_port = htons(m_n_port);  //本机到网络转换

    //任意主机都可以连接
    ser_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    n_ret = bind(this->m_l_sock,                //socket
                 (SOCKADDR*)&ser_addr,   //指定端口
                 sizeof(sockaddr_in));   //结构体大小

    //如果绑定失败
    if(SOCKET_ERROR == n_ret)
    {
        goto SOCK_ERR;
    }

    //--------------------listen------------
    n_ret = listen(this->m_l_sock, SOMAXCONN);

    //监听失败
    if (SOCKET_ERROR == n_ret)
    {
        goto SOCK_ERR;
    }

    return 0;

SOCK_ERR:
    if (INVALID_SOCKET != this->m_l_sock)
    {
        closesocket(this->m_l_sock);
    }
    WSACleanup();
    return -3;
}

void Ps_Socket::setB_stop_listen(bool value)
{
    m_b_stop_listen = value;
}

void Ps_Socket::setP_thd_pool(QThreadPool* p_thd_pool)
{
    m_p_thd_pool = p_thd_pool;
}

void Ps_Socket::set_wnd_this(PS_M_Wnd *wnd_this)
{
    this->m_wnd_this = wnd_this;

    //写在这里简直太烂了  以后再改吧

    //开启检测心跳包的线程
    this->m_heart_thd = 0;
    this->m_heart_thd = new Heart_thd(this->m_client_map);

    //绑定心跳包和主窗口的槽函数
    connect(this->m_heart_thd, &Heart_thd::sin_dis_conn,
            this->m_wnd_this, &PS_M_Wnd::slot_disconn);
}

void Ps_Socket::cs_remove(SOCKET h_socket)
{
    this->m_client_map->remove(h_socket);
}



//接收函数  轮循接收是否有新的socket 如果有 调用接收 success:0  err:-1
int Ps_Socket::accept_func()
{
    //建立用来接收新连接的两个结构体
    SOCKET new_socket = INVALID_SOCKET;
    sockaddr_in new_ser = { 0 };

    int n_addr_len = sizeof(sockaddr_in);

    while (1)
    {
        //如果停止监听哨兵值为真
        if(m_b_stop_listen)
        {
            return 0;
        }

        //如果没有新连接
        if (!Net_Tools::Select(this->m_l_sock))
        {
            continue;
        }

        new_socket = INVALID_SOCKET;
        new_ser = { 0 };

        //接收新的socket 不出错就加入数组
        new_socket = accept(this->m_l_sock, (sockaddr*)&new_ser, &n_addr_len);

        qDebug() << "accept is run" ;

        //如果接收出错
        if (INVALID_SOCKET == new_socket)
        {
            qDebug() << "accept is error" ;
            continue;
        }

        //如果是重复的socket continue
        if (this->m_client_map->contains(new_socket))
        {
            closesocket(new_socket);
            qDebug() << "socket is existed\n";
            continue;
        }

        qDebug() << ("has a new connection\n");

//        //创建行数据结构体 初始化全0
//        Line_Data* p_ld = 0;
//        p_ld = new Line_Data;
//        memset(p_ld, 0, sizeof(Line_Data));

//        //赋值行数据的Socket IP
//        p_ld->s_host_sock = new_socket;
//        strcpy_s(p_ld->sz_host_ip, inet_ntoa(new_ser.sin_addr));

        //创建新的客户端会话结构体
        Client_Session* p_client_seeion = 0;
        p_client_seeion = new Client_Session(new_socket, new_ser);

        //开启一条线程接收新连接的数据
        Dps_Thd* p_dps_thd = 0;
        p_dps_thd = new Dps_Thd(p_client_seeion);

        //赋值线程指针成员
        p_client_seeion->m_dps_thd.reset(p_dps_thd);

        //数据结构中加入新元素
        this->m_client_map->insert(new_socket, p_client_seeion);

        //开新线程处理上线主机
        this->m_p_thd_pool->start(p_dps_thd);

        //连接线程和主窗口相关槽函数
        this->conn_this(p_dps_thd);


    } //end while

    return 0;
}

void Ps_Socket::conn_this(Dps_Thd* p_dps_thd)
{
    //连接上线信号处理槽函数
    connect(p_dps_thd, &Dps_Thd::sin_online,
            this->m_wnd_this, &PS_M_Wnd::slot_online);

    connect(p_dps_thd, &Dps_Thd::sin_create_dlg,
            this->m_wnd_this, &PS_M_Wnd::slot_create_dlg);

    connect(p_dps_thd, &Dps_Thd::sin_recv_data,
            this->m_wnd_this, &PS_M_Wnd::slot_recv_data);
}

Client_Session* Ps_Socket::get_cs(SOCKET h_soeket)
{
    if(!this->m_client_map->contains(h_soeket))
    {
        return 0;
    }

    return this->m_client_map->value(h_soeket);
}
