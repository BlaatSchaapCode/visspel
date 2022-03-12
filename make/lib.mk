LDFLAGS += 	$(shell $(PREFIX)pkg-config --libs   sdl)
INCLUDES += $(shell $(PREFIX)pkg-config --cflags sdl)

LDFLAGS += 	$(shell $(PREFIX)pkg-config --libs   libpng)
INCLUDES += $(shell $(PREFIX)pkg-config --cflags libpng)
