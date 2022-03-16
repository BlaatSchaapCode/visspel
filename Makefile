#CXX_SRC += src/main.cpp
CXX_SRC = $(shell find src -iname "*.cpp")


MAKEFILES=make
include $(MAKEFILES)/make.mk



