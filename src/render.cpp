#include "render.h"

Color renderPixelAt(float x, float y, Scene scene, RenderStats* r){
  Ray ray = scene.camera.getRay(x, y);
  Color pixel = trace(ray, 0, scene, r); 
  r->raysTraced++;
  return pixel;
}


Color renderPixel(int x, int y, Scene scene, RenderStats* r){
  return renderPixelAt((float) x / (float) scene.width, (float) y / (float) scene.height, scene, r); 
}

Color renderAntiAliasedPixel(int x, int y, Scene scene, RenderStats* r){
  float x1 = (float) x / (float) scene.width;
  float x2 = ((float) x + 0.5)  / (float) scene.width;
  float y1 = (float) y / (float) scene.height;
  float y2 = ((float) y + 0.5)  / (float) scene.height;
  Ray ray1 = scene.camera.getRay(x1, y1);
  Ray ray2 = scene.camera.getRay(x1, y2);
  Ray ray3 = scene.camera.getRay(x2, y1);
  Ray ray4 = scene.camera.getRay(x2, y2);

  Color avg = trace(ray1, 0, scene, r);
  avg = color_add(avg, trace(ray2, 0, scene, r));
  avg = color_add(avg, trace(ray3, 0, scene, r));
  avg = color_add(avg, trace(ray4, 0, scene, r));


  avg = color_scale(avg, 0.25);

  return avg;
}
