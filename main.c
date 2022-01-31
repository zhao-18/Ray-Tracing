#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "ray.h"

int const DEPTH = 20;

/* This fits in my screen. Adjust the amount of characters to be printed. */
int const WIDTH = 470;
int const HEIGHT = 162;
//double const ASPECT_RATIO = WIDTH/HEIGHT;
double const ASPECT_RATIO = 470/162;

double greyscale(vector color) {
  //Definition of Greyscale
  return 0.2126*color.x + 0.7152*color.y + 0.0722*color.z;
}

int main(int argc, char const *argv[]) {
  /* Create screen. Just a Matrix */
  screen scr;
  scr.width = WIDTH;
  scr.height = HEIGHT;
  scr.view = createScr(scr.height, scr.width);

  /* Convert into whatever unit used in the 3D space */
  double viewport_height = 2.0;
  double viewport_width = ASPECT_RATIO * viewport_height;

  /* Field of View. Small number to make scene wider */
  double focalLength = 1.2;

  /* Position of Camera */
  vector origin;
  fill_value(&origin, 0, 0, 0);

  /* Width element */
  vector horizontal;
  fill_value(&horizontal, viewport_width, 0, 0);

  /* Height element */
  vector vertical;
  fill_value(&vertical, 0, viewport_height, 0);

  /* Length element */
  vector length;
  fill_value(&length, 0, 0, focalLength);

  char input = '?';

  do {
    vector lower_left_corner;
    //lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - length
    lower_left_corner = subtract_vect(subtract_vect(subtract_vect(origin, div_const(horizontal, 2)), div_const(vertical, 2)), length);

    /* Going through every bit of screen. */
    for (size_t i = 0; i < scr.height; i++) {
      for (size_t j = 0; j < scr.width; j++) {

        /* Determine the point where a ray should point to */
        double u = (double)i / (scr.height - 1);
        double v = (double)j / (scr.width - 1);

        /* Create a ray with origin at camera position */
        ray r;
        r.orig = origin;

        //r.dir = lower_left_corner + u*vertical + v*horizontal - origin
        //By subtracting the origin, the direction become relative.
        r.dir = subtract_vect(add_vect(lower_left_corner, add_vect(mult_const(vertical, u), mult_const(horizontal, v))), origin);

        /* SHOOT THE RAY */
        vector color = shootRay(r, DEPTH);

        /* Convert into greyscale */
        scr.view[i][j] = greyscale(mult_const(color, 255 * 0.5));

      }
    }
    printScr(scr);

    /* movement */
    //Note that the direction is global and not relative to current camera position / angle.
    scanf(" %c", &input);

    if (input == 'w') {
      fill_value(&origin, origin.x, origin.y, origin.z - 0.2);

    } else if (input == 's') {
      fill_value(&origin, origin.x, origin.y, origin.z + 0.2);

    } else if (input == 'd') {
      fill_value(&origin, origin.x + 0.2, origin.y, origin.z);

    } else if (input == 'a') {
      fill_value(&origin, origin.x - 0.2, origin.y, origin.z);

    } else if (input == 'A') {
      horizontal = rotateY(horizontal, 10);
      vertical = rotateY(vertical, 10);
      length = rotateY(length, 10);

    } else if (input == 'D') {
      horizontal = rotateY(horizontal, -10);
      vertical = rotateY(vertical, -10);
      length = rotateY(length, -10);

    } else if (input == 'W') {
      horizontal = rotateX(horizontal, 10);
      vertical = rotateX(vertical, 10);
      length = rotateX(length, 10);

    } else if (input == 'S') {
      horizontal = rotateX(horizontal, -10);
      vertical = rotateX(vertical, -10);
      length = rotateX(length, -10);

    } else if (input == 'Q') {
      horizontal = rotateZ(horizontal, 10);
      vertical = rotateZ(vertical, 10);
      length = rotateZ(length, 10);

    } else if (input == 'E') {
      horizontal = rotateZ(horizontal, -10);
      vertical = rotateZ(vertical, -10);
      length = rotateZ(length, -10);
    }

  } while(input != 'q');

  deleteScr(&scr);
  return 0;
}
