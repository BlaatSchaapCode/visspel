MAKEFILES=make
include $(MAKEFILES)/make.mk

BUILD_DIR = bld/$(TARGET_OS)
OUT_DIR =   out/$(TARGET_OS)
OUT_EXE = $(OUT_DIR)/$(EXEPRE)visspel$(EXESUF) 



CXX_SRC += src/main.cpp
CXX_OBJ = $(CXX_SRC:%=$(BUILD_DIR)/%.o)

default: $(BUILD_DIR) | $(OUT_EXE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUT_EXE): $(CXX_OBJ)
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXX_OBJ) $(CXXFLAGS) $(LDFLAGS) -o$@

# asm source
$(BUILD_DIR)/%.s.o: %.s
	mkdir -p  $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p  $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p  $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

################################################################################
# Dependencies
################################################################################
-include $(wildcard $(BUILD_DIR)/*.d)
