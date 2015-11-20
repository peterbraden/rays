#ifndef RAYS_TRACE
#define RAYS_TRACE


std::vector<Intersection> intersect(vec3 ro, vec3 rd, Scene scene);
Intersection nearestIntersection(vec3 ro, vec3 rd, float max, float min, Scene scene);
Color trace(Ray r, int depth, Scene scene);



#endif
