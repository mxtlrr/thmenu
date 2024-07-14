CXX := g++
CXXFLAGS := -Iinclude $(LINKERS) -march=x86-64

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

LINKERS := -lpsapi -lkernel32

SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

$(BIN_DIR)/thmenu: $(OBJS)
	@echo "Linking..."
	g++ -o $@ $^ $(LINKERS)
	@echo "Build successful!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "CC $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p obj/ obj/hacks

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Clean up build files
.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(OBJ_DIR)
	@echo "Cleaned."

$(BIN_DIR)/$(BIN_NAME): | $(BIN_DIR)
