#include <memory.h>
#include "pc_buffer.h"


#define SAFE_MEM(x) if(0 != x)      \
                    {               \
                        delete[] x; \
                        x = 0;      \
                    }               \


#define INIT_SIZE 20

//初始化分配20个字节控件大小
Pc_Buffer::Pc_Buffer()
{
    this->init();
}

Pc_Buffer::Pc_Buffer(Pc_Buffer &obj)
{
    this->init();
    *this = obj;
}

Pc_Buffer::Pc_Buffer(void *p_data, int n_size)
{
    this->init();
    this->set_data(p_data, n_size);
}

Pc_Buffer::~Pc_Buffer()
{
    this->m_n_buf_size = 0;
        this->m_n_mem_size = 0;
    this->m_n_remain_size = 0;

    SAFE_MEM(this->m_buf);
}

Pc_Buffer &Pc_Buffer::operator=(Pc_Buffer &obj)
{
    this->set_data(obj.get_buffer(), 
                   obj.get_buffer_len());
    
    return *this;
}

bool Pc_Buffer::operator==(Pc_Buffer &obj)
{
    int n_ret = 0;
    
    if(this->m_n_buf_size != obj.get_buffer_len()
    || this->m_n_mem_size != obj.get_mem_size())
    {
        return false;  
    }
    
    n_ret = memcmp(this->m_buf, 
                   obj.get_buffer(), 
                   this->m_n_buf_size);
    
    if(0 != n_ret)
    {
        return false;
    }
    
    return true;
}

bool Pc_Buffer::operator!=(Pc_Buffer &obj)
{
    return !(this->operator ==(obj));
}

void Pc_Buffer::init()
{
    this->m_buf = 0;
    this->m_n_buf_size = 0;

    //初始化空间 顺便清0
    this->m_n_mem_size = INIT_SIZE;
    this->m_n_remain_size = INIT_SIZE;
    this->m_buf = alloc_buffer(INIT_SIZE);
}

bool Pc_Buffer::read(void *p_data, int n_read_size)
{
    if(n_read_size > this->m_n_buf_size)
    {
        return false;
    }

    //拷贝数据到 p_data
    memcpy(p_data,
           this->m_buf,
           n_read_size);

    //剩余数据移动到起始位置
    memcpy(this->m_buf,
           this->m_buf + n_read_size,
           this->m_n_buf_size - n_read_size);

    this->m_n_buf_size = this->m_n_buf_size - n_read_size;
    this->m_n_remain_size =
            this->m_n_mem_size - this->m_n_buf_size;

    return true;
}

void Pc_Buffer::append(void* p_data, int n_data_size)
{
    //添加数据大于当前剩余空间
    if(n_data_size > this->m_n_remain_size)
    {
        char* new_buf =
              this->alloc_buffer(this->m_n_buf_size + n_data_size);

        //拷贝当前数据和新增数据
        memcpy(new_buf, this->m_buf, this->m_n_buf_size);
        memcpy(new_buf + this->m_n_buf_size,
               p_data,
               n_data_size);

        SAFE_MEM(this->m_buf);
        this->m_buf = new_buf;
        this->m_n_mem_size += n_data_size;
    }
    else
    {
        memcpy(this->m_buf + this->m_n_buf_size,
               p_data,
               n_data_size);
    }

    //更新数据占用空间和剩余空间
    this->m_n_buf_size += n_data_size;
    this->m_n_remain_size =
          this->m_n_mem_size - this->m_n_buf_size;

}

int Pc_Buffer::set_data(void *p_data, int n_data_size)
{
    //如果相等不做处理
    if(n_data_size == this->m_n_buf_size
    && 0 == memcmp(p_data, this->m_buf, n_data_size))
    {
        return 0;
    }

    //如果要设置的数据长度 大于当前数据内存长度
    if(n_data_size > this->m_n_mem_size)
    {
        SAFE_MEM(this->m_buf);

        //申请空间 复制源数据到当前
        this->m_buf = this->alloc_buffer(n_data_size);
        memcpy(this->m_buf, p_data, n_data_size);

        this->m_n_mem_size = n_data_size;
        this->m_n_buf_size = n_data_size;
        this->m_n_remain_size = 0;
        return 0;
    }

    //当前空间清0 拷贝源数据
    memset(this->m_buf, 0, this->m_n_buf_size);
    memcpy(this->m_buf, p_data, n_data_size);

    //修改剩余空间  占用空间
    this->m_n_buf_size = n_data_size;
    this->m_n_remain_size = this->m_n_mem_size - n_data_size;

    return 0;
}

char *Pc_Buffer::get_buffer()
{
    return this->m_buf;
}

int Pc_Buffer::get_mem_size()
{
    return this->m_n_mem_size;  
}

int Pc_Buffer::get_buffer_len()
{
    return this->m_n_buf_size;
}

char *Pc_Buffer::alloc_buffer(int n_buf_size)
{
    return new char[n_buf_size]();
}
