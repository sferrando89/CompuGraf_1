#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <stdio.h>
#include "Vector3.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int S_RADIO = 10;

//Vector3 mapCenter;

bool initSDL();
/*Initialize SDL*/

bool initGL();
/*
Pre Condition:
 -A valid OpenGL context
Post Condition:
 -Initializes matrices and clear color
 -Reports to console if there was an OpenGL error
 -Returns false if there was an error in initialization
Side Effects:
 -Projection matrix is set to identity matrix
 -Modelview matrix is set to identity matrix
 -Matrix mode is set to modelview
 -Clear color is set to black
*/

void update();
/*
Pre Condition:
 -None
Post Condition:
 -Does per frame logic
Side Effects:
 -None
*/

int render();
/*
Pre Condition:
 -A valid OpenGL context
 -Active modelview matrix
Post Condition:
 -Renders the scene
Side Effects:
 -Clears the color buffer
 -Swaps the front/back buffer
*/

void updateCamera3d();
void updateCamera2d();

void renderTextTexture(GLuint texture, int x, int y);

void renderHud();

void renderSettings();

void renderMap();

void renderPlayer();

void renderEnemy();

Uint32 getAvgFrames();