#ifndef SCR_DLG_H
#define SCR_DLG_H
#include "settings.h"
#include <QImage>
#include <QDialog>
#include <QByteArray>

namespace Ui
{
    class Scr_Dlg;
}

class Scr_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit Scr_Dlg(SOCKET h_socket, QWidget *parent = 0);
    ~Scr_Dlg();

public:
    void dps_data(QByteArray buf);

public:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Scr_Dlg *ui;

private:
    bool m_b_draw;
    QSharedPointer<QImage> m_img;

private:
    SOCKET m_socket;

};

#endif // SCR_DLG_H
