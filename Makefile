EMSCRIPTEN=../emscripten/emcc
BUILD=./build

build:
	mkdir -p build
	g++ `sdl2-config --cflags --libs` -Werror -Wall  src/rays.cpp -o $(BUILD)/rays.out
	#$(EMSCRIPTEN) -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -g3 src/rays.cpp -o $(BUILD)/rays.html
	$(EMSCRIPTEN) -s ALLOW_MEMORY_GROWTH=1 -g3 src/rays.cpp -o $(BUILD)/rays.html
.PHONY: build
