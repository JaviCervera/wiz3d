#include "../src/wiz3d.h"

#define ROTATION_SPEED 32
#define TEXT "Hover Bike by Ptis is licensed under CC Attribution-NonCommercial"

int main() {
    /* Data */
    Viewer* viewer;
    Light* dir_light;
    Object* hoverbike;
    Material* mat0;
    Material* mat1;

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Hoverbike");

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzSetViewerClearMode(viewer, CLEAR_SKYBOX);
    wzSetViewerSkybox(viewer, wzLoadTexture("data/skybox.png"));
    wzSetViewerPosition(viewer, 0, 4, -8);
    wzSetViewerRotation(viewer, 20, 0, 0);

    /* Setup lighting */
    dir_light = wzCreateLight(LIGHT_DIRECTIONAL);
    wzSetLightSpecularColored(dir_light, FALSE);
    wzTurnLight(dir_light, 45, -45);

    /* Load hoverbike */
    hoverbike = wzLoadObject("data/hoverbike.assbin");
    wzSetObjectScale(hoverbike, 0.025f, 0.025f, 0.025f);
    mat0 = wzGetObjectMaterial(hoverbike, 0);
    mat1 = wzGetObjectMaterial(hoverbike, 1);
    wzSetMaterialTexture(mat0, wzLoadTexture("data/bike.png"));
    wzSetMaterialDiffuse(mat0, COLOR_WHITE);
    wzSetMaterialSpecular(mat0, COLOR_WHITE);
    wzSetMaterialShininess(mat0, 0.95f);
    wzSetMaterialTexture(mat1, wzLoadTexture("data/glass.png"));
    wzSetMaterialDiffuse(mat1, COLOR_WHITE);
    wzSetMaterialSpecular(mat1, COLOR_WHITE);
    wzSetMaterialShininess(mat1, 0.99f);
    wzSetMaterialBlend(mat1, BLEND_ALPHA);

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        /* Turn hoverbike */
        wzTurnObject(hoverbike, 0, ROTATION_SPEED * wzGetDeltaTime(), 0);

        /* Draw scene */
        wzPrepareViewer(viewer);
        wzDrawObject(hoverbike);

        /* Draw UI */
        wzSetup2D();
        wzSetDrawColor(wzGetRGB(240, 240, 240));
        wzDrawText(TEXT, (wzGetScreenWidth() - wzGetTextWidth(TEXT)) / 2, 8);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
