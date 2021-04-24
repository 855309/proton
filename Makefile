SRC_DIR := proton
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TARGET := build/proton

$(TARGET): $(OBJ_FILES)
	g++ -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -c -o $@ $<

clean:
	rm -rf $(OBJ_FILES) $(TARGET)