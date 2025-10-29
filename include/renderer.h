#pragma once

#include <iostream>
#include <vector>

#include "bird.h"
#include "common.h"
#include "pipe.h"
#include "pipeManager.h"
#include "raylib.h"
#include "agent.h"
#include "resource_dir.h"

class Renderer {
private:
  static Texture birdTexture;
  static Texture pipeTexture;
  static Texture backgroundTexture;
  static Texture groundTexture;

public:
  static void LoadAllTexture();
  static void UnloadAllTexture();
  static void RenderPipes(PipeManager &pipeManager);
  static void RenderBird(Bird *bird);
  static void RenderGround();
  static void RenderPlayer(Bird *bird, PipeManager &pipeManager, int currentState,
                         int score);
  static void RenderAI(Agent *agent, PipeManager &pipeManager, int currentState,
                         int score);
};