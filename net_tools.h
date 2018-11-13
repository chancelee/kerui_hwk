#ifndef NET_TOOLS_H
#define NET_TOOLS_H

#include <winsock2.h>

#define PART_SIZE (1024 * 8)

class Net_Tools
{
public:
    Net_Tools();


public:
    static bool Select(SOCKET h_socket,
                       bool b_read = true,
                       int n_time_out = 100);

public:
    static int send_buf(SOCKET h_socket,
                        char* p_buf,
                        int n_buf_size);

    static int recv_buf(SOCKET h_socket,
                        char* p_buf,
                        int n_buf_size);

private:
    static int send_part(SOCKET h_socket,
                         char* p_data,
                         int n_size,
                         int n_part_size = PART_SIZE);
};

#endif // NET_TOOLS_H
