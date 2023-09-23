QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
CONFIG += console;
SOURCES += \
    DataDirectory/formarchitecture.cpp \
    DataDirectory/formbaserelocationtable.cpp \
    DataDirectory/formboundimport.cpp \
    DataDirectory/formcertificatetable.cpp \
    DataDirectory/formclrruntimeheader.cpp \
    DataDirectory/formdebug.cpp \
    DataDirectory/formdelayimportdescriptor.cpp \
    DataDirectory/formexceptiontable.cpp \
    DataDirectory/formexporttable.cpp \
    DataDirectory/formglobalptr.cpp \
    DataDirectory/formiat.cpp \
    DataDirectory/formimporttable.cpp \
    DataDirectory/formloadconfigtable.cpp \
    DataDirectory/formresourcetable.cpp \
    DataDirectory/formtlstable.cpp \
    document/buffer/qfilebuffer.cpp \
    document/buffer/qhexbuffer.cpp \
    document/buffer/qmemorybuffer.cpp \
    document/buffer/qmemoryrefbuffer.cpp \
    document/commands/hexcommand.cpp \
    document/commands/insertcommand.cpp \
    document/commands/removecommand.cpp \
    document/commands/replacecommand.cpp \
    document/qhexcursor.cpp \
    document/qhexdocument.cpp \
    document/qhexmetadata.cpp \
    document/qhexrenderer.cpp \
    formdatadirectory.cpp \
    formeditpefile.cpp \
    formfileheader.cpp \
    formmsdosheader.cpp \
    formntheaders.cpp \
    formoptionalheader.cpp \
    formrvatofoa.cpp \
    formsectionheader.cpp \
    formsections.cpp \
    main.cpp \
    pedumpmainwindow.cpp \
    peutils.cpp \
    qhexview.cpp

HEADERS += \
    DataDirectory/formarchitecture.h \
    DataDirectory/formbaserelocationtable.h \
    DataDirectory/formboundimport.h \
    DataDirectory/formcertificatetable.h \
    DataDirectory/formclrruntimeheader.h \
    DataDirectory/formdebug.h \
    DataDirectory/formdelayimportdescriptor.h \
    DataDirectory/formexceptiontable.h \
    DataDirectory/formexporttable.h \
    DataDirectory/formglobalptr.h \
    DataDirectory/formiat.h \
    DataDirectory/formimporttable.h \
    DataDirectory/formloadconfigtable.h \
    DataDirectory/formresourcetable.h \
    DataDirectory/formtlstable.h \
    antiDebug.h \
    antiDebug2.h \
    document/buffer/qfilebuffer.h \
    document/buffer/qhexbuffer.h \
    document/buffer/qmemorybuffer.h \
    document/buffer/qmemoryrefbuffer.h \
    document/commands/hexcommand.h \
    document/commands/insertcommand.h \
    document/commands/removecommand.h \
    document/commands/replacecommand.h \
    document/qhexcursor.h \
    document/qhexdocument.h \
    document/qhexmetadata.h \
    document/qhexrenderer.h \
    formdatadirectory.h \
    formeditpefile.h \
    formfileheader.h \
    formmsdosheader.h \
    formntheaders.h \
    formoptionalheader.h \
    formrvatofoa.h \
    formsectionheader.h \
    formsections.h \
    mapfile.h \
    pedumpmainwindow.h \
    peutils.h \
    qhexview.h

FORMS += \
    DataDirectory/formarchitecture.ui \
    DataDirectory/formbaserelocationtable.ui \
    DataDirectory/formboundimport.ui \
    DataDirectory/formcertificatetable.ui \
    DataDirectory/formclrruntimeheader.ui \
    DataDirectory/formdebug.ui \
    DataDirectory/formdelayimportdescriptor.ui \
    DataDirectory/formexceptiontable.ui \
    DataDirectory/formexporttable.ui \
    DataDirectory/formglobalptr.ui \
    DataDirectory/formiat.ui \
    DataDirectory/formimporttable.ui \
    DataDirectory/formloadconfigtable.ui \
    DataDirectory/formresourcetable.ui \
    DataDirectory/formtlstable.ui \
    formdatadirectory.ui \
    formeditpefile.ui \
    formfileheader.ui \
    formmsdosheader.ui \
    formntheaders.ui \
    formoptionalheader.ui \
    formrvatofoa.ui \
    formsectionheader.ui \
    formsections.ui \
    pedumpmainwindow.ui

TRANSLATIONS += \
    PEDump_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
