#ifndef RAYS_RENDER
#define RAYS_RENDER

#include "types.h" 
#include "scene.h" 
#include "trace.h"


// Per Pixel, no side effects
Color renderPixel(int screenX, int screenY, Scene s, RenderStats* r);
Color renderAntiAliasedPixel(int x, int y, Scene scene, RenderStats* r);

#endif
