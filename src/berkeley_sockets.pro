TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        application.cpp \
        business_logic/business_logic.cpp \
        business_logic/string_extensions.cpp \
        communicate/communicator.cpp \
        communicate/tcp_client.cpp \
        communicate/tcp_server.cpp \
        communicate/udp_client.cpp \
        communicate/udp_server.cpp \
        main.cpp

HEADERS += \
    application.h \
    business_logic/business_logic.h \
    business_logic/string_extensions.h \
    communicate/communicator.h \
    communicate/tcp_client.h \
    communicate/tcp_server.h \
    communicate/udp_client.h \
    communicate/udp_server.h

LIBS += \
-pthread \
