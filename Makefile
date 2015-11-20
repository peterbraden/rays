EMSCRIPTEN=../emscripten/emcc
BUILD=./build

build: buildcpp
	mkdir -p build
	#g++ `sdl2-config --cflags --libs` -Werror -Wall  src/rays.cpp -o $(BUILD)/rays.out
	#$(EMSCRIPTEN) -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -g3 src/rays.cpp -o $(BUILD)/rays.html
	#$(EMSCRIPTEN) -s ALLOW_MEMORY_GROWTH=1 -g3 src/rays.cpp -o $(BUILD)/rays.html
.PHONY: build

buildcpp:
	g++ -L/usr/local/lib -lSDL2  -I/usr/local/include  src/rays.cpp src/trace.cpp src/types.cpp src/camera.cpp -o $(BUILD)/rays.out
.PHONY: buildcpp

devcpp: buildcpp
	$(BUILD)/rays.out
.PHONY: devcpp
