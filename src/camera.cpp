class Camera {
  public:
    vec3 up;
	  vec3 location;
	  vec3 lookat;
	  float angle;
     
	  Camera(vec3 u, vec3 loc, vec3 la, float a): angle(a){
      up = u;
      location = loc;
      lookat = la;
    }

    // NB. Proportional x and y
	  Ray getRay(float x, float y){

      vec3 camx;
      vec3 camy;
      vec3 camz;
      vec3 ncamz;
      vec3 xdir;
      vec3 ydir;
      vec3 dest;

      vec3_sub(camz, lookat, location);
      vec3_print(location);
      vec3_print(lookat);
      vec3_print(camz);
      if (vec3_len(camz) == 0){
        printf("FATAL: BAD CAMERA VECTORS");
      }
      vec3_norm(camz, camz);
      vec3_mul_cross(camx, up, camz);
      vec3_norm(camx, camx);
      vec3_sub(ncamz, (vec3) {0., 0., 0.}, camz);
      vec3_mul_cross(camy, up, ncamz);
      vec3_norm(camy, camy);

      float tax = tan(angle);
      float tay = tan(HEIGHT/WIDTH * angle);

      vec3_scale(xdir, camx, (x-0.5) * tax);
      vec3_scale(ydir, camy, (y-0.5) * tay);

      vec3_add(dest, xdir, ydir);
      vec3_add(dest, camz, dest);

      Ray r;
      r.ro = location;
      r.rd = dest;

      printf("<%f, %f> --> <%f, %f, %f>", x, y, dest.x, dest.y, dest.z);
      return r;
	}
};




