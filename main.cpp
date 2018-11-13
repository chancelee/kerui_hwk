#include "ps_m_wnd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PS_M_Wnd w;

    w.show();

    return a.exec();
}
