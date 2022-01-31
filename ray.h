#ifndef RAY_H
#define RAY_H

#include "vector.h"

typedef struct ray_struct {
  vector orig;
  vector dir;
} ray;

vector ray_at(ray v, double t);
vector shootRay(ray v, int depth);

#endif
