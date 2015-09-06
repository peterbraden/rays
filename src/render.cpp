//struct Image {};


Color renderPixel(int x, int y, Scene scene){
  Ray ray = scene.camera.getRay((float) x / (float) WIDTH, (float) y / (float) HEIGHT);

  Color pixel = trace(ray, 0, scene); 

  //printf("\nRender <%i,%i>: %i,%i,%i", x, y, pixel.r, pixel.g, pixel.b);
  return pixel;
}

Color renderPixelAA(int x, int y, Scene scene){
  // TODO - adaptive subsampling
  float x1 = (float) x / (float) WIDTH;
  float x2 = ((float) x + 0.5)  / (float) WIDTH;
  float y1 = (float) y / (float) HEIGHT;
  float y2 = ((float) y + 0.5)  / (float) HEIGHT;
  Ray ray1 = scene.camera.getRay(x1, y1);
  Ray ray2 = scene.camera.getRay(x1, y2);
  Ray ray3 = scene.camera.getRay(x2, y1);
  Ray ray4 = scene.camera.getRay(x2, y2);

  printf(">1\n");
  Color avg = trace(ray1, 0, scene);
  printf(">2\n");
  avg = color_add(avg, trace(ray2, 0, scene));
  avg = color_add(avg, trace(ray3, 0, scene));
  avg = color_add(avg, trace(ray4, 0, scene));

  avg = color_scale(avg, 0.25);

  return avg;
}
