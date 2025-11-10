#include "bird.h"

#include "common.h"

Bird::Bird() { reset(); }

void Bird::reset() {
  setPosX(100);
  setPosY(WINDOW_HEIGHT / 2);
  dead = 0;
}

double Bird::getPosX() { return posX; }
double Bird::getPosY() { return posY; }
double Bird::getVelocity() { return velocity; }
bool Bird::isDead() { return dead; }

void Bird::setPosX(double posX) { this->posX = posX; }
void Bird::setPosY(double posY) { this->posY = posY; }
void Bird::setVelocity(double velocity) { this->velocity = velocity; }
void Bird::setDead(bool dead) { this->dead = dead; }

void Bird::updatePosition() {
  velocity += GRAVITY;
  posY += velocity;
  return;
}

void Bird::flap() { velocity = -JUMP_FORCE; }