#ifndef PS_M_WND_H
#define PS_M_WND_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QStandardItemModel>
#include "ps_socket.h"

struct Client_Session;

namespace Ui
{
    class PS_M_Wnd;
}

class PS_M_Wnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit PS_M_Wnd(QWidget *parent = 0);
    ~PS_M_Wnd();

private slots:
    void on_act_cmd_triggered();
    void on_act_scr_triggered();

public slots:
    void slot_online(Line_Data* p_data);
    void slot_disconn(Client_Session* p_cs);

    void slot_create_dlg(Client_Session* p_cs, int n_type);
    void slot_recv_data(Client_Session* p_cs, int n_type, QByteArray buf);

public:
    SOCKET get_sel_sock();    
    
private:
    void init_table();

private:
    Ui::PS_M_Wnd *ui;

private:
    Ps_Socket* m_p_ps_sock;

private:
    QSharedPointer<QStandardItemModel> m_tv_model;
};

#endif // PS_M_WND_H
