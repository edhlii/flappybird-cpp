#pragma once

#include "raylib.h"

class Pipe {
 private:
  double posXBot, posYBot;
  double posXTop, posYTop;
  double spaceWidth;
  int direction = 1;

 public:
  bool scoreIncreased = 0;
  int timer = 1;
  Pipe();
  double getPosXBot();
  double getPosYBot();
  double getPosXTop();
  double getPosYTop();
  double getSpaceWidth();
  int getDirection();
  void setPosXBot(double posX);
  void setPosYBot(double posY);
  void setPosXTop(double posX);
  void setPosYTop(double posY);
  void setSpaceWidth(double spaceWidth);
  void setDirection(int direction);
  void updatePosition();
};