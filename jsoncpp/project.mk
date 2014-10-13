# Required
NAME := jsoncpp
TYPE := static

# Since we have the includes in the same folder as source
INCLUDES += -I$(PROJECT_ROOT)/include

# Deploy
EXPORT_SYSTEM_LIB := 1
EXPORT_LIBNAME := jsoncpp
EXPORT_LIBVERSION := 0.5.0
