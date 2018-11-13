#include <QTextCodec>
#include "settings.h"
#include "cmd_dlg.h"
#include "ui_cmd_dlg.h"
#include "net_tools.h"

Cmd_Dlg::Cmd_Dlg(SOCKET h_socket, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cmd_Dlg)
{
    ui->setupUi(this);

    this->m_sock = h_socket;
}

Cmd_Dlg::~Cmd_Dlg()
{
    delete ui;
}

void Cmd_Dlg::append_data(QByteArray buf)
{
    //转码
    QTextCodec* q_text_code = QTextCodec::codecForName("gbk");
    QString str = q_text_code->toUnicode(buf.data(), buf.length());
    //QString str = QString::fromLocal8Bit(szBuf);

    ui->te_cmd->append(str);
}

void Cmd_Dlg::send_buf(QString str_out)
{
    Data_Head* p_data_head = 0;
    p_data_head = new Data_Head(PSC_CMD, PSC_CMD_DATA);

    //获取要申请缓冲区的大小
    int n_buf_size = sizeof(Data_Head) + str_out.size();

    //拷贝命令头  发送数据 到缓冲区
    char* p_send_buf = new char[n_buf_size]();
    memcpy(p_send_buf, p_data_head, sizeof(Data_Head));
    memcpy(p_send_buf + sizeof(Data_Head),
           str_out.toStdString().c_str(),
           str_out.size());

    Net_Tools::send_buf(m_sock, p_send_buf, n_buf_size);

    delete[] p_data_head;
    delete []p_send_buf;
}

//主控端这里只处理 REPLY(已经初始化完毕) DATA(接收数据)
//int Cmd_Dlg::ifs_cmd(unsigned char c_cmd_id, char *p_data)
//{
//    if(PSC_CMD_REPLY == c_cmd_id)
//    {
//        //this->show(); 子线程不能操作任何UI相关操作
//        emit sin_cmd_reply();
//    }
//    else if(PSC_CMD_DATA == c_cmd_id)
//    {
//        //ui->te_cmd->append(QString::fromLocal8Bit(p_data));
//        QString out_str = QString::fromLocal8Bit(p_data);
//        emit sin_cmd_recv(out_str);
//    }
//}

void Cmd_Dlg::on_le_cmd_returnPressed()
{
    ui->te_cmd->clear();

    QString cmd_str = ui->le_cmd->text();
    cmd_str += '\n';

    this->send_buf(cmd_str);
}

//void Cmd_Dlg::on_btn_cmd_clicked()
//{
//    //this->on_le_cmd_returnPressed();
//}
