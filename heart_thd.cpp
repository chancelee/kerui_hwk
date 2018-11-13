#include "heart_thd.h"

#define TIME_INVL 10000

Heart_thd::Heart_thd(QMap<SOCKET, Client_Session *> *cs_map)
{
    this->m_cs_map = cs_map;
    this->m_b_stop_check = false;
}

void Heart_thd::run()
{
    while(!this->m_b_stop_check)
    {
        Sleep(TIME_INVL);
        this->check_heart();
    }
}

//遍历检测主机连接是否超时 超时就下线
int Heart_thd::check_heart()
{
    QTime time = QTime::currentTime();
    int n_cur_mec = time.msecsSinceStartOfDay();

    QMap<SOCKET, Client_Session*>::Iterator  it;

    for(it = this->m_cs_map->begin(); it != this->m_cs_map->end(); it++)
    {
        if(n_cur_mec - (it.value())->m_last_time > TIME_INVL)
        {
            emit sin_dis_conn(it.value());
        }
    }
}
