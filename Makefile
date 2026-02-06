# =========================
# Compiler & flags
# =========================
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -Iinclude
LDFLAGS :=

# =========================
# Directories
# =========================
SRC_DIR   := src
TEST_DIR  := tests
BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj
BIN_DIR   := $(BUILD_DIR)/bin
TEST_BIN_DIR := $(BUILD_DIR)/tests

# =========================
# Source files
# =========================
APP_SRC := $(SRC_DIR)/main.c
LIB_SRC := $(filter-out $(APP_SRC), $(wildcard $(SRC_DIR)/*.c))
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)

# =========================
# Object files
# =========================
APP_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(APP_SRC))
LIB_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRC))

# =========================
# Binaries
# =========================
APP_BIN  := $(BIN_DIR)/tinydbms
TEST_BIN := $(TEST_BIN_DIR)/run_tests

# =========================
# Dependency files
# =========================
DEPS := $(LIB_OBJ:.o=.d) $(APP_OBJ:.o=.d)

# =========================
# Phony targets
# =========================
.PHONY: all app test clean dirs

# =========================
# Default target
# =========================
all: app

# =========================
# Create directories
# =========================
dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR) $(TEST_BIN_DIR)

# =========================
# Build application
# =========================
app: dirs $(APP_BIN)

$(APP_BIN): $(LIB_OBJ) $(APP_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# =========================
# Build & run tests
# =========================
test: dirs $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(LIB_OBJ) $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIB_OBJ) -o $@

# =========================
# Compile source files
# =========================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# =========================
# Include dependencies
# =========================
-include $(DEPS)

# =========================
# Clean
# =========================
clean:
	rm -rf $(BUILD_DIR)
