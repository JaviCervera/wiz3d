#include "../src/wiz3d.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_BILLBOARDS 64
#define ROTATION_SPEED 32

int main() {
    /* Data */
    Viewer* viewer;
    Texture* tex;
    Object* billboards[NUM_BILLBOARDS];
    int x, z;
    int i;
    char str[STRING_SIZE];

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Billboards");

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzSetViewerClearColor(viewer, COLOR_WHITE);
    wzSetViewerRotation(viewer, 45, -45, 0);

    /* Load texture */
    tex = wzLoadTexture("data/smile.png");

    /* Create billboards */
    x = z = -8;
    for (i = 0; i < NUM_BILLBOARDS; ++i) {
        Material* material;

        billboards[i] = wzCreateQuad();
        wzSetObjectPosition(billboards[i], x, 0, z);
        material = wzGetObjectMaterial(billboards[i], 0);
        wzSetMaterialTexture(material, tex);
        wzSetMaterialDiffuse(material, wzGetRGB(rand() % 256, rand() % 256, rand() % 256));
        wzSetMaterialBlend(material, BLEND_ALPHA);
        
        x += 2;
        if (x >= 8) {
            x = -8;
            z += 2;
        }
    }

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        /* Update viewer */
        wzTurnViewer(viewer, 0, ROTATION_SPEED * wzGetDeltaTime(), 0);
        wzSetViewerPosition(viewer, 0, 0, 0);
        wzMoveViewer(viewer, 0, 0, -8);

        /* Update billboards */
        for (i = 0; i < NUM_BILLBOARDS; ++i) {
            wzObjectLookAt(billboards[i], wzGetViewerX(viewer), wzGetViewerY(viewer), wzGetViewerZ(viewer));
        }

        /* Draw scene */
        wzPrepareViewer(viewer);
        for (i = 0; i < NUM_BILLBOARDS; ++i) {
            wzDrawObject(billboards[i]);
        }

        /* Draw UI */
        sprintf(str, "%i FPS", wzGetScreenFPS());
        wzSetup2D();
        wzSetDrawColor(COLOR_BLACK);
        wzDrawText(str, 4, 4);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
