#pragma once

#include "raylib.h"

class Bird {
public:
  double posX;
  double posY;
  double velocity = 0;
  const int WIDTH = 40, HEIGHT = 35;
};