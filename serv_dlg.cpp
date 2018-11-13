#include <windows.h>
#include "serv_dlg.h"
#include "ui_serv_dlg.h"

Serv_Dlg::Serv_Dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Serv_Dlg)
{
    ui->setupUi(this);
}

Serv_Dlg::~Serv_Dlg()
{
    delete ui;
}

void Serv_Dlg::dps_data(QByteArray buf)
{
    //初始化服务结构体指针
    LPENUM_SERVICE_STATUS_PROCESS p_serv_info = 0;

    //指向获取的服务缓冲区 (存储服务信息结构体)
    p_serv_info = (LPENUM_SERVICE_STATUS_PROCESS)(buf.data());

    for(int n_index = 0; n_index < m_dw_ret_serv; n_index++)
    {
        QList<QStandardItem*> row_item;

        //进程标识符
        int n_id = (int)(p_serv_info->ServiceStatusProcess.dwProcessId);
        QStandardItem* p_id_item = 0;
        p_id_item = new QStandardItem(QString::number(n_id));

        //服务名
        QStandardItem* p_name_item = 0;
        QString name = QString::fromStdWString(p_serv_info->lpServiceName);
        p_name_item = new QStandardItem(name);

        //显示名称
        QString dis_name = QString::fromStdWString(p_serv_info->lpDisplayName);
        QStandardItem* p_dis_item = 0;
        p_dis_item = new QStandardItem(dis_name);

        //状态
        DWORD dw_status = p_serv_info->ServiceStatusProcess.dwCurrentState;
        QString status_str = m_p_status_lst->at(dw_status - 1);
        QStandardItem* p_status_item = 0;
        p_status_item = new QStandardItem(status_str);

        row_item << p_id_item      //标识符
                 << p_name_item    //服务名
                 << p_dis_item     //显示名称
                 << p_status_item; //状态

        //添加行数据
        this->m_model_serv->appendRow(row_item);
        p_serv_info++;
    }
}
