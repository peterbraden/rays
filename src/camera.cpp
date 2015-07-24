class Camera {
  public:
    vec3 up;
	  vec3 location;
	  vec3 lookat;
	  float angle;
     
	  Camera(up, location, lookat, angle)
/*
	  vec3 getRay(int x, int y){

      vec3 camx;
      vec3 camy;
      vec3 camz;
      vec3 ncamz;

      vec3_norm(camz, lookat, location);
      vec3_norm(camz, camz);
      vec3_mul_cross(camx, up, camz);
      vec3_norm(camx, camx);
      vec3_sub(ncamz, (vec3) {0., 0., 0.}, camz);
      vec3_mul_cross(camy, up, ncamz);
      vec_norm(camy, camy);

	
	this.tax = Math.tan(angle);
	this.tay = Math.tan((height/width) * angle)
		var xdir = plib.v3.scale(this.camx, (x - 0.5) * this.tax);
		var ydir = plib.v3.scale(this.camy, (y - 0.5) * this.tay);
		
		var pt = plib.v3.add(this.camz, plib.v3.add(xdir, ydir));
		
		//postMessage("DBG2 " + this.location + " |  " +pt + " | " + plib.v3.sub(pt, this.location) );
		return [this.location, pt]
    
    }
	
	}
  */
};




