EMSCRIPTEN=../emscripten/emcc
BUILD=./build

build:
	mkdir -p build
	$(EMSCRIPTEN) src/rays.cpp -o $(BUILD)/rays.html
.PHONY: build
