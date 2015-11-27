/* Ray tracing algorithm */
#include "trace.h"

std::vector<Intersection> intersect(vec3 ro, vec3 rd, Scene scene){
  std::vector<Intersection> v;

  for(int i = scene.objects.size()-1; i>=0; --i) {
    //printf("Iterate objects: %i of %zi \n", i, scene.objects.size());
    Intersection intersect = scene.objects[i]->intersects(ro, rd);
    if (intersect.distance > 0){
      v.push_back(intersect);
    }
  }
  //printf("Intersection %zi", v.size());

  return v;
}

Intersection nearestIntersection(vec3 ro, vec3 rd, float max, float min, Scene scene){
  Intersection closest;
  closest.distance = std::numeric_limits<float>::max();
  int intersects = 0;

  for(int i = scene.objects.size()-1; i>=0; --i) {
    Intersection intersect = scene.objects[i]->intersects(ro, rd);
    if (intersect.distance > 0 && 
        intersect.distance < closest.distance &&
        intersect.distance < max &&
        intersect.distance > min){
      closest = intersect;
      intersects = 1;
    }
  }

  if (intersects == 0){
    closest.distance = -1;
  }
  return closest;
}

float max = std::numeric_limits<float>::max();

// trace ro->rd into scene.
Color trace(Ray r, int depth, Scene scene){
  //totalRaysTraced ++;

  Intersection closest = nearestIntersection(r.ro, r.rd, max, 0, scene);

  if (closest.distance < 0) {
    // No Intersection.
    return (Color) {0,0,0};
  }

  Material material = closest.obj->material(closest.point);
  Color out;


  // Ambient
  out = color_scale(material.pigment, scene.ambient);
  vec3 speculars = (vec3) {0,0,0};

  for(int i = scene.lights.size()-1; i>=0; --i) {
    vec3 lightVec = vec3_sub(scene.lights[i].location, closest.point);
    Intersection shadow = nearestIntersection(closest.point, lightVec, vec3_len(lightVec), 0.05, scene);
    // if there's an intersection (dist > 0) then the point is shadowed.
    if (shadow.distance < 0){

      // Diffuse (Lambertian)
      float diffuse_scale = vec3_dot(vec3_norm(lightVec), closest.normal) * scene.lights[i].intensity;
      if (diffuse_scale > 0) {
        Color diffuse = color_scale(material.pigment, diffuse_scale);
        out = color_add(out, diffuse);
      }

      // Specular
      vec3 ln = vec3_norm(lightVec);
      vec3 refl = vec3_sub(ln, vec3_scale(closest.normal, 2.0 * vec3_dot(closest.normal, ln)));
      float dp = vec3_dot(refl, vec3_norm(r.rd));
      if (dp > 0){
        float spec_scale = pow(dp, material.phong);
        speculars = vec3_add(speculars, vec3_scale( (vec3) {1.,1.,1.}, std::min(spec_scale * 255., 255.)));// TODO Color 
      }
    
    }
  }
  out = color_add(out, speculars);

  // Reflection
  if (depth < scene.maxDepth){ // TODO - only if reflection != 0
    Ray refl;
    refl.ro = closest.point;
    refl.rd = vec3_sub(r.rd, vec3_scale(closest.normal, 2.0 * vec3_dot(closest.normal, r.rd)));
    Color rc = trace(refl, depth + 1, scene);
    out = color_add(color_scale(out, 1 - material.reflection), color_scale(rc, material.reflection)); 
  }
  

  return out;
}


