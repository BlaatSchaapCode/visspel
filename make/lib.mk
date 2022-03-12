LDFLAGS += 	$(shell $(PREFIX)pkg-config --libs   sdl2)
INCLUDES += $(shell $(PREFIX)pkg-config --cflags sdl2)

LDFLAGS += 	$(shell $(PREFIX)pkg-config --libs   libpng)
INCLUDES += $(shell $(PREFIX)pkg-config --cflags libpng)
