# Required
NAME := BoostThread
TYPE := static

$(info $(TARGET))

ifeq ($(TYPE),static)
DEFINES += -DBOOST_THREAD_BUILD_LIB
else
DEFINES += -DBOOST_THREAD_BUILD_DLL
endif

# For windows builds
ifeq ($(TARGET),i686-w64-mingw32)
DEFINES += -DBOOST_USE_WINDOWS_H
# Other
else
DEFINES += -DBOOST_THREAD_POSIX
endif

ifeq ($(TARGET),i686-w64-mingw32)
SOURCES := \
win32/thread.cpp \
future.cpp
ifeq ($(TYPE),shared)
SOURCES += win32/tss_dll.cpp
endif
SOURCES += win32/tss_pe.cpp
else
SOURCES := \
pthread/thread.cpp \
pthread/once.cpp \
future.cpp
endif

# Deploy
EXPORT_SYSTEM_LIB := 1
EXPORT_INCLUDE_FOLDER_NAME := boost
EXPORT_LIBNAME := BoostThread
EXPORT_LIBVERSION := 1.55
