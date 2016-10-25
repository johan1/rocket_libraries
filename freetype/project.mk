# Required
NAME := freetype
TYPE := static

SOURCE_DIR := $(PROJECT_ROOT)/src
INCLUDES += -I$(PROJECT_ROOT)/src/include

ifeq ($(TARGET),i686-w64-mingw32)
INCLUDES += -I$(PROJECT_ROOT)/src/builds/windows
DEFINES += "-DFT_CONFIG_CONFIG_H=<config/ftconfig.h>"
else
INCLUDES += -I$(PROJECT_ROOT)/src/builds/unix
DEFINES += "-DFT_CONFIG_CONFIG_H=<ftconfig.h>"
endif
INCLUDES += -I$(PROJECT_ROOT)/src/objs

DEFINES += -DFT_CONFIG_OPTION_USE_PNG

DEFINES += -DFT2_BUILD_LIBRARY
DEFINES += "-DFT_CONFIG_MODULES_H=<ftmodule.h>"

# Deploy
EXPORT_SYSTEM_LIB := 1
EXPORT_INCLUDE_FOLDER_NAME := freetype
EXPORT_LIBNAME := freetype
EXPORT_LIBVERSION := 2.5.2

CSOURCES := \
	src/base/ftdebug.c \
	src/base/ftinit.c \
	src/base/ftbase.c \
	src/base/ftbbox.c \
	src/base/ftbdf.c \
	src/base/ftbitmap.c \
	src/base/ftcid.c \
	src/base/ftfstype.c \
	src/base/ftgasp.c \
	src/base/ftglyph.c \
	src/base/ftgxval.c \
	src/base/ftlcdfil.c \
	src/base/ftmm.c \
	src/base/ftotval.c \
	src/base/ftpatent.c \
	src/base/ftpfr.c \
	src/base/ftstroke.c \
	src/base/ftsynth.c \
	src/base/fttype1.c \
	src/base/ftwinfnt.c \
	src/base/ftxf86.c \
	src/truetype/truetype.c \
	src/type1/type1.c \
	src/cff/cff.c \
	src/cid/type1cid.c \
	src/pfr/pfr.c \
	src/type42/type42.c \
	src/winfonts/winfnt.c \
	src/pcf/pcf.c \
	src/bdf/bdf.c \
	src/sfnt/sfnt.c \
	src/autofit/autofit.c \
	src/pshinter/pshinter.c \
	src/raster/raster.c \
	src/smooth/smooth.c \
	src/cache/ftcache.c \
	src/gzip/ftgzip.c \
	src/lzw/ftlzw.c \
	src/bzip2/ftbzip2.c \
	src/psaux/psaux.c \
	src/psnames/psmodule.c

ifeq ($(TARGET),i686-w64-mingw32)
CSOURCES += builds/windows/ftdebug.c
CSOURCES += src/base/ftsystem.c
else
CSOURCES += builds/unix/ftsystem.c
endif

