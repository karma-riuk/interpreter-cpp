# -------------------------------------------------------------------
# Project‐wide settings
# -------------------------------------------------------------------
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Iinclude -Isrc -MMD -MP
LDFLAGS   :=
SRC_DIR   := src
TEST_DIR  := test
BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/objs
BIN_DIR   := $(BUILD_DIR)/bin

# -------------------------------------------------------------------
# Source & object lists
# -------------------------------------------------------------------
SRC_CPP    := $(shell find $(SRC_DIR)  -name '*.cpp')
TEST_CPP   := $(shell find $(TEST_DIR) -name '*.cpp')
OBJ        := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_CPP))
TEST_OBJ   := $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/test/%.o,$(TEST_CPP))
DEPFILES   := $(OBJ:.o=.d) $(TEST_OBJ:.o=.d)

# Identify your “real” main.cpp so we can exclude it from tests
MAIN_SRC        := $(SRC_DIR)/main.cpp
MAIN_OBJ        := $(MAIN_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SRC_OBJS_NO_MAIN := $(filter-out $(MAIN_OBJ),$(OBJ))

# Binaries
TARGET        := $(BIN_DIR)/monkey
TEST_TARGET   := $(BIN_DIR)/monkey_tests

# -------------------------------------------------------------------
# Top‐level rules
# -------------------------------------------------------------------
.PHONY: all clean monkey tests
all: $(TARGET) $(TEST_TARGET)

clean:
	@rm -rf $(BUILD_DIR)

# -------------------------------------------------------------------
# Build & run
# -------------------------------------------------------------------
monkey: $(TARGET)
	@$(TARGET)

tests: $(TEST_TARGET)
	@$(TEST_TARGET) $(if $(TEST),--test-case=$(TEST))

# -------------------------------------------------------------------
# Link binaries
# -------------------------------------------------------------------
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(TEST_TARGET): $(SRC_OBJS_NO_MAIN) $(TEST_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

# -------------------------------------------------------------------
# Compile rules
# -------------------------------------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -------------------------------------------------------------------
# Auto‐include dependencies
# -------------------------------------------------------------------
-include $(DEPFILES)
