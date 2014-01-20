ifeq ($(TARGET),host)
SYSTEM_LIBRARIES += -lrt -lpthread
endif

LOCAL_LIBNAME 		:= BoostSystem
LOCAL_LIBVERSION	:= 1.55
include $(BUILD_ROOT)/common/repo_dependency.mk
