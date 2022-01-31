#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "ray.h"

//Ray at given t. Returns the point wherever the ray points to.
vector ray_at(ray v, double t) {
  vector u = add_vect(v.orig, mult_const(v.dir, t));
  return u;
}

/*
 * Formula for a sphere of radius r, centered at C(Cx, Cy, Cz) is
 * (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = r^2
 *
 * This can be expressed with dot product of arbitrary point P(x, y, z) and the center C(Cx, Cy, Cz)
 * (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2
 *  = (x - Cx)*(x - Cx) + (y - Cy)*(y - Cy) + (z - Cz)*(z - Cz)
 *  = (P - C)・(P - C)
 *  = r^2
 *
 * P is the point where a ray hits. There has to be a t to express P using vector.
 * V is a direction vector.
 * b is where V is shooting from.
 * P(t) = tV + b. P is t's function, so it should be P(t) instead of P.
 *
 * (P - C)・(P - C) = (P(t) - C)・(P(t) - C)
 * Expand P(t)
 * (P(t) - C)・(P(t) - C)
 *  = (tV + (b - C))・(tV + (b - C))  Group b and - C.
 *  = r^2
 *
 * Expand the entire expression & move r^2 to the left side.
 * t^2 V・V + 2t(b - C)・V + (b - C)・(b - C) - r^2 = 0
 *
 * It's a quadratic formula of t. Use determinant to see if there is a answer for t.
 * If so, ray hits sphere. Return one of the answer.
 * We aren't going to see backside anyways, We only need the one comes in front.
 */
double sphere(vector const centre, double const radius, ray const r) {
  vector distance = subtract_vect(r.orig, centre);
  double a = dot(r.dir, r.dir);
  double b = 2 * (dot(r.dir, distance));
  double c = dot(distance, distance) - radius * radius;
  double discriminant = b*b - 4*a*c;
  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-b - sqrt(discriminant)) / (2.0 * a);
  }
}

vector shootRay(ray v, int depth) {
  /*
   * Adding a limit to how many times the ray are allowed to reflect.
   */
  if (depth < 1) {
    vector col;
    fill_value(&col, 1, 1, 1);
    return col;
  }

  vector sphere1;
  fill_value(&sphere1, 0, 0, -1.0);  //Center
  double t = sphere(sphere1, 0.5, v);  //Center position, radius, and target ray
  if (t > 0.0) {  //If the ray hits sphere,
    vector n = unit_vec(subtract_vect(ray_at(v, t), sphere1));
    /*
     * Color the sphere based on direction of normal vector(-1 < x, y, z < 1).
     * When x, y, and z is positive, the surface appears brighter.
     * When x, y, and z is negative, the surface appears darker.
     */
    vector col = add_const(n, 1);
    return col;
  }

  vector sphere2;
  fill_value(&sphere2, 1, 0.5, -1.5);//Center
  t = sphere(sphere2, 0.5, v);
  if (t > 0.0) {
    vector n = unit_vec(subtract_vect(ray_at(v, t), sphere2));
    //Create a Ray shooting from where original ray hits in the direction of normal vector.
    //This is inaccurate but accurate enough for humans.
    ray nRay;
    nRay.orig = ray_at(v, t);
    nRay.dir = n;
    //Determine the color of the point using recursion.
    vector col = shootRay(nRay, depth - 1);
    return col;
  }

  vector sphere3;
  fill_value(&sphere3, -1.5, 0.5, -0.5);//Center
  t = sphere(sphere3, 0.8, v);
  if (t > 0.0) {
    vector n = unit_vec(subtract_vect(ray_at(v, t), sphere3));
    ray nRay;
    nRay.orig = ray_at(v, t);
    nRay.dir = n;
    vector col = shootRay(nRay, depth - 1);
    return col;
  }

  //Ground is just a huge sphere.
  vector ground;
  fill_value(&ground, 0, -100.5, 0);
  t = sphere(ground, 100, v);
  if (t > 0.0) {
    vector n = unit_vec(subtract_vect(ray_at(v, t), ground));
    vector col;

    //Add checker pattern based on normal vector's direction. Given direction times 1000 and see if that is odd or even.
    //Increase the number multiplied to direction make the grid finer.
    if ((int)(n.x * 1000) % 2 == 0 && (int)(n.z * 1000) % 2 == 0) {
      fill_value(&col, 1, 1, 1);
    } else if ((int)(n.x * 1000 + 1) % 2 == 0 && (int)(n.z * 1000 + 1) % 2 == 0) {
      fill_value(&col, 1, 1, 1);
    } else {
      fill_value(&col, 0, 0, 0);
    }

    return col;
  }

  //Add sky with gradient based on ray's y value.
  /*vector unitDir = unit_vec(v.dir);  //-1 <= y <= 1
  t = unitDir.y + 1;  // 0 <= y <= 2

  vector col1;
  fill_value(&col1, 1.0, 1.0, 1.0);
  vector col2;
  fill_value(&col2, 0.5, 0.7, 1.0);

  return add_vect(mult_const(col1, (2 - t)), mult_const(col2, t));*/

  vector col1;
  fill_value(&col1, 0, 0, 0);
  return col1;
}
