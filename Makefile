EMSCRIPTEN=../emscripten/emcc
BUILD=./build

build:
	$(EMSCRIPTEN) src/rays.cpp -o $(BUILD)/rays.html
.PHONY: build
