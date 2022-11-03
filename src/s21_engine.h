#ifndef SRC_S21_ENGINE_H_
#define SRC_S21_ENGINE_H_

#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum errors { S21_OK, S21_FAIL, S21_MALLOC, S21_REALLOC, S21_FILE };

typedef struct Vector4D {
  float x;
  float y;
  float z;
  float w;
} vector;

#endif  // SRC_S21_ENGINE_H_