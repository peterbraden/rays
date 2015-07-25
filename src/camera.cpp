class Camera {
  private:
    vec3 camx;
    vec3 camy;
    vec3 camz;
    vec3 ncamz;
    float tax;
    float tay;

  public:
    vec3 up;
	  vec3 location;
	  vec3 lookat;
	  float angle;

     
	  Camera(vec3 u, vec3 loc, vec3 la, float a): angle(a){
      up = u;
      location = loc;
      lookat = la;

      camz = vec3_sub(lookat, location);
      if (vec3_len(camz) == 0){
        printf("FATAL: BAD CAMERA VECTORS");
      }
      camz = vec3_norm(camz);

      camx = vec3_mul_cross(up, camz);
      camx = vec3_norm(camx);
      
      camy = vec3_mul_cross(camx, vec3_sub((vec3) {0., 0., 0.}, camz));
      camy = vec3_norm(camy);

      tax = tan(angle);
      tay = tan((float) HEIGHT / (float) WIDTH * angle);

      /*
      printf("\n CAMERA: ");
      vec3_print(camx);
      vec3_print(camy);
      vec3_print(camz);
      printf("\n");
      */
    }

    // NB. Proportional x and y
	  Ray getRay(float x, float y){
      vec3 xdir;
      vec3 ydir;
      vec3 dest;

      xdir = vec3_scale(camx, (x-0.5) * tax);
      ydir = vec3_scale(camy, (y-0.5) * tay);

      dest = vec3_add(camz, vec3_add(xdir, ydir));

      Ray r;
      r.ro = location;
      r.rd = dest;

      //printf("[%f, %f]", x,y);
      //vec3_print(dest);
      return r;
	}
};




