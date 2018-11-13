#ifndef SETTINGS_H
#define SETTINGS_H

#include <winsock2.h>

#define PACK_FLAG "SMILE"
#define PACK_FLAG_SIZE 6

//PSC == Pc_Share_Command
//命令的枚举  比如上线 文件 各种命令
enum Em_Psc_Type
{
    PSC_ONLINE = 122,
    PSC_INFO,
    PSC_REG,
    PSC_CMD,
    PSC_PROC,
    PSC_SERV,
    PSC_SCREEN,
    PSC_KEYBORAD,
    PSC_HEART_BEAT
};

//cmd枚举
enum Em_Cmd_Type
{
    PSC_CMD_INIT,	//cmd初始化
    PSC_CMD_REPLY,	//cmd窗口已经准备好
    PSC_CMD_DATA,	//cmd命令
    PSC_CMD_CLOSE,	//cmd关闭
};

//远程屏幕枚举
enum Em_Scr_Type
{
    PSC_SCR_INIT = 5,	//cmd初始化
    PSC_SCR_REPLY,      //cmd窗口已经准备好
    PSC_SCR_DATA,       //cmd命令
    PSC_SCR_CLOSE,      //cmd关闭
};

//服务枚举
enum Em_Serv_Type
{
    PSC_SERV_INIT = 9,	 //服务初始化
    PSC_SERV_REPLY,      //服务窗口已经准备好
    PSC_SERV_DATA,       //获取服务列表
    PSC_SERV_CLOSE,      //服务关闭
};

struct Col_Data
{
    char* sz_title;
    int n_width;
};

//数据头 这里注意字节对齐
#pragma pack(push, 1)
struct Data_Head
{
    Data_Head()
    {
        this->c_id = 0;
        this->c_type = 0;
        this->n_size = sizeof(Data_Head);
        strcpy_s(this->sz_flag, PACK_FLAG);
    }

    Data_Head(unsigned char c_cmd_type,
              unsigned char c_cmd_id = 0)
    {
        this->c_type = c_cmd_type;
        this->c_id = c_cmd_id;

        this->n_size = sizeof(Data_Head);
        strcpy_s(this->sz_flag, PACK_FLAG);
    }

    char sz_flag[6];	   //软件签名
    unsigned char c_type;  //命令类型
    unsigned char c_id;	   //命令ID
    int n_size;            //数据包大小
};
#pragma pack(pop)

//行数据的结构体
#pragma pack(push, 1)
struct Line_Data
{
    char sz_host_ip[20];   //主机IP
//  char c_host_os;        //主机版本
    char c_host_ver;       //客户端版本
    char c_host_cpu;       //主机核心数
    char c_is_camera;      //是否有摄像头
    SOCKET s_host_sock;    //套接字
};
#pragma pack(pop)

//上线包结构体
#pragma pack(push, 1)
struct OnLine_Data
{
    Data_Head data_head;   //数据头
    Line_Data line_data;   //行数据
};
#pragma pack(pop)

//屏幕数据包 用到的结构体 表屏幕宽高
#pragma pack(push, 1)
struct Scr_Data
{
    Scr_Data()
    {
        this->n_width = 0;
        this->n_height = 0;
    }

    int n_width;
    int n_height;
};
#pragma pack(pop)

#endif // SETTINGS_H
