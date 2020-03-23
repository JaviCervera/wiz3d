#include "../src/wiz3d.h"

int main() {
    /* Data */
    Object* floor;
    Object* ball;
    Object* block;
    Object* ball_shadow;
    Object* block_shadow;
    Viewer* viewer;
    Light* dir_light;
    int direction = 1;

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Collisions");

    /* Create floor */
    floor = wzCreateCube();
    wzMoveObject(floor, 0, -0.5f, 4);
    wzSetObjectCollision(floor, COL_BOX);
    wzSetObjectScale(floor, 20, 1, 20);
    wzSetMaterialDiffuse(wzGetObjectMaterial(floor, 0), COLOR_BLUE);

    /* Load ball */
    ball = wzLoadObject("data/sphere.assbin");
    wzMoveObject(ball, 0, 0.5f, -4);
    wzSetObjectCollision(ball, COL_SPHERE);
    wzSetObjectRadius(ball, 0.5f);
    wzSetMaterialDiffuse(wzGetObjectMaterial(ball, 0), COLOR_RED);

    /* Create block */
    block = wzCreateCube();
    wzMoveObject(block, 0, 2, 0);
    wzSetObjectCollision(block, COL_BOX);
    wzSetObjectScale(block, 4, 4, 1);
    wzSetMaterialDiffuse(wzGetObjectMaterial(block, 0), COLOR_LIGHTGRAY);

    /* Create ball shadow */
    ball_shadow = wzCreateQuad();
    wzSetObjectRotation(ball_shadow, 90, 0, 0);
    wzSetMaterialTexture(wzGetObjectMaterial(ball_shadow, 0), wzLoadTexture("data/circle_shadow.png"));
    wzSetMaterialDiffuse(wzGetObjectMaterial(ball_shadow, 0), COLOR_BLACK);
    wzSetMaterialBlend(wzGetObjectMaterial(ball_shadow, 0), BLEND_ALPHA);

    /* Create block shadow */
    block_shadow = wzCreateQuad();
    wzSetObjectRotation(block_shadow, 90, 0, 0);
    wzSetObjectScale(block_shadow, 4, 1, 1);
    wzSetMaterialDiffuse(wzGetObjectMaterial(block_shadow, 0), COLOR_LIGHTGRAY);
    wzSetMaterialBlend(wzGetObjectMaterial(block_shadow, 0), BLEND_MUL);

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzMoveViewer(viewer, 0, 7, -8);
    wzTurnViewer(viewer, 45, 0, 0);

    /* Setup lighting */
    wzSetAmbientColor(COLOR_LIGHTGRAY);
    dir_light = wzCreateLight(LIGHT_DIRECTIONAL);
    wzSetLightRotation(dir_light, 15, 60);

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        /* Move ball */
        if (wzIsKeyPressed(KEY_UP)) wzMoveObject(ball, 0, 0, 2 * wzGetDeltaTime());
        if (wzIsKeyPressed(KEY_DOWN)) wzMoveObject(ball, 0, 0, -2 * wzGetDeltaTime());
        if (wzIsKeyPressed(KEY_LEFT)) wzMoveObject(ball, -2 * wzGetDeltaTime(), 0, 0);
        if (wzIsKeyPressed(KEY_RIGHT)) wzMoveObject(ball, 2 * wzGetDeltaTime(), 0, 0);

        /* Move block */
        wzMoveObject(block, 0, 2 * direction * wzGetDeltaTime(), 0);
        if (wzGetObjectY(block) >= 4) {
            wzSetObjectPosition(block, wzGetObjectX(block), 4, wzGetObjectZ(block));
            direction = -1;
        }
        if (wzObjectCollidesObject(block, floor) || wzObjectCollidesObject(block, ball)) {
            direction = 1;
        }

        /* Update shadows */
        wzSetObjectPosition(ball_shadow, wzGetObjectX(ball), 0, wzGetObjectZ(ball));
        wzSetObjectPosition(block_shadow, wzGetObjectX(block), 0, wzGetObjectZ(block));

        /* Draw scene */
        wzPrepareViewer(viewer);
        wzDrawObject(floor);
        wzDrawObject(ball);
        wzDrawObject(block);
        wzDrawObject(block_shadow);
        wzDrawObject(ball_shadow);

        /* Draw UI */
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
