TEMPLATE = app
#CONFIG += console -std=c++14
#CONFIG += console -std=c++1y
CONFIG += console -std=c++17 -fgnu-tm
CONFIG -= qt app_bundle

#QMAKE_CXXFLAGS += -std=c++14 -Wall -Wextra -pedantic
#QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -pedantic
QMAKE_CXXFLAGS += -std=c++17 -fgnu-tm -Wall -Wextra -pedantic

INCLUDEPATH += ../../include
INCLUDEPATH += ../../test
INCLUDEPATH += C:/local/boost_1_59_0

SOURCES += ./main.cpp
