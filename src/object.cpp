#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "object.h"

Sphere::Sphere(vec3 c, float r, Color col) : radius(r) {
  center = c;
  _material.pigment = col;
  _material.reflection = 0.5;
  _material.phong = 40;
}

Plane::Plane(float height) : y(height) {}


Intersection Plane::intersects(vec3 ro, vec3 rd){
  vec3 rdn = vec3_norm(rd);
  vec3 norm = (vec3) {0,1,0};
  float dist = vec3_dot( norm, vec3_sub( (vec3) {0,y,0}, ro));
  dist = dist / vec3_dot(norm, rdn);
  vec3 pt = vec3_add(ro, vec3_scale(vec3_norm(rd), dist));

  return (Intersection) {dist, pt, norm, this};
}

BBox* Plane::getBounds() {
  return NULL;
}

Material Plane::material(vec3 pt){
  Material m;
	int zig = pt.x > 0 ? abs( (int) pt.x)/50 % 2 ? 1 : 0 : abs( (int) pt.x)/50 % 2 ? 0 : 1;
  int zag = pt.z > 0 ? abs( (int) pt.z)/50 % 2 ? 1 : 0 : abs( (int) pt.z)/50 % 2 ? 0 : 1;

	if(!zig != !zag) { // zig XOR zag
    m.pigment = (Color){255,255,255};
  } else {
    m.pigment = (Color){0,0,0};
  }
  return m;
}

void Plane::printInfo(){
  printf("plane");
}

vec3 Sphere::normal(vec3 pt){
  return vec3_norm(vec3_sub(pt, center));
}

Material Sphere::material(vec3 pt){
  return _material;
}

Intersection Sphere::intersects(vec3 ro, vec3 rd){
  //printf("Called Sphere::intersects, radius:  %f", radius);
  vec3 dst;
  vec3 pt;

  dst = vec3_sub(ro, center);
  float b = vec3_mul_inner(dst, vec3_norm(rd)); // dot product.
  float c = vec3_mul_inner(dst, dst) - radius * radius;
  float d = b*b-c;
  float dist;

  if (d > 0){
    dist = -b - sqrt(d);
  } else {
    dist = -1;
  }

  // Project point along ray
  pt = vec3_add(ro, vec3_scale(vec3_norm(rd), dist));
  return (Intersection) {dist, pt, normal(pt), this};
}

void Sphere::printInfo(){
  printf("Sphere, radius: %f center:<%f,%f,%f> ", radius, center.x, center.y, center.z);
}

BBox* Sphere::getBounds(){
  return new BBox(
    (vec3) {center.x - radius, center.y - radius, center.z - radius}, // neg?
    (vec3) {center.x + radius, center.y + radius, center.z + radius}
    );
}
