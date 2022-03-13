LDFLAGS += 	$(shell $(PREFIX)pkg-config --libs   sdl2)
INCLUDES += $(shell $(PREFIX)pkg-config --cflags sdl2)

LDFLAGS += 	$(shell $(PREFIX)pkg-config --libs   libpng)
INCLUDES += $(shell $(PREFIX)pkg-config --cflags libpng)

LDFLAGS += 	$(shell $(PREFIX)pkg-config --libs   jsoncpp)
INCLUDES += $(shell $(PREFIX)pkg-config --cflags jsoncpp)

LDFLAGS += 	$(shell $(PREFIX)pkg-config --libs   cxxopts)
INCLUDES += $(shell $(PREFIX)pkg-config --cflags cxxopts)


# No pkg-config support for imgui
LDFLAGS += -limgui

# As catch2 is source only, there is no target specific version
# Thus we have no prefix here
LDFLAGS += 	$(shell pkg-config --libs   catch2)
INCLUDES += $(shell pkg-config --cflags catch2)

