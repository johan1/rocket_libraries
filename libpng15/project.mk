# Required
NAME := png15
TYPE := static

INCLUDES += -I$(PROJECT_ROOT)/src/include

# Deploy
EXPORT_SYSTEM_LIB := 1
EXPORT_INCLUDE_FOLDER_NAME := png15
EXPORT_LIBNAME := png15
EXPORT_LIBVERSION := 1.15.3

CSOURCES := \
		pngerror.c \
		pngread.c \
		pngwutil.c \
		pngget.c \
		pngtest.c \
		pngset.c \
		pngwrite.c \
		pngpread.c \
		pngrio.c \
		pngtrans.c \
		pngwio.c \
		pngmem.c \
		pngrutil.c \
		png.c \
		pngrtran.c \
		pngwtran.c
