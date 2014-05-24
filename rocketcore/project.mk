# Required
NAME := rocketcore
TYPE := static

TARGET_OPTIM := debug

SOURCE_DIR := $(PROJECT_ROOT)/src

# SOURCES := $(shell find $(PROJECT_ROOT)/src/common -name *.cpp | sed 's/.*src\///g' | tr '\n' ' ')

# Deploy
EXPORT_AUTO_INCLUDES := 1
EXPORT_INCLUDE_FOLDER_NAME := rocket
EXPORT_LIBNAME := rocketcore
EXPORT_LIBVERSION := 0.0.1
