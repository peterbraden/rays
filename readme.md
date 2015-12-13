# Rays
[![Build
Status](https://travis-ci.org/peterbraden/rays.svg?branch=master)](https://travis-ci.org/peterbraden/rays)

An experimental raytracer. 

```sh
make build
./build/rays.out
```





### References
- [M Agate, R Grimsdale, P Lister, 1989, The HERO Algorithm for Ray-Tracing
    Octrees](http://dl.acm.org/citation.cfm?id=2421200)
  This is the algorithm currently powering the scene graph.
- [H Samet, 1989. IMPLEMENTING RAY TRACING WITH OCTREES AND NEIGHBOR FINDING* ](http://www.cs.umd.edu/~hjs/pubs/SameCG89.pdf)
  Seemed like it would be a useful paper, but at the last minute, the author
  switches to an approach that needs "computation to be exact" and thus can't
  use floating point, thus rendering the entire paper useless.
