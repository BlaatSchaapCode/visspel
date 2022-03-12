COMPILER?=GCC

ifeq ($(COMPILER),GCC) 
	CC=$(PREFIX)gcc
	CXX=$(PREFIX)g++
	LD?=$CXX
else
ifeq ($(COMPILER),CLANG) 
	CC=$(PREFIX)clang
	CXX=$(PREFIX)clang++
	LD?=$CXX
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



