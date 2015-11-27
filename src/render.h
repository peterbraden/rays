#ifndef RAYS_RENDER
#define RAYS_RENDER

#include "types.h" 
#include "scene.h" 

// Per Pixel, no side effects
Color renderPixel(int screenX, int screenY, Scene s);
Color renderPixelAA(int screenX, int screenY, Scene s);

// Chunks of pixels, output data goes into Image struct
//void renderLine(int x, Scene s, Image im);


#endif
