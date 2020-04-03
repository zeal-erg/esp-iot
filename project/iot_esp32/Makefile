#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

IDF_PATH := $(abspath $(shell pwd)/../../esp-idf)
PROJECT_NAME := iot_esp32

EXTRA_COMPONENT_DIRS += $(abspath $(shell pwd)/iot_app)
EXTRA_COMPONENT_DIRS += $(abspath $(shell pwd)/iot_user_common)
EXTRA_COMPONENT_DIRS += $(abspath $(shell pwd)/iot_common)
EXTRA_COMPONENT_DIRS += $(abspath $(shell pwd)/iot_component)

include $(IDF_PATH)/make/project.mk
