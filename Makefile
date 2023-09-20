# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_NAME := WavPlayer

BUILD_DIR := ./build
SRC_DIRS := ./src
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
HEADERS = $(shell find $(SRC_DIRS) -name '*.h')

CC = clang
CFLAGS := -Wall -Wextra -pedantic 
CFLAGS += -g3
CFLAGS += $(INC_FLAGS)
CFLAGS += -MMD -MP 

CXX = clang++
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17

LDLIBS :=

all: build

.PHONY: build
build: $(TARGET)

.PHONY: run
run: $(TARGET)
	@echo "\nrunning $^ !\n"
	@./$^

.PHONY: re
re: clean update

.PHONY: hex
hex: run
	hexdump wave.wav > $(BUILD_DIR)/hex.txt

# Linking
$(TARGET): $(OBJS)
	@echo "Linking"
	@$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Compile C++
$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C
$(BUILD_DIR)/%.c.o: %.c
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	@echo "Clean up"
	@$(RM) -r $(BUILD_DIR)

.PHONY: format
format:
	clang-format -i $(SRCS)
	clang-format -i $(HEADERS)

.PHONY: update
update:
	make clean
	mkdir -p $(BUILD_DIR)
	bear --output $(BUILD_DIR)/compile_commands.json -- make b

# aliases
.PHONY: b r f c u
b: build
r: run
f: format
c: clean
u: update

-include $(DEPS)
