#-------------------------------------------------
#
# Project created by QtCreator 2018-11-01T15:15:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Q_Pc_Share
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        ps_m_wnd.cpp \
    dps_thd.cpp \
    ps_socket.cpp \
    net_tools.cpp \
    cmd_dlg.cpp \
    client_session.cpp \
    scr_dlg.cpp \
    ps_func.cpp \
    heart_thd.cpp \
    pc_buffer.cpp \
    serv_dlg.cpp

HEADERS += \
        ps_m_wnd.h \
    settings.h \
    dps_thd.h \
    ps_socket.h \
    net_tools.h \
    cmd_dlg.h \
    client_session.h \
    scr_dlg.h \
    ps_func.h \
    heart_thd.h \
    pc_buffer.h \
    serv_dlg.h

FORMS += \
        ps_m_wnd.ui \
    cmd_dlg.ui \
    scr_dlg.ui \
    serv_dlg.ui

LIBS += -lws2_32

RESOURCES += \
    res.qrc
