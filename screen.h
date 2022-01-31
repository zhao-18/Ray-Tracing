#ifndef SCREEN_H
#define SCREEN_H

typedef struct screen_struct {
  double** view;
  int height;
  int width;
} screen;

double** createScr(int height, int width);
void deleteScr(screen* scr);
void printScr(screen scr);

#endif
