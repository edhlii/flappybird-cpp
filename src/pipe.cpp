#include "pipe.h"

#include "common.h"
#include <iostream>

Pipe::Pipe() {
  std::random_device rd;
  std::mt19937 gen(rd());
  // spaceWidth = randomDouble(200, 300, gen);
  direction = round(randomDouble(0, 1, gen));

  posYBot = randomDouble(MIN_PIPE_Y, MAX_PIPE_Y, gen);
  posXBot = posXTop = WINDOW_WIDTH + PIPE_WIDTH;
  posYTop = posYBot - PIPE_GAP - PIPE_HEIGHT;
  // std::cout << posYTop  << std::endl;
  // posYTop = posYBot;

  // Check pipe out of window
  // if (posYBot + PIPE_HEIGHT <= WINDOW_HEIGHT)
  //   posYBot = WINDOW_HEIGHT - PIPE_HEIGHT;
  // if (posYTop >= 0)
  //   posYTop = 0;
}

double Pipe::getPosXBot() { return posXBot; }
double Pipe::getPosYBot() { return posYBot; }
double Pipe::getPosXTop() { return posXTop; }
double Pipe::getPosYTop() { return posYTop; }
double Pipe::getSpaceWidth() { return spaceWidth; }
int Pipe::getDirection() { return direction; }

void Pipe::setPosXBot(double posX) { this->posXBot = posX; }
void Pipe::setPosYBot(double posY) { this->posYBot = posY; }
void Pipe::setPosXTop(double posX) { this->posXTop = posX; }
void Pipe::setPosYTop(double posY) { this->posYTop = posY; }
void Pipe::setSpaceWidth(double spaceWidth) { this->spaceWidth = spaceWidth; }
void Pipe::setDirection(int direction) { this->direction = direction; }

void Pipe::moveHorizontal() {
  posYBot += direction * PIPE_Y_VELOCITY;

  if (posYBot + PIPE_HEIGHT <= WINDOW_HEIGHT) {
    posYBot = WINDOW_HEIGHT - PIPE_HEIGHT;
    direction = 1;
  }
  if (posYTop >= -GROUND_HEIGHT - 200) {
    posYTop = -GROUND_HEIGHT - 200;
    direction = -1;
  }

  posYTop = posYBot - spaceWidth - PIPE_HEIGHT;
}

void Pipe::updatePosition() {
  if (isMoveHorizontal)
    moveHorizontal();
  posYTop = posYBot - PIPE_GAP - PIPE_HEIGHT;

  posXBot -= PIPE_X_VELOCITY;
  posXTop = posXBot;
}
