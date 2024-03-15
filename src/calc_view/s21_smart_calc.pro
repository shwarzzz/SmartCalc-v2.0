QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../calc_model/calc_model.cc \
    ../calc_model/parser.cc \
    ../calc_model/converter.cc \
    ../calc_model/calculator.cc \
    ../calc_controller/calc_controller.cc \
    calc_view.cc \
    ../credit_model/credit_model.cc \
    ../credit_controller/credit_controller.cc \
    ../credit_view/credit_view.cc \
    main.cc \
    ../modules/qcustomplot.cc
HEADERS += \
    ../calc_model/calc_model.h \
    ../calc_model/parser.h \
    ../calc_model/converter.h \
    ../calc_model/calculator.h \
    ../calc_controller/calc_controller.h \
    calc_view.h \
    ../credit_model/credit_model.h \
    ../credit_controller/credit_controller.h \
    ../credit_view/credit_view.h \
    ../modules/qcustomplot.h
FORMS += \
    ../ui/calc_view.ui \
    ../ui/credit_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
