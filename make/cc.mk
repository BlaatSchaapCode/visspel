COMPILER?=GCC

ifeq ($(COMPILER),GCC) 
	CC=$(PREFIX)gcc
	CXX=$(PREFIX)g++
	LINK=$(CXX)
else
ifeq ($(COMPILER),CLANG) 
	CC=$(PREFIX)clang
	CXX=$(PREFIX)clang++
	LINK=$(CXX)
endif
endif

CXXFLAGS += -Werror
CXXFLAGS += -Wall

# For GCC, gnu++23 and gnu++2b are equivalent, but clang only accepts 2b
#CXXFLAGS += --std=gnu++23
CXXFLAGS += --std=gnu++2b

CFLAGS += -Werror
CFLAGS += -Wall
CFLAGS += --std=gnu2x

ifeq ($(BUILD_TYPE),DEBUG)
	CXXFLAGS += -g  # Generate debug information (inside the binary)
	CXXFLAGS += -O0 # Disable optimisation
	CFLAGS += -g  # Generate debug information (inside the binary)
	CFLAGS += -O0 # Disable optimisation
else 
	CXXFLAGS += -O2 # Optimise code
	CXXFLAGS += -D_FORTIFY_SOURCE=2
	CFLAGS += -O2 # Optimise code
	CFLAGS += -D_FORTIFY_SOURCE=2
endif


################################################################################
## Add verbose option													       #
################################################################################
V ?= 0
ACTUAL_CC := $(CC)
ACTUAL_CXX := $(CXX)
ACTUAL_AS := $(AS)
ACTUAL_AR := $(AR)
ACTUAL_LINK := $(LINK)


CC_0 =  @echo "Compiling     $<..."; $(ACTUAL_CC)
CC_1 =  $(ACTUAL_CC)
CC =    $(CC_$(V))

CXX_0 = @echo "Compiling     $<..."; $(ACTUAL_CXX)
CXX_1 = $(ACTUAL_CXX)
CXX =   $(CXX_$(V))

AS_0 =  @echo "Assembling    $<..."; $(ACTUAL_AS)
AS_1 =  $(ACTUAL_AS)
AS =    $(AS_$(V))

AR_0 =  @echo "Archiving     $@..."; $(ACTUAL_AR)
AR_1 =  $(ACTUAL_AR)
AR =    $(AR_$(V))

LINK_0 =@echo "Linking       $@..."; $(ACTUAL_LINK)
LINK_1 =$(ACTUAL_LINK)
LINK =  $(LINK_$(V))

MKDIR_P0 = @mkdir -p
MKDIR_P1 = mkdir -p
MKDIR_P = $(MKDIR_P$(V))

