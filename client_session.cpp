#include "client_session.h"

Client_Session::Client_Session()
{
    this->m_sock = 0;
    this->m_ser = {0};

    this->m_dps_thd = 0;

    this->m_last_time = 0;

    this->m_cmd_dlg = 0;
    this->m_scr_dlg = 0;
}

Client_Session::Client_Session(SOCKET h_sock, sockaddr_in new_ser)
{
    this->m_sock = 0;
    this->m_ser = {0};
    this->m_ser = new_ser;
    this->m_sock = h_sock;

    this->m_dps_thd = 0;

    this->m_cmd_dlg = 0;
    this->m_scr_dlg = 0;
}

Client_Session::~Client_Session()
{
    if(0 != this->m_sock)
    {
        closesocket(this->m_sock);
    }

    this->m_sock = 0;
    this->m_ser = {0};

    if(0 != this->m_cmd_dlg)
    {
        this->m_cmd_dlg->close();
    }
    if(0 != this->m_scr_dlg)
    {
        this->m_scr_dlg->close();
    }

    this->m_cmd_dlg.clear();
    this->m_scr_dlg.clear();

    this->m_dps_thd->setB_stop_recv(true);
    //this->m_dps_thd.clear();

    this->m_last_time = 0;
}
