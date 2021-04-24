SRC_DIR := proton
OBJ_DIR := obj
BUILD_DIR := build
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TARGET := build/proton

$(TARGET): $(OBJ_FILES)
	g++ -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	[-d $(OBJ_DIR)] || mkdir $(OBJ_DIR)
	[-d $(BUILD_DIR)] || mkdir $(BUILD_DIR)
	g++ -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
