# Appending this library to the build variables
ifeq ($(TARGET),host)
LIBRARIES += -L$(LOCAL_LIBPATH)/lib/$(TARGET) -lopenal -ldl -lsndio
LIBRARY_FILES += $(LOCAL_LIBPATH)/lib/$(TARGET)/libopenal.so
SHARED_FILES += $(LOCAL_LIBPATH)/lib/$(TARGET)/libopenal.so
endif
ifeq ($(TARGET),i686-w64-mingw32)
LIBRARIES += -L$(LOCAL_LIBPATH)/lib/$(TARGET) -lOpenAL32 -lole32 -lwinmm -lm
LIBRARY_FILES += $(LOCAL_LIBPATH)/lib/$(TARGET)/libOpenAL32.dll.a
SHARED_FILES += $(LOCAL_LIBPATH)/bin/$(TARGET)/OpenAL32.dll
endif
INCLUDES += -I$(LOCAL_LIBPATH)/include

