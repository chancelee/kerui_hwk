/********************************************************************************
** Form generated from reading UI file 'cmd_dlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMD_DLG_H
#define UI_CMD_DLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Cmd_Dlg
{
public:
    QPushButton *btn_cmd;
    QLineEdit *le_cmd;
    QTextEdit *te_cmd;

    void setupUi(QDialog *Cmd_Dlg)
    {
        if (Cmd_Dlg->objectName().isEmpty())
            Cmd_Dlg->setObjectName(QStringLiteral("Cmd_Dlg"));
        Cmd_Dlg->resize(541, 406);
        btn_cmd = new QPushButton(Cmd_Dlg);
        btn_cmd->setObjectName(QStringLiteral("btn_cmd"));
        btn_cmd->setGeometry(QRect(410, 40, 101, 41));
        le_cmd = new QLineEdit(Cmd_Dlg);
        le_cmd->setObjectName(QStringLiteral("le_cmd"));
        le_cmd->setGeometry(QRect(50, 40, 331, 41));
        te_cmd = new QTextEdit(Cmd_Dlg);
        te_cmd->setObjectName(QStringLiteral("te_cmd"));
        te_cmd->setGeometry(QRect(50, 110, 461, 261));
        QFont font;
        font.setFamily(QStringLiteral("Comic Sans MS"));
        te_cmd->setFont(font);

        retranslateUi(Cmd_Dlg);

        QMetaObject::connectSlotsByName(Cmd_Dlg);
    } // setupUi

    void retranslateUi(QDialog *Cmd_Dlg)
    {
        Cmd_Dlg->setWindowTitle(QApplication::translate("Cmd_Dlg", "Dialog", Q_NULLPTR));
        btn_cmd->setText(QApplication::translate("Cmd_Dlg", "\346\211\247\350\241\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Cmd_Dlg: public Ui_Cmd_Dlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMD_DLG_H
