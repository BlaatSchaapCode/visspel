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



ifeq ($(BUILD_TYPE),DEBUG)
	CXXFLAGS += -g  # Generate debug information (inside the binary)
	CXXFLAGS += -O0 # Disable optimisation
else 
	CXXFLAGS += -O2 # Optimise code
	CXXFLAGS += -D_FORTIFY_SOURCE=2
endif



