# Sources for makefile

# WPILib dir
WPILIB_DIR := $(HOME)/wpilib

# Source directory
SRC_DIR := src

# Build directory
BUILD_DIR := build

# Include directories
INCLUDE_DIRS := $(SRC_DIR) $(WPILIB_DIR)/cpp/current/include $(WPILIB_DIR)/user/cpp/include

# Library directories
LIB_DIRS := $(WPILIB_DIR)/user/cpp/lib $(WPILIB_DIR)/cpp/current/lib

# All source files, recursively found in SRC_DIR
CPP_SRC := $(shell find $(SRC_DIR) -name '*.cpp')

# All object files, from CPP_SRC
OBJS := $(addprefix $(BUILD_DIR)/,$(CPP_SRC:%.cpp=%.o))
