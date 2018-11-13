#include "net_tools.h"


Net_Tools::Net_Tools()
{

}

//选择模型 可读可写返回true 默认等待100毫秒  静态函数
bool Net_Tools::Select(SOCKET h_socket, bool b_read, int n_time_out)
{
    int n_ret = 0;

    /*初始化所需结构体*/
    timeval tv = {0};
    fd_set fdset = {0};

    //把hsocket 加入套接字 fdset
    FD_SET(h_socket, &fdset);

    /*大于1秒会影响效率 所以最大1000就挺好*/
    n_time_out = n_time_out > 1000 ? 1000 : n_time_out;
    tv.tv_sec = 0;
    tv.tv_usec = n_time_out;

    //bread = 1 表示监测socket 是否可读   = 0 表示是否可写
    if (b_read)
    {
        n_ret = select(0, &fdset, NULL, NULL, &tv);
    }
    else
    {
        n_ret = select(0, NULL, &fdset, NULL, &tv);
    }

    if (n_ret <= 0)
    {
        //如果不可读 不可写 返回flase
        return false;
    }
    else if (FD_ISSET(h_socket, &fdset))
    {
        return true;
    }

    return false;
}


/*发送数据
 * arg1 发送的socket
 * arg2 发送的数据
 * arg3 要发送数据的大小
 *
 * ret(0) 发送成功 (-1)凉了
 *
 */
int Net_Tools::send_buf(SOCKET h_socket, char* p_buf, int n_buf_size)
{
    //分块发送数据
    int n_ret = send_part(h_socket, p_buf, n_buf_size);

    if(-1 == n_ret)
    {
        return SOCKET_ERROR;
    }

    return 0;
}


int Net_Tools::recv_buf(SOCKET h_socket, char* p_buf, int n_buf_size)
{
    int n_ret = 0;
    int n_recv_len = 0;              //已经接收长度
    int n_remain_len = n_buf_size;   //剩余接收长度

    if (0 == n_buf_size)
    {
        return -1;
    }

    while (n_remain_len > 0)
    {
        n_ret = recv(h_socket,
                     p_buf,
                     n_remain_len,
                     0);

        if (SOCKET_ERROR == n_ret || 0 == n_ret)
        {
            return -1;   //接收错误就返回
        }

        p_buf += n_ret;
        n_recv_len += n_ret;
        n_remain_len -= n_ret;
    }

    if (n_recv_len != n_buf_size)
    {
        return -2;
    }

    return 0;
}


/*
 * 按块发送数据
 * 每次发送块大小 比如每次发送8k
 * arg1 socket
 * arg2 要发送缓冲区指针
 * arg3 要发送的数据大小
 * arg4 每次发送数据的块大小
 *
 * ret(-1) 错误  or 成功发送的字节数
*/
int Net_Tools::send_part(SOCKET h_socket, char* p_data,
                         int n_size, int n_part_size)
{
    //健壮性检查
    if(0 == p_data || 0 >= n_size || 0 >= n_part_size)
    {
        return -1;
    }

    int	n_ret = 0;
    int	n_remain_size = 0;  //剩余未发送数据
    int	n_send = 0;         //已经发生的数据总和
    int	n_send_count = 15;  //最大发送次数

    const char *p_buf = (char *)p_data;

    // 依次发送
    for (n_remain_size = n_size; n_remain_size >= n_part_size;
         n_remain_size -= n_part_size)
    {
        int n_count = 0;

        for (n_count = 0; n_count < n_send_count; n_count++)
        {
            //每次发送一个块大小
            n_ret = send(h_socket, p_buf, n_part_size, 0);

            if (n_ret > 0)  //充分考虑到每一次出错的情况
            {
                break;      //跳出内层for  避免过快引发混乱
            }

        }
        if (n_count == n_send_count) //如果已经发了15次 直接报错
        {
            return -1;
        }

        n_send += n_ret;        // 完成数据的赋值后继续大循环
        p_buf += n_part_size;   // 移动数据指针
        Sleep(10);              // 必要的Sleep,过快会引起控制端数据混乱
    }
    // 发送最后的部分
    if (n_remain_size > 0)
    {
        int n_count = 0;

        //假设了最坏的情况 一点渣渣数据发送15次
        for (n_count = 0; n_count < n_send_count; n_count++)
        {
            //发送剩余数据 ret是成功发送数据的长度
            n_ret = send(h_socket, p_buf, n_remain_size, 0);

            if (n_ret > 0)
            {
                break;         //成功发送直接跳出循环
            }
        }

        //如果真的发送了15次  直接报错
        if (n_count == n_send_count)
        {
            return -1;
        }

        n_send += n_ret;	//已发送的数据累加
    }

    //如果完全发送  直接返回字节数
    if (n_send == n_size)
    {
        return n_send;
    }

    return SOCKET_ERROR;
}
