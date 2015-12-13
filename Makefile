EMSCRIPTEN=emcc
BUILD=./build

CC=g++
CFLAGS=-MMD -g -Wall
#-Werror -Wall -std=c++0x
INCLUDES=-I/usr/local/include -I./ext -I./src 
LFLAGS=-L/usr/local/lib 
PKG_CONFIG_SDL=`sdl2-config --cflags --libs`
LIBS=-lpng $(PKG_CONFIG_SDL)
C_SRCS=ext/sdl-savepng/savepng.c
C_OBJS=$(C_SRCS:.c=.c.o)


SRCS=$(wildcard src/*.cpp)
OBJS=$(addprefix obj/, $(notdir $(SRCS:.cpp=.cpp.o)))


devcpp: buildcpp
	# Build successfully
	$(BUILD)/rays.out -w 5 -h 5
.PHONY: devcpp
.DEFAULT: devcpp

install:
	mkdir -p obj

buildEmscripten:
	mkdir -p build
	$(EMSCRIPTEN) -s ALLOW_MEMORY_GROWTH=1 -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -g3 $(SRCS) -o $(BUILD)/rays.html
.PHONY: build


buildcpp: $(OBJS) $(C_OBJS)
	mkdir -p build
	$(CC) $(LFLAGS) $(INCLUDES) $(OBJS) $(C_OBJS) -o $(BUILD)/rays.out $(LIBS)
	#g++ `sdl2-config --cflags --libs` -Werror -Wall -std=c++0x -pthread src/rays.cpp -o $(BUILD)/rays.out
.PHONY: buildcpp

build: buildcpp buildEmscripten

obj/%.cpp.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.c.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f ./obj/* 


# Script shortcuts
# lldb -- ./build/rays.out -w 50 -h 50
# valgrind --tool=callgrind ./build/rays.out




