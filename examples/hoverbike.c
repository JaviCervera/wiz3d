#include "../src/beam.h"

#define ROTATION_SPEED 32
#define TEXT "Hover Bike by Ptis is licensed under CC Attribution-NonCommercial"

int main()
{
  /* data */
  Viewer* viewer;
  Light* dir_light;
  Object* hoverbike;
  Material* mat0;
  Material* mat1;

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = CreateViewer();
  viewer->clearmode = CLEAR_SKYBOX;
  viewer->skybox = LoadTexture("data/skybox.png");
  MoveViewer(viewer, 0, 4, -8);
  TurnViewer(viewer, 20, 0, 0);

  /* setup lighting */
  SetShininessPower(2);
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  TurnLight(dir_light, 45, -45);

  /* load hoverbike */
  hoverbike = LoadObject("data/hoverbike.assbin");
  hoverbike->sx = hoverbike->sy = hoverbike->sz = 0.025f;
  mat0 = GetObjectMaterial(hoverbike, 0);
  mat1 = GetObjectMaterial(hoverbike, 1);
  mat0->texture = LoadTexture("data/bike.png");
  mat0->diffuse = COLOR_WHITE;
  mat0->specular = COLOR_WHITE;
  mat1->texture = LoadTexture("data/glass.png");
  mat1->diffuse = COLOR_WHITE;
  mat1->specular = COLOR_WHITE;
  mat1->blend = BLEND_ALPHA;

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    /* turn hoverbike */
    TurnObject(hoverbike, 0, ROTATION_SPEED * GetDeltaTime(), 0);

    /* draw scene */
    PrepareViewer(viewer);
    DrawObject(hoverbike);

    /* draw ui */
    Setup2D();
    SetDrawColor(GetRGB(240, 240, 240));
    DrawText(TEXT, (GetScreenWidth() - GetTextWidth(TEXT)) / 2, 8);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
