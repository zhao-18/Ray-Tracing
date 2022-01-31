#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

//All utilities

#define PI 3.14159265

void fill_value(vector* vec, double x, double y, double z) {
  vec->x = x;
  vec->y = y;
  vec->z = z;
  return;
}

vector add_const(vector vec, double n) {
  vec.x = vec.x + n;
  vec.y = vec.y + n;
  vec.z = vec.z + n;
  return vec;
}

vector add_vect(vector vec1, vector vec2) {
  vector vec3;
  vec3.x = vec1.x + vec2.x;
  vec3.y = vec1.y + vec2.y;
  vec3.z = vec1.z + vec2.z;
  return vec3;
}

vector subtract_const(vector vec, double n) {
  vec.x = vec.x - n;
  vec.y = vec.y - n;
  vec.z = vec.z - n;
  return vec;
}

vector subtract_vect(vector vec1, vector vec2) {
  vector vec3;
  vec3.x = vec1.x - vec2.x;
  vec3.y = vec1.y - vec2.y;
  vec3.z = vec1.z - vec2.z;
  return vec3;
}

vector mult_const(vector vec, double n) {
  vec.x = n * vec.x;
  vec.y = n * vec.y;
  vec.z = n * vec.z;
  return vec;
}

vector mult_vect(vector vec1, vector vec2) {
  vector vec3;
  vec3.x = vec1.x * vec2.x;
  vec3.y = vec1.y * vec2.y;
  vec3.z = vec1.z * vec2.z;
  return vec3;
}

vector div_const(vector vec, double n) {
  vec.x = vec.x / n;
  vec.y = vec.y / n;
  vec.z = vec.z / n;
  return vec;
}

vector div_vect(vector vec1, vector vec2) {
  vector vec3;
  vec3.x = vec1.x / vec2.x;
  vec3.y = vec1.y / vec2.y;
  vec3.z = vec1.z / vec2.z;
  return vec3;
}

vector cross(vector vec1, vector vec2) {
  vector vec3;
  vec3.x = vec1.y * vec2.z - vec1.z * vec2.y;
  vec3.y = vec1.z * vec2.x - vec1.x * vec2.z;
  vec3.z = vec1.x * vec2.y - vec1.y * vec2.x;
  return vec3;
}

double dot(vector vec1, vector vec2) {
  return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

vector rotateX(vector r, double degree) {
  vector result;
  double theta = degree * PI / 180;
  double sinTheta = sin(theta);
  double cosTheta = cos(theta);
  double x = r.x;
  double y = r.y * cosTheta - r.z * sinTheta;
  double z = r.y * sinTheta + r.z * cosTheta;
  fill_value(&result, x, y, z);
  return result;
}

vector rotateY(vector r, double degree) {
  vector result;
  double theta = degree * PI / 180;
  double sinTheta = sin(theta);
  double cosTheta = cos(theta);
  double x = r.x * cosTheta + r.z * sinTheta;
  double y = r.y;
  double z = -1 * r.x * sinTheta + r.z * cosTheta;
  fill_value(&result, x, y, z);
  return result;
}

vector rotateZ(vector r, double degree) {
  vector result;
  double theta = degree * PI / 180;
  double sinTheta = sin(theta);
  double cosTheta = cos(theta);
  double x = r.x * cosTheta - r.y * sinTheta;
  double y = r.x * sinTheta + r.y * cosTheta;
  double z = r.z;
  fill_value(&result, x, y, z);
  return result;
}

double length(vector vec) {
  return sqrt(dot(vec, vec));
}

vector unit_vec(vector vec) {
  return div_const(vec, length(vec));
}
