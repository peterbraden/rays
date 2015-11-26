EMSCRIPTEN=emcc
BUILD=./build

CC=g++
CFLAGS=-Werror -Wall -std=c++0x
INCLUDES=-I/usr/local/include -I./ext -I./src 
LFLAGS=-L/usr/local/lib 
PKG_CONFIG_SDL=`sdl2-config --cflags --libs`
LIBS=-lpng $(PKG_CONFIG_SDL)

SRCS=src/rays.cpp src/types.cpp src/camera.cpp src/object.cpp 
OBJS=$(SRCS:.cpp=.cpp.o)

C_SRCS=ext/sdl-savepng/savepng.c
C_OBJS=$(C_SRCS:.c=.c.o)


buildEmscripten:
	mkdir -p build
	$(EMSCRIPTEN) -s ALLOW_MEMORY_GROWTH=1 -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -g3 src/rays.cpp -o $(BUILD)/rays.html
	#$(EMSCRIPTEN) -s ALLOW_MEMORY_GROWTH=1 -g3 src/rays.cpp -o $(BUILD)/rays.html
.PHONY: build


buildcpp: $(OBJS) $(C_OBJS)
	mkdir -p build
	$(CC) $(LFLAGS) $(LIBS) $(INCLUDES) $(OBJS) $(C_OBJS) -o $(BUILD)/rays.out
	#g++ `sdl2-config --cflags --libs` -Werror -Wall -std=c++0x -pthread src/rays.cpp -o $(BUILD)/rays.out
.PHONY: buildcpp

build: buildcpp buildEmscripten

%.cpp.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.c.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(C_OBJS)

devcpp: buildcpp
	$(BUILD)/rays.out
.PHONY: devcpp
