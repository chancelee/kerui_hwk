#ifndef CMD_DLG_H
#define CMD_DLG_H

#include <QDialog>
#include <winsock2.h>

namespace Ui
{
class Cmd_Dlg;
}

class Cmd_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit Cmd_Dlg(SOCKET h_socket, QWidget *parent = 0);
    ~Cmd_Dlg();

public:
    void append_data(QByteArray buf);

    void send_buf(QString str_out);

    //public:
    //    int ifs_cmd(unsigned char c_cmd_id, char *p_data);

    //signals:
    //    void sin_cmd_reply();
    //    void sin_cmd_recv(QString out_str);

private slots:
    //void on_btn_cmd_clicked();
    void on_le_cmd_returnPressed();

private:
    SOCKET m_sock;

private:
    Ui::Cmd_Dlg *ui;
};

#endif // CMD_DLG_H
