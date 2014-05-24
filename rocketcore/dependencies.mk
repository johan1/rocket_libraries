# Boost dependencies
LOCAL_LIBNAME 		:= BoostThread
LOCAL_LIBVERSION	:= 1.55
include $(BUILD_ROOT)/common/repo_dependency.mk

LOCAL_LIBNAME 		:= BoostFileSystem
LOCAL_LIBVERSION	:= 1.55
include $(BUILD_ROOT)/common/repo_dependency.mk

LOCAL_LIBNAME 		:= BoostChrono
LOCAL_LIBVERSION	:= 1.55
include $(BUILD_ROOT)/common/repo_dependency.mk

ifneq ($(findstring android,$(TARGET)),)
SYSTEM_LIBRARIES += -llog
endif
