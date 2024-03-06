QT -= gui
QT+=network
CONFIG += c++11 console
CONFIG -= app_bundle

QMAKE_CXXFLAGS_RELEASE = -O3

#LIBS += -lusb-1.0

GCC_OUTPUT = $$system(gcc --version)

message("$$GCC_OUTPUT")

SOURCES += \
        main.cpp \
        gpio.cpp \
        server.cpp \

SOURCES += \
        readData.cpp 

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#HEADERS += \
#	main.h 

HEADERS += \
	gpio.h \
	server.h \
	readData.h \
