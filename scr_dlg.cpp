//#include "settings.h"
#include "scr_dlg.h"
#include "ui_scr_dlg.h"
#include "net_tools.h"
#include <QPainter>

Scr_Dlg::Scr_Dlg(SOCKET h_socket, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Scr_Dlg)
{
    ui->setupUi(this);

    this->m_b_draw = false;
    this->m_img = 0;
    this->m_img.reset(new QImage);

    this->m_socket = 0;
    this->m_socket = h_socket;
}

Scr_Dlg::~Scr_Dlg()
{
    delete ui;
}

void Scr_Dlg::dps_data(QByteArray buf)
{
    //显示图片数据
    char* p_buf = buf.data();
    int n_width = *(int*)p_buf;
    int n_height = *((int*)p_buf+1);

    QImage img(n_width, n_height, QImage::Format_ARGB32);
    memcpy(img.bits() , p_buf + 8 , 4* n_width *n_height);

    *(this->m_img) = img;
    this->m_b_draw = true;

    update();

    //发送数据让下一帧的画面传过来
    Data_Head data_head(PSC_SCREEN, PSC_SCR_DATA);
    Net_Tools::send_buf(this->m_socket,
                        (char*)&data_head,
                        sizeof(Data_Head));
}

void Scr_Dlg::paintEvent(QPaintEvent *event)
{
    if (!this->m_b_draw)
    {
        return;
    }

    //在当前窗口显示按比例缩放的图
    QPainter painter(this);
    QImage img_show = m_img->scaled(width(), height());
    painter.drawImage(0, 0, img_show);

    //this->m_b_draw = false;
}
