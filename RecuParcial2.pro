QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -Wa,-mbig-ob

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L"C:\Users\Ing. Gadiel Pardo\Desktop\DLLs\DLLmuParser"
LIBS += -lDLLmuParser
INCLUDEPATH += "C:\Users\Ing. Gadiel Pardo\Desktop\DLLs\DLLmuParser"

LIBS += -L"C:\Users\Ing. Gadiel Pardo\Desktop\DLLs\DLLQCustom1.1\QcustomDLL"
LIBS += -l qcustomplotd2
INCLUDEPATH += "C:\Users\Ing. Gadiel Pardo\Desktop\DLLs\DLLQCustom1.1\QcustomDLL"
