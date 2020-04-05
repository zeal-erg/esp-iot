
# Component Makefile

# This Makefile can be left empty. By default, it will take the sources in the
# src/ directory, compile them and link them into lib(subdirectory_name).a
# in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.

# add app path
COMPONENT_ADD_INCLUDEDIRS := $(APP_BIN_NAME)/include
COMPONENT_SRCDIRS := $(APP_BIN_NAME)/src

CFLAGS += -w
CFLAGS += \
	-DAPP_BIN_NAME=\"$(APP_BIN_NAME)\" \
	-DUSER_SW_VER=\"$(USER_SW_VER)\"

