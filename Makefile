EMSCRIPTEN=../emscripten/emcc
BUILD=./build

build:
	mkdir -p build
	$(EMSCRIPTEN) -g3 src/rays.cpp -o $(BUILD)/rays.html
.PHONY: build
