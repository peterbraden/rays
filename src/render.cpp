//struct Image {};


Color renderPixelAt(float x, float y, Scene scene){
  Ray ray = scene.camera.getRay(x, y);
  Color pixel = trace(ray, 0, scene); 
  return pixel;
}


Color renderPixel(int x, int y, Scene scene){
  return renderPixelAt((float) x / (float) WIDTH, (float) y / (float) HEIGHT, scene); 
}

// BUGS:
Color renderPixelAA(int x, int y, Scene scene){
  float _x = (float) x;
  float _y = (float) y;

  Color avg = renderPixelAt(_x/WIDTH, _y/HEIGHT, scene);
  avg = color_add(avg, renderPixelAt((_x + 0.5) / WIDTH, y / HEIGHT, scene));
  avg = color_add(avg, renderPixelAt(_x / WIDTH, (_y + 0.5) / HEIGHT, scene));
  avg = color_add(avg, renderPixelAt((_x + 0.5) / WIDTH, (_y + 0.5) / HEIGHT, scene));
  avg = color_scale(avg, 0.25);

  return avg;
}
