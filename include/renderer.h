#pragma once

#include <iostream>
#include <vector>

#include "agent.h"
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
  static Texture groundTexture;

public:
  static void LoadAllTexture();
  static void UnloadAllTexture();
  static void RenderPipes(PipeManager &pipeManager);
  static void RenderBird(Bird *bird);
  static void RenderGround(float groundX);
  static void RenderPlayer(Bird *bird, PipeManager &pipeManager,
                           int currentState, int score, float groundX1,
                           float groundX2);
  static void RenderAgent0(Agent *agent, PipeManager &pipeManager,
                           int currentState, int score, float groundX1,
                           float groundX2);
  static void RenderAgent1(std::vector<Agent *> agents,
                           PipeManager &pipeManager, int currentState,
                           int score, float groundX1, float groundX2);
};