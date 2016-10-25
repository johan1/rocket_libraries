# Required
NAME := glew
TYPE := static
TARGET_OPTIM := release

PLATFORMS := host i686-w64-mingw32

SOURCE_DIR := $(PROJECT_ROOT)/glew-2.0.0/src
INCLUDES += -I$(PROJECT_ROOT)/glew-2.0.0/include
DEFINES += -DGLEW_NO_GLU

CSOURCES := \
	glew.c

ifeq ($(TARGET),i686-w64-mingw32)
ifeq ($(TYPE),shared)
LDFLAGS += -nostdlib
endif
endif

# Deploy
EXPORT_INCLUDE_FOLDER_NAME := glew
EXPORT_LIBNAME := glew
EXPORT_LIBVERSION := 2.0.0
