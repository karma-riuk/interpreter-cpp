# ────────────────────────────────────
# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall -WError -I./include

# ────────────────────────────────────
# Paths
SRC_DIR   := src
TEST_SRC  := test/test.cpp
REPL_SRC  := $(SRC_DIR)/main.cpp

OBJ_DIR   := build/obj
BIN_DIR   := build/bin

# ────────────────────────────────────
# Source listings
# All .cpp under src/, but exclude your REPL main
LIB_SRCS := $(filter-out $(REPL_SRC),$(shell find $(SRC_DIR) -name '*.cpp'))

# Mirror src/.../*.cpp → build/obj/src/.../*.o
LIB_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/$(SRC_DIR)/%.o,$(LIB_SRCS))

# Binaries
TEST_BIN := $(BIN_DIR)/tests
REPL_BIN := $(BIN_DIR)/repl

# ────────────────────────────────────
# Default target: build & run tests
all: test

# ─ Link test runner (test.cpp defines main via DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
$(TEST_BIN): $(LIB_OBJS) | $(BIN_DIR)
    @echo "⏳ Linking tests..."
    $(CXX) $(CXXFLAGS) $(TEST_SRC) $(LIB_OBJS) -o $@

# ─ Link REPL
$(REPL_BIN): $(LIB_OBJS) | $(BIN_DIR)
    @echo "🚀 Linking REPL..."
    $(CXX) $(CXXFLAGS) $(REPL_SRC) $(LIB_OBJS) -o $@

# ─ Compile each library .cpp → mirrored .o
$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
    @echo "🛠  Compiling $<"
    @mkdir -p $(dir $@)
    $(CXX) $(CXXFLAGS) -c $< -o $@

# ────────────────────────────────────
# Run or launch targets
.PHONY: test repl clean all

test: $(TEST_BIN)
    @echo "\n✅ Running tests..."
    @$(TEST_BIN)
    # @$(TEST_BIN) $(if $(TESTCASE),--test-case=$(TESTCASE))

repl: $(REPL_BIN)
    @echo "\n🔧 Starting REPL..."
    @$(REPL_BIN)

# ────────────────────────────────────
# Ensure bin/ exists before linking
$(BIN_DIR):
    @mkdir -p $@

# ────────────────────────────────────
# Clean up everything
clean:
    @echo "🧹 Cleaning build artifacts"
    @rm -rf $(OBJ_DIR) $(BIN_DIR)

