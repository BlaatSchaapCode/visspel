
# If the OS is not set, set it to uname
ifeq ($(OS),)
	OS=$(shell uname)
endif

TARGET_OS?=$(OS)

$(info HOST:   $(OS))
$(info TARGET: $(TARGET_OS))

ifeq ($(TARGET_OS),Windows_NT)
	PREFIX=x86_64-w64-mingw32-
	EXESUF=.exe
endif


