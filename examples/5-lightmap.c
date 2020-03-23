#include "../src/wiz3d.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main() {
    /* Data */
    Viewer* viewer;
    Light* dir_light;
    Object* cube;
    Material* material;
    bool_t space_down;
    char str[STRING_SIZE];

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Lightmapping");

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzSetViewerClearColor(viewer, wzGetRGB(15, 15, 15));
    wzSetViewerPosition(viewer, 0, 2, -2);
    wzViewerLookAt(viewer, 0, 0, 0);

    /* Setup lighting */
    wzSetAmbientColor(COLOR_BLACK);
    dir_light = wzCreateLight(LIGHT_DIRECTIONAL);
    wzTurnLight(dir_light, 45, -45);

    /* Create a cube */
    cube = wzCreateCube();
    material = wzGetObjectMaterial(cube, 0);
    wzSetMaterialTexture(material, wzLoadTexture("data/box.png"));
    wzSetMaterialLightmap(material, wzLoadTexture("data/lightmap.png"));

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        /* Update lighting mode */
        if (wzIsKeyPressed(KEY_SPACE)) {
            if (!space_down) {
                if (wzGetMaterialFlags(material) & FLAG_LIGHTING) {
                    wzSetMaterialFlags(material, wzGetMaterialFlags(material) - FLAG_LIGHTING);
                } else {
                    wzSetMaterialFlags(material, wzGetMaterialFlags(material) + FLAG_LIGHTING);
                }
            }
            space_down = TRUE;
        } else {
            space_down = FALSE;
        }

        /* Turn cube */
        wzTurnObject(cube, 0, ROTATION_SPEED * wzGetDeltaTime(), 0);

        /* Draw scene */
        wzPrepareViewer(viewer);
        wzDrawObject(cube);

        /* Draw UI */
        wzSetup2D();
        sprintf(str, "%i FPS", wzGetScreenFPS());
        wzDrawText(str, 4, 4);
        sprintf(str, "Press SPACE to switch dynamic lighting");
        wzDrawText(str, 4, 16);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
