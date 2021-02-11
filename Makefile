SRC_PATH := src
BUILD_PATH := build
CXX_FLAGS := -MMD -c
SRC_FILES := $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_PATH)/%.cpp,$(BUILD_PATH)/%.o,$(SRC_FILES))

nash: $(OBJ_FILES)
	g++ -o $@ $^

debug: CXX_FLAGS += -g
debug: nash

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp | $(BUILD_PATH)
	g++ $(CXX_FLAGS) -o $@ $<

-include $(OBJ_FILES:.o=.d)

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

clean:
	rm -rf build/
	rm -f nash

.PHONY: clean debug