#include "../src/beam.h"
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
    bmInitBeam();
    bmSetScreen(800, 600, FALSE, TRUE);
    bmSetScreenTitle("Angel");

    /* Create and position viewer */
    viewer = bmCreateViewer();
    bmSetViewerClearColor(viewer, bmGetRGB(15, 15, 15));
    bmSetViewerPosition(viewer, 7, 7, -7);
    bmViewerLookAt(viewer, 0, 0, 0);

    /* Setup lighting */
    bmSetAmbientColor(bmGetRGB(15, 15, 15));
    dir_light = bmCreateLight(LIGHT_DIRECTIONAL);
    bmSetLightColor(dir_light, bmGetRGB(100, 100, 100));
    point_light1 = bmCreateLight(LIGHT_POINT);
    bmSetLightPosition(point_light1, 0, 0, -2);
    bmSetLightColor(point_light1, bmGetRGB(255, 100, 0));
    point_light2 = bmCreateLight(LIGHT_POINT);
    bmSetLightPosition(point_light2, 0, 8, 4);
    bmSetLightColor(point_light2, bmGetRGB(0, 100, 255));

    /* Load object (contains embedded texture) */
    angel = bmLoadObject("data/angel.assbin");
    bmTurnObject(angel, 90, 0, 0);

    /* main loop */
    while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
        float s, c;

        /* Rotate statue */
        bmTurnObject(angel, 0, ROTATION_SPEED * bmGetDeltaTime(), 0);

        /* Update lighting */
        value += bmGetDeltaTime();
        s = 0.5f + fabsf(sinf(value)) * 0.5f;
        c = 0.5f + fabsf(cosf(value)) * 0.5f;
        bmSetLightLinearAttenuation(point_light1, 1.0f / (10 * s));
        bmSetLightLinearAttenuation(point_light2, 1.0f / (10 * c));

        /* Draw scene */
        bmPrepareViewer(viewer);
        bmDrawObject(angel);

        /* Draw UI */
        bmSetup2D();
        bmSetDrawColor(bmGetRGB(240, 240, 240));
        bmDrawText(TEXT, (bmGetScreenWidth() - bmGetTextWidth(TEXT)) / 2, 8);
        bmRefreshScreen();
    }

    /* Shutdown */
    bmShutdownBeam();
}
