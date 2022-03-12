LDFLAGS += $(shell $(PREFIX)pkg-config --libs libusb-1.0)
LDFLAGS += -lpthread  

INCLUDES += $(shell $(PREFIX)pkg-config --cflags libusb-1.0)
