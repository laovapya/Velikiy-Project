TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_INCDIR += Headers
QMAKE_LIBDIR += ../velikiy/Libs
QMAKE_LIBS += libglfw3 libgdi32
QMAKE_LFLAGS += -static

SOURCES += \
        Source/Camera.cpp \
        Source/Cone.cpp \
        Source/Controller.cpp \
        Source/Cube.cpp \
        Source/Cylinder.cpp \
        Source/EBO.cpp \
        Source/main.cpp \
        Source/ObjectManager.cpp \
        Source/SceneRenderer.cpp \
        Source/Shader.cpp \
        Source/Shape.cpp \
        Source/VAO.cpp \
        Source/VBO.cpp \
        Source/VertexData.cpp \
        Source/glad.c
