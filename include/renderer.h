#pragma once

#include <iostream>
#include <vector>

#include "bird.h"
#include "common.h"
#include "pipe.h"
#include "pipeManager.h"
#include "raylib.h"
#include "resource_dir.h"

class Renderer {
 private:
  static Texture birdTexture;
  static Texture pipeTexture;
  static Texture backgroundTexture;

 public:
  static void LoadTexture();
  static void RenderPipes(PipeManager& pipeManager);
  static void RenderBird(Bird* bird);
  static void Render(Bird* bird, PipeManager& pipeManager, int currentState,
                     int score);
};