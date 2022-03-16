CXX_SRC 	= $(shell find src -iname "*.cpp")
CXX_HEADERS = $(shell find src -iname "*.hpp")

BUILD_TYPE?=debug

ifeq ($(BUILD_TYPE),debug)
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


BUILD_DIR = bld/$(TARGET_OS)/$(BUILD_TYPE)
OUT_DIR =   out/$(TARGET_OS)/$(BUILD_TYPE)
OUT_EXE = $(OUT_DIR)/$(EXEPRE)visspel$(EXESUF) 

CXX_OBJ = $(CXX_SRC:%=$(BUILD_DIR)/%.o)



default: $(OUT_EXE)

$(OUT_EXE): $(CXX_OBJ)
	$(MKDIR_P) $(OUT_DIR)
	$(LINK) $(CXX_OBJ) $(CXXFLAGS) $(LDFLAGS) -o$@

# asm source
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P)  $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P)  $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P)  $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) $(OUT_EXE)

################################################################################
# Dependencies
################################################################################
-include $(wildcard $(BUILD_DIR)/*.d)
