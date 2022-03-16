HOST_OS=$(shell uname)

# Under MSYS, uname returns a string like MINGW64_NT-10.0-19043
# We are not interested in the version, so we replace the string here
ifneq (,$(findstring MINGW64,$(HOST_OS)))
	HOST_OS=MINGW64
endif

ifneq (,$(findstring MINGW32,$(HOST_OS)))
        HOST_OS=MINGW32
endif

ifneq (,$(findstring MSYS_NT,$(HOST_OS)))
        HOST_OS=MSYS_NT
endif


TARGET_OS?=$(HOST_OS)

$(info HOST:   $(HOST_OS))
$(info TARGET: $(TARGET_OS))

ifeq ($(TARGET_OS),MINGW64)
	PREFIX=x86_64-w64-mingw32-
	EXESUF=.exe
endif

ifeq ($(TARGET_OS),MINGW32)
	PREFIX=i686-w64-mingw32-
	EXESUF=.exe
endif

ifeq ($(TARGET_OS),MSYS_NT)
	EXESUF=.exe
endif

