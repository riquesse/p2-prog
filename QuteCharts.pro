#-------------------------------------------------
#
# Project created by QtCreator 2022-06-26T12:19:30
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuteCharts
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
        Model/chartitem.cpp \
        Model/slice.cpp \
        Model/barset.cpp \
        Model/line.cpp \
        Model/chart.cpp \
        Model/piechart.cpp \
        Model/cartesianchart.cpp \
        Model/barchart.cpp \
        Model/linechart.cpp \
        Model/Interface/model.cpp \
        Model/Interface/piemodel.cpp \
        Model/Interface/cartesianmodel.cpp \
        View/chartmenu.cpp \
        View/mainwindow.cpp \
        View/customheader.cpp \
        View/tableview.cpp \
        View/editchartdetailsdialog.cpp \
        View/customlineseries.cpp \
        View/Managers/chartmanager.cpp \
        View/Managers/piechartmanager.cpp \
        View/Managers/cartesianchartmanager.cpp \
        View/Managers/linechartmanager.cpp \
        View/Managers/barchartmanager.cpp \
        Utility/jsonchecker.cpp \
        Utility/colorgenerator.cpp

HEADERS += \
        Model/chartitem.h \
        Model/slice.h \
        Model/barset.h \
        Model/line.h \
        Model/chart.h \
        Model/piechart.h \
        Model/cartesianchart.h \
        Model/barchart.h \
        Model/linechart.h \
        Model/Interface/model.h \
        Model/Interface/piemodel.h \
        Model/Interface/cartesianmodel.h \
        View/chartmenu.h \
        View/mainwindow.h \
        View/customheader.h \
        View/tableview.h \
        View/editchartdetailsdialog.h \
        View/customlineseries.h \
        View/Managers/chartmanager.h \
        View/Managers/piechartmanager.h \
        View/Managers/cartesianchartmanager.h \
        View/Managers/linechartmanager.h \
        View/Managers/barchartmanager.h \
        Utility/jsonchecker.h \
        Utility/colorgenerator.h

RESOURCES += \
    resource.qrc
