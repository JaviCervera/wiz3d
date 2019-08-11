#include "../src/beam.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_BILLBOARDS 64
#define ROTATION_SPEED 32

int main()
{
  /* data */
  Viewer* viewer;
  struct STexture* tex;
  Object* billboards[NUM_BILLBOARDS];
  int x, z;
  int i;
  char str[STRING_SIZE];

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = CreateViewer();
  viewer->clearcolor = COLOR_WHITE;
  TurnViewer(viewer, 45, -45, 0);

  /* load texture */
  tex = LoadTexture("data/smile.png");

  /* create billboards */
  x = z = -8;
  for (i = 0; i < NUM_BILLBOARDS; ++i)
  {
    billboards[i] = CreateQuad();
    billboards[i]->x = x;
    billboards[i]->z = z;
    GetObjectMaterial(billboards[i], 0)->texture = tex;
    GetObjectMaterial(billboards[i], 0)->diffuse = GetRGB(rand() % 256, rand() % 256, rand() % 256);
    GetObjectMaterial(billboards[i], 0)->blend = BLEND_ALPHA;
    
    x += 2;
    if (x >= 8)
    {
      x = -8;
      z += 2;
    }
  }

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    /* update viewer */
    TurnViewer(viewer, 0, ROTATION_SPEED * GetDeltaTime(), 0);
    viewer->x = viewer->y = viewer->z = 0;
    MoveViewer(viewer, 0, 0, -8);

    /* update billboards */
    for (i = 0; i < NUM_BILLBOARDS; ++i)
    {
      ObjectLookAt(billboards[i], viewer->x, viewer->y, viewer->z);
    }

    /* draw scene */
    PrepareViewer(viewer);
    for (i = 0; i < NUM_BILLBOARDS; ++i)
    {
      DrawObject(billboards[i]);
    }

    /* draw ui */
    sprintf(str, "%i FPS", GetScreenFPS());
    Setup2D();
    SetDrawColor(COLOR_BLACK);
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
