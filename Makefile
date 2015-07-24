EMSCRIPTEN=../emscripten/emcc
BUILD=./build

build:
	mkdir -p build
	g++ `sdl2-config --cflags --libs` -Wall  src/rays.cpp -o $(BUILD)/rays.out
	$(EMSCRIPTEN) -g3 src/rays.cpp -o $(BUILD)/rays.html
.PHONY: build
