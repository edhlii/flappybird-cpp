#pragma once

#include "raylib.h"

class Bird {
 private:
  double posX;
  double posY;
  double velocity = 0;
  bool dead = 0;

 public:
  Bird();
  void reset();
  double getPosX();
  double getPosY();
  double getVelocity();
  bool isDead();
  void setPosX(double posX);
  void setPosY(double posY);
  double setVelocity(double velocity);
  void setDead(bool dead);
};