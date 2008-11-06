TEMPLATE = app
TARGET = tulip_plugins
QT += core \
    gui \
    script
HEADERS += tests/HistogramWidgetTest.h \
    tests/CurveWidgetTest.h \
    tests/AddDeleteTest.h \
    tests/ColorGraphicTest.h \
    QData.h \ 
    #Application.h \
    tests/DataTest.h \
    tests/ModelTest.h \
    tests/ScriptWidgetTest.h \
    ScriptViewer.h \
    CurveGroup.h \
    Data.h \
    Graphic.h \
    HistogramGroup.h \
    IData.h \
    IModel.h \
    Model.h \
    Observable.h \
    Observer.h \
    QGraphic.h \
    Viewer.h \
    DataScriptClass.h
SOURCES += tests/HistogramWidgetTest.cpp \
    tests/CurveWidgetTest.cpp \
    ScriptViewer.cpp \ 
    # DataScriptClass.cpp \
	#Application.cpp \
    tests/DataTest.cpp \
    tests/ModelTest.cpp \
    tests/ScriptWidgetTest.cpp \
    tests/testObserver.cpp \
    tests/testRunner.cpp \
    tests/AddDeleteTest.cpp \
    tests/ColorGraphicTest.cpp \
    CurveGroup.cpp \
    HistogramGroup.cpp \
    Model.cpp \
    Observable.cpp \
    Observer.cpp \
    Viewer.cpp
RESOURCES += 
LIBS += -L/net/cremi/rnappee/root/lib
LIBS += -lcppunit
INCLUDEPATH += /net/cremi/rnappee/root/include
FORMS += ScriptViewer.ui
