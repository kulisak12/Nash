SRC_PATH := src
BUILD_PATH := build
SRC_FILES := $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_PATH)/%.cpp,$(BUILD_PATH)/%.o,$(SRC_FILES))

nash: $(OBJ_FILES)
	g++ -o $@ $^

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp | $(BUILD_PATH)
	g++ -MMD -c -o $@ $<

-include $(OBJ_FILES:.o=.d)

$(BUILD_PATH):
	mkdir -p build

clean:
	rm -rf build/
	rm -f nash

.PHONY: clean