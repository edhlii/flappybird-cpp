#include "pipe.h"
#include "common.h"

Pipe::Pipe() {
  std::random_device rd;
  std::mt19937 gen(rd());
  posY = randomDouble(WINDOW_HEIGHT / 2, WINDOW_HEIGHT, gen);
  posX = WINDOW_WIDTH + PIPE_WIDTH;
  spaceWidth = randomDouble(PIPE_HEIGHT / 4, 2 * PIPE_HEIGHT / 3, gen);
}
