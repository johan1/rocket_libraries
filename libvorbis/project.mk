# Required
NAME := vorbis
TYPE := static

SOURCE_DIR := $(PROJECT_ROOT)/src/lib

INCLUDES += -I$(PROJECT_ROOT)/src/include
INCLUDES += -I$(PROJECT_ROOT)/src/lib

CSOURCES := \
	analysis.c \
	bitrate.c \
	block.c \
	codebook.c \
	envelope.c \
	floor0.c \
	floor1.c \
	info.c \
	lookup.c \
	lpc.c \
	lsp.c \
	mapping0.c \
	mdct.c \
	psy.c \
	registry.c \
	res0.c \
	sharedbook.c \
	smallft.c \
	synthesis.c \
	vorbisenc.c \
	vorbisfile.c \
	window.c

# Deploy
EXPORT_SYSTEM_LIB := 1
EXPORT_INCLUDE_FOLDER_NAME := vorbis
EXPORT_LIBNAME := vorbis
EXPORT_LIBVERSION := 1.3.3
