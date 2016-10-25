DEFINES += -DGLEW_STATIC

ifeq ($(TARGET),i686-w64-mingw32)
SYSTEM_LIBRARIES += -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
endif

ifeq ($(TARGET),host)
SYSTEM_LIBRARIES += -lGL
endif
