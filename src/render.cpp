#include "types.h"
#include "scene.h"
#include "trace.h"

//struct Image {};


Color renderPixelAt(float x, float y, Scene scene){
  Ray ray = scene.camera.getRay(x, y);
  Color pixel = trace(ray, 0, scene); 
  return pixel;
}


Color renderPixel(int x, int y, Scene scene){
  return renderPixelAt((float) x / (float) scene.width, (float) y / (float) scene.height, scene); 
}

// BUGS:
Color renderPixelAA(int x, int y, Scene scene){
  float _x = (float) x;
  float _y = (float) y;

  Color avg = renderPixelAt(_x/scene.width, _y/scene.height, scene);
  avg = color_add(avg, renderPixelAt((_x + 0.5) / scene.width, y / scene.height, scene));
  avg = color_add(avg, renderPixelAt(_x / scene.width, (_y + 0.5) / scene.height, scene));
  avg = color_add(avg, renderPixelAt((_x + 0.5) / scene.width, (_y + 0.5) / scene.height, scene));
  avg = color_scale(avg, 0.25);

  return avg;
}
