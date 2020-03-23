#include "../src/wiz3d.h"
#include <math.h>

#define ROTATION_SPEED 32
#define TEXT "Frank by misterdevious is licensed under CC Attribution-NonCommercial-ShareAlike"

int main() {
    /* Data */
    Viewer* viewer;
    Light* dir_light;
    Light* point_light1;
    Light* point_light2;
    Object* angel;
    float value = 0;

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Angel");

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzSetViewerClearColor(viewer, wzGetRGB(15, 15, 15));
    wzSetViewerPosition(viewer, 7, 7, -7);
    wzViewerLookAt(viewer, 0, 0, 0);

    /* Setup lighting */
    wzSetAmbientColor(wzGetRGB(15, 15, 15));
    dir_light = wzCreateLight(LIGHT_DIRECTIONAL);
    wzSetLightColor(dir_light, wzGetRGB(100, 100, 100));
    point_light1 = wzCreateLight(LIGHT_POINT);
    wzSetLightPosition(point_light1, 0, 0, -2);
    wzSetLightColor(point_light1, wzGetRGB(255, 100, 0));
    point_light2 = wzCreateLight(LIGHT_POINT);
    wzSetLightPosition(point_light2, 0, 8, 4);
    wzSetLightColor(point_light2, wzGetRGB(0, 100, 255));

    /* Load object (contains embedded texture) */
    angel = wzLoadObject("data/angel.assbin");
    wzTurnObject(angel, 90, 0, 0);

    /* main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        float s, c;

        /* Rotate statue */
        wzTurnObject(angel, 0, ROTATION_SPEED * wzGetDeltaTime(), 0);

        /* Update lighting */
        value += wzGetDeltaTime();
        s = 0.5f + fabsf(sinf(value)) * 0.5f;
        c = 0.5f + fabsf(cosf(value)) * 0.5f;
        wzSetLightLinearAttenuation(point_light1, 1.0f / (10 * s));
        wzSetLightLinearAttenuation(point_light2, 1.0f / (10 * c));

        /* Draw scene */
        wzPrepareViewer(viewer);
        wzDrawObject(angel);

        /* Draw UI */
        wzSetup2D();
        wzSetDrawColor(wzGetRGB(240, 240, 240));
        wzDrawText(TEXT, (wzGetScreenWidth() - wzGetTextWidth(TEXT)) / 2, 8);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
