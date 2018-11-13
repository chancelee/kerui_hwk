#include <QDebug>
#include "qsettings.h"
#include "client_session.h"

#define MAX_SIZE 1024

Dps_Thd::Dps_Thd(Client_Session* p_cs)
{
    this->m_p_cs = 0;
    this->m_p_cs = p_cs;
    this->m_b_stop_recv = false;
}

Dps_Thd::~Dps_Thd()
{

}

void Dps_Thd::run()
{
    this->send_online();
    this->recv_func();
}

//发送上线包让主机上线
int Dps_Thd::send_online()
{
    int n_ret = 0;

    SOCKET h_sock = 0;
    h_sock = this->m_p_cs->m_sock;

    if(0 == h_sock)
    {
        return -1;
    }

    //初始化 发送一个上线包
    Data_Head* p_get_info = new Data_Head(PSC_ONLINE);

    //发送命令让被控端上线
    n_ret = Net_Tools::send_buf(h_sock,
                                (char*)p_get_info,
                                sizeof(Data_Head));

    //如果发送失败
    if (SOCKET_ERROR == n_ret)
    {
        throw "send is error";
    }

    return 0;
}

//接收被控端发来的数据
int Dps_Thd::recv_func()
{
    int n_ret = 0;
    int n_recv_size = 0;

    //获取当前对应socket
    SOCKET h_socket = 0;
    h_socket = this->m_p_cs->m_sock;

    //初始化接收缓冲区 初始化为0
    char* p_head = 0;   //头数据
    char* p_data = 0;   //主要数据包
    p_head = new char[sizeof(Data_Head)]();

    while (1)
    {
        if(m_b_stop_recv)
        {
            break;
        }

        if (!Net_Tools::Select(h_socket))   //如果有新数据过来
        {
           continue;
        }

        //先接收数据头 获取数据长度 然后接收数据包
        memset(p_head, 0, sizeof(Data_Head));
        n_ret = Net_Tools::recv_buf(h_socket,
                                    p_head,
                                    sizeof(Data_Head));

        //如果接收数据头出错
        if (0 != n_ret)
        {

            qDebug() << "recv is err \n" ;
            goto SOCK_ERR;
        }

        //没有软件签名就不处理
        if(!this->check_data_head(p_head))
        {
            continue;
        }

        //接收数据包
        n_recv_size = ((Data_Head*)p_head)->n_size;

        if(n_recv_size > 0)
        {
            p_data = new char[n_recv_size]();
            n_ret = Net_Tools::recv_buf(h_socket, p_data, n_recv_size);

            if (0 != n_ret)
            {
                qDebug() << "recv is err \n" ;
                goto SOCK_ERR;
            }
        }

        //分发处理命令
        this->ifs_dps((Data_Head*)p_head, p_data);

        if(0 != p_data)
        {
            //delete[] p_data;
        }
    }//end while

    delete[] p_head;
    return 0;

SOCK_ERR:
    if (INVALID_SOCKET != this->m_p_cs->m_sock)
    {
        closesocket(this->m_p_cs->m_sock);
    }

    WSACleanup();
    return -1;
}

//处理心跳包
int Dps_Thd::ifs_heart()
{
    Data_Head data_head(PSC_HEART_BEAT);
    Net_Tools::send_buf(this->m_p_cs->m_sock,
                        (char*)&data_head,
                        sizeof(Data_Head));
}

//检测数据头 如果没有 软件签名不处理
bool Dps_Thd::check_data_head(char *p_buf)
{
    int n_ret = 0;

    //对比前面有没有软件签名 'smile'
    n_ret = memcmp(PACK_FLAG,
                   ((Data_Head*)p_buf)->sz_flag,
                   PACK_FLAG_SIZE);

    if (n_ret != 0)
    {
        qDebug() << "\n bad online_data \n";
        return false;
    }

    return true;
}


int Dps_Thd::ifs_dps(Data_Head* p_head, char *p_data)
{
    //获取数据包大小
    int n_data_size = p_head->n_size;

    //获取命令id
    unsigned char c_cmd_id = p_head->c_id;

    //获取命令类型
    unsigned char c_cmd_type = p_head->c_type;

    //任何数据包发过来都有必要更新时间
    QTime time = QTime::currentTime();
    this->m_p_cs->m_last_time
            = time.msecsSinceStartOfDay();

    switch (c_cmd_type)
    {
    case PSC_HEART_BEAT:
        this->ifs_heart();
        break;

    case PSC_ONLINE:
        this->ifs_online(p_data);
        break;

    case PSC_CMD:
        this->ifs_cmd(c_cmd_id, p_data, n_data_size);
        break;

    case PSC_REG:
        break;

    case PSC_PROC:
        break;

    case PSC_SCREEN:
        this->ifs_scr(c_cmd_id, p_data, n_data_size);
        break;

    default:
        break;
    }
}


int Dps_Thd::ifs_online(char *p_data)
{
    //深拷贝一份数据
    Line_Data* p_l = new Line_Data();
    memcpy(p_l, p_data, sizeof(Line_Data));

    //赋值ip 和 socket
    strcpy_s(p_l->sz_host_ip,
             inet_ntoa(this->m_p_cs->m_ser.sin_addr));
    p_l->s_host_sock = this->m_p_cs->m_sock;

    //发送信号 完成上线
    emit sin_online(p_l);
}

int Dps_Thd::ifs_cmd(unsigned char c_cmd_id, char *p_data, int n_data_size)
{ 
    if(PSC_CMD_REPLY == c_cmd_id)
    {
        emit sin_create_dlg(this->m_p_cs, PSC_CMD_REPLY);
    }
    else if(PSC_CMD_DATA == c_cmd_id)
    {        
        emit sin_recv_data(this->m_p_cs,
                           PSC_CMD_DATA,
                           QByteArray(p_data, n_data_size));
    }
}

int Dps_Thd::ifs_scr(unsigned char c_cmd_id, char *p_data, int n_data_size)
{ 
    if(PSC_SCR_REPLY == c_cmd_id)
    {
        emit sin_create_dlg(this->m_p_cs, PSC_SCR_REPLY);
    }
    else if(PSC_SCR_DATA == c_cmd_id)
    {
        emit sin_recv_data(this->m_p_cs,
                           PSC_SCR_DATA,
                           QByteArray(p_data, n_data_size));
    }
}

void Dps_Thd::setB_stop_recv(bool b_stop_recv)
{
    m_b_stop_recv = b_stop_recv;
}
