#pragma once

#include "raylib.h"

class Pipe {
public:
  double posX, posY;
  double spaceWidth;
  bool scoreIncreased = 0;
  Pipe();
};