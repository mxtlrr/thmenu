CXX := g++
CXXFLAGS := -Wall -Wextra -Iinclude

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

$(BIN_DIR)/thmenu: $(OBJS)
	@echo "Linking..."
	$(CXX) -o $@ $^
	@echo "Build successful!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "CC $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Clean up build files
.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/thmenu
	@echo "Cleaned."

$(BIN_DIR)/$(BIN_NAME): | $(BIN_DIR)
