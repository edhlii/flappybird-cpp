#pragma once
#include <vector>

#include "common.h"
#include "pipe.h"

class PipeManager {
 private:
  std::vector<Pipe*> pipes;

 public:
  PipeManager();
  std::vector<Pipe*> getPipeList();
  void updatePipeQueue();
  void updatePipePosition();
  void reset();
};