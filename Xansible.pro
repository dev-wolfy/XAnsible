#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T09:13:14
#
#-------------------------------------------------

QT       += core gui svg xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Xansible
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

CONFIG += c++11

SOURCES += \
        apropos.cpp \
        hostgroup.cpp \
        main.cpp \
        newhostform.cpp \
        newplaybookform.cpp \
        newroleform.cpp \
        newtaskform.cpp \
        p_role.cpp \
        playbook.cpp \
        tabpageedit.cpp \
        xansible.cpp

HEADERS += \
        apropos.h \
        hostgroup.h \
        newhostform.h \
        newplaybookform.h \
        newroleform.h \
        newtaskform.h \
        p_role.h \
        playbook.h \
        tabpageedit.h \
        xansible.h

FORMS += \
        apropos.ui \
        newhostform.ui \
        newplaybookform.ui \
        newroleform.ui \
        newtaskform.ui \
        tabpageedit.ui \
        xansible.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

DISTFILES +=
