#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector_struct {
  double x;
  double y;
  double z;
} vector;

void fill_value(vector* vec, double x, double y, double z);
vector add_const(vector vec, double n);
vector add_vect(vector vec1, vector vec2);
vector subtract_const(vector vec, double n);
vector subtract_vect(vector vec1, vector vec2);
vector mult_const(vector vec, double n);
vector mult_vect(vector vec1, vector vec2);
vector div_const(vector vec, double n);
vector div_vect(vector vec1, vector vec2);
vector cross(vector vec1, vector vec2);
double dot(vector vec1, vector vec2);
vector rotateX(vector r, double degree);
vector rotateY(vector r, double degree);
vector rotateZ(vector r, double degree);
vector unit_vec(vector vec);
double length(vector vec);

#endif
