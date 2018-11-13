/********************************************************************************
** Form generated from reading UI file 'ps_m_wnd.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PS_M_WND_H
#define UI_PS_M_WND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PS_M_Wnd
{
public:
    QWidget *centralWidget;
    QPushButton *btn_cmd;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *btn_scr;
    QPushButton *pushButton_5;
    QPushButton *btn_proc;
    QPushButton *pushButton_7;
    QListView *tv_info;
    QTableView *tv_host;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PS_M_Wnd)
    {
        if (PS_M_Wnd->objectName().isEmpty())
            PS_M_Wnd->setObjectName(QStringLiteral("PS_M_Wnd"));
        PS_M_Wnd->resize(724, 686);
        centralWidget = new QWidget(PS_M_Wnd);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btn_cmd = new QPushButton(centralWidget);
        btn_cmd->setObjectName(QStringLiteral("btn_cmd"));
        btn_cmd->setGeometry(QRect(20, 20, 75, 51));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(530, 20, 75, 51));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(430, 20, 75, 51));
        btn_scr = new QPushButton(centralWidget);
        btn_scr->setObjectName(QStringLiteral("btn_scr"));
        btn_scr->setGeometry(QRect(130, 20, 75, 51));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(230, 20, 75, 51));
        btn_proc = new QPushButton(centralWidget);
        btn_proc->setObjectName(QStringLiteral("btn_proc"));
        btn_proc->setGeometry(QRect(320, 20, 75, 51));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(630, 20, 75, 51));
        tv_info = new QListView(centralWidget);
        tv_info->setObjectName(QStringLiteral("tv_info"));
        tv_info->setGeometry(QRect(20, 500, 691, 121));
        tv_host = new QTableView(centralWidget);
        tv_host->setObjectName(QStringLiteral("tv_host"));
        tv_host->setGeometry(QRect(20, 90, 691, 401));
        PS_M_Wnd->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PS_M_Wnd);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 724, 22));
        PS_M_Wnd->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PS_M_Wnd);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PS_M_Wnd->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PS_M_Wnd);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PS_M_Wnd->setStatusBar(statusBar);

        retranslateUi(PS_M_Wnd);

        QMetaObject::connectSlotsByName(PS_M_Wnd);
    } // setupUi

    void retranslateUi(QMainWindow *PS_M_Wnd)
    {
        PS_M_Wnd->setWindowTitle(QApplication::translate("PS_M_Wnd", "Pc_Share by \345\210\230\344\270\200\345\210\200", Q_NULLPTR));
        btn_cmd->setText(QApplication::translate("PS_M_Wnd", "cmd", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("PS_M_Wnd", "\346\263\250\345\206\214\350\241\250\347\256\241\347\220\206", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("PS_M_Wnd", "\346\234\215\345\212\241\347\256\241\347\220\206", Q_NULLPTR));
        btn_scr->setText(QApplication::translate("PS_M_Wnd", "\345\261\217\345\271\225\347\233\221\346\216\247", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("PS_M_Wnd", "\346\226\207\344\273\266\347\256\241\347\220\206", Q_NULLPTR));
        btn_proc->setText(QApplication::translate("PS_M_Wnd", "\350\277\233\347\250\213\347\256\241\347\220\206", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("PS_M_Wnd", "\347\224\237\346\210\220\346\234\215\345\212\241\347\253\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PS_M_Wnd: public Ui_PS_M_Wnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PS_M_WND_H
