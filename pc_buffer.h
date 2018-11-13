#ifndef PC_BUFFER_H
#define PC_BUFFER_H

class Pc_Buffer
{
public:
    Pc_Buffer();
    Pc_Buffer(Pc_Buffer& obj);
    Pc_Buffer(void* p_data, int n_size);

    ~Pc_Buffer();

public:
   Pc_Buffer& operator=(Pc_Buffer& obj);

   bool operator==(Pc_Buffer& obj);
   bool operator!=(Pc_Buffer& obj);

public:
    void init();
    bool read(void* p_data/*inout*/, int n_read_size);
    void append(void* p_buf/*in*/, int n_buf_size);

public:
    int set_data(void* p_data, int n_size);

public:
    char* get_buffer();
    int get_buffer_len();
    int get_mem_size();

public:
    char* alloc_buffer(int n_buf_size);

private:
    int m_n_mem_size;       //内存空间
    int m_n_buf_size;       //可用空间
    int m_n_remain_size;    //剩余空间

private:
    char* m_buf;
};

#endif // PC_BUFFER_H
