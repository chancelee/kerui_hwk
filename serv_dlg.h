#ifndef SERV_DLG_H
#define SERV_DLG_H

#include <QDialog>

namespace Ui {
class Serv_Dlg;
}

class Serv_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit Serv_Dlg(QWidget *parent = 0);
    ~Serv_Dlg();

private:
    Ui::Serv_Dlg *ui;
};

#endif // SERV_DLG_H
