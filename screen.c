#include <stdio.h>
#include <stdlib.h>
#include "screen.h"

double** createScr(int height, int width) {
  double** scr = (double**)calloc(height, sizeof(double*));
  for (size_t row = 0; row < height; row++) {
    scr[row] = (double*)calloc(width, sizeof(double));
  }
  return scr;
}

void deleteScr(screen* scr) {
  for (size_t height = 0; height < scr->height; height++) {
    free((scr->view)[height]);
    (scr->view)[height] = NULL;
  }
  free(scr->view);
  scr->view = NULL;
  return;
}

void printScr(screen scr) {
  for (size_t i = scr.height-1; i >0 ; i--) {
    for (size_t j = 0; j < scr.width; j++) {
      if (scr.view[i][j] < 15) {
        printf("一");
      } else if (scr.view[i][j] < 30) {
        printf("..");
      } else if (scr.view[i][j] < 45) {
        printf("--");
      } else if (scr.view[i][j] < 60) {
        printf("!!");
      } else if (scr.view[i][j] < 75) {
        printf("++");
      } else if (scr.view[i][j] < 90) {
        printf("亥");
      } else if (scr.view[i][j] < 105) {
        printf("得");
      } else if (scr.view[i][j] < 120) {
        printf("譜");
      } else if (scr.view[i][j] < 135) {
        printf("??");
      } else if (scr.view[i][j] < 150) {
        printf("嘩");
      } else if (scr.view[i][j] < 165) {
        printf("==");
      } else if (scr.view[i][j] < 180) {
        printf("##");
      } else if (scr.view[i][j] < 195) {
        printf("HH");//
      } else if (scr.view[i][j] < 210) {
        printf("@@");//
      } else if (scr.view[i][j] < 225) {
        printf("MM");//
      } else if (scr.view[i][j] < 240) {
        printf("WW");
      } else {
        printf("88");
      }
    }
    printf("\n");
  }
}
