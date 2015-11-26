EMSCRIPTEN=../emscripten/emcc
BUILD=./build

build: buildcpp
	mkdir -p build
	g++ `sdl2-config --cflags --libs` -Werror -Wall -std=c++0x -pthread src/rays.cpp -o $(BUILD)/rays.out
	#$(EMSCRIPTEN) -s ALLOW_MEMORY_GROWTH=1 -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -g3 src/rays.cpp -o $(BUILD)/rays.html
	#$(EMSCRIPTEN) -s ALLOW_MEMORY_GROWTH=1 -g3 src/rays.cpp -o $(BUILD)/rays.html
.PHONY: build

buildcpp:
	g++ -L/usr/local/lib -lSDL2 -lpng -I/usr/local/include -I./ext -x c ext/sdl-savepng/savepng.c -x c++ src/rays.cpp src/types.cpp src/camera.cpp src/object.cpp ext/sdl-savepng/savepng.c -o $(BUILD)/rays.out
.PHONY: buildcpp

devcpp: buildcpp
	$(BUILD)/rays.out
.PHONY: devcpp
