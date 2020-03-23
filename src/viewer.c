#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "viewer.h"
#include "color.h"
#include "light.h"
#include "material.h"
#include "mesh.h"
#include "screen.h"
#include "texture.h"
#include "util.h"
#include <math.h>

typedef struct SViewer {
    float                         x, y, z;
    float                         pitch, yaw, roll;
    int                             vx;
    int                             vy;
    int                             vw;
    int                             vh;
    int                             clearmode;
    int                             clearcolor;
    Texture* skybox;
    bool_t                        ortho;
    float                         fov;
    float                         min;
    float                         max;
    bool_t                        fogenabled;
    int                             fogcolor;
    float                         fogmin;
    float                         fogmax;
} Viewer;

static const Viewer* _view_active_viewer = NULL;
static lmat4_t _view_matrix;
static Mesh* _viewer_skybox = NULL;

static Mesh* _SetupViewerSkyboxMesh(Texture* texture);

EXPORT Viewer* CALL wzCreateViewer() {
    Viewer* viewer = _Alloc(Viewer);
    viewer->x = 0;
    viewer->y = 0;
    viewer->z = 0;
    viewer->pitch = 0;
    viewer->yaw = 0;
    viewer->roll = 0;
    viewer->vx = 0;
    viewer->vy = 0;
    viewer->vw = -1;
    viewer->vh = -1;
    viewer->clearmode = CLEAR_COLOR;
    viewer->clearcolor = wzGetRGB(52, 73, 94);
    viewer->skybox = NULL;
    viewer->ortho = FALSE;
    viewer->fov = 60;
    viewer->min = 1;
    viewer->max = 1000;
    viewer->fogenabled = FALSE;
    viewer->fogcolor = COLOR_DARKGRAY;
    viewer->fogmin = 0;
    viewer->fogmax = 1000;
    return viewer;
}

EXPORT void CALL wzDeleteViewer(Viewer* viewer) { free(viewer); }

EXPORT float CALL wzGetViewerX(const Viewer* viewer) { return viewer->x; }

EXPORT float CALL wzGetViewerY(const Viewer* viewer) { return viewer->y; }

EXPORT float CALL wzGetViewerZ(const Viewer* viewer) { return viewer->z; }

EXPORT void CALL wzSetViewerPosition(Viewer* viewer, float x, float y, float z) {
    viewer->x = x;
    viewer->y = y;
    viewer->z = z;
}

EXPORT void CALL wzMoveViewer(Viewer* viewer, float x, float y, float z) {
    lvec3_t vec;

    vec = lvec3_add(
        lvec3(viewer->x, viewer->y, viewer->z),
        lquat_mulvec3(lquat_fromeuler(lvec3_rad(lvec3(viewer->pitch, viewer->yaw, viewer->roll))), lvec3(x, y, z)));
    viewer->x = vec.x;
    viewer->y = vec.y;
    viewer->z = vec.z;
}

EXPORT float CALL wzGetViewerPitch(const Viewer* viewer) { return viewer->pitch; }

EXPORT float CALL wzGetViewerYaw(const Viewer* viewer) { return viewer->yaw; }

EXPORT float CALL wzGetViewerRoll(const Viewer* viewer) { return viewer->roll; }

EXPORT void CALL wzSetViewerRotation(Viewer* viewer, float pitch, float yaw, float roll) {
    viewer->pitch = pitch;
    viewer->yaw = yaw;
    viewer->roll = roll;
}

EXPORT void CALL wzTurnViewer(Viewer* viewer, float pitch, float yaw, float roll) {
    lvec3_t vec;

    vec = lvec3_add(lvec3(viewer->pitch, viewer->yaw, viewer->roll), lvec3(pitch, yaw, roll));
    viewer->pitch = vec.x;
    viewer->yaw = vec.y;
    viewer->roll = vec.z;
}

EXPORT void CALL wzViewerLookAt(Viewer* viewer, float x, float y, float z) {
    lvec3_t dir;
    dir = lvec3_norm(lvec3_sub(lvec3(x, y, z), lvec3(viewer->x, viewer->y, viewer->z)));
    viewer->pitch = lm_rad2deg((float)asin(-dir.y));
    viewer->yaw = lm_rad2deg((float)atan2(dir.x, dir.z));
}

EXPORT int CALL wzGetViewerViewportX(const Viewer* viewer) { return viewer->vx; }

EXPORT int CALL wzGetViewerViewportY(const Viewer* viewer) { return viewer->vy; }

EXPORT int CALL wzGetViewerViewportWidth(const Viewer* viewer) { return viewer->vw; }

EXPORT int CALL wzGetViewerViewportHeight(const Viewer* viewer) { return viewer->vh; }

EXPORT void CALL wzSetViewerViewport(Viewer* viewer, int x, int y, int width, int height) {
    viewer->vx = x;
    viewer->vy = y;
    viewer->vw = width;
    viewer->vh = height;
}

EXPORT int CALL wzGetViewerClearMode(const Viewer* viewer) { return viewer->clearmode; }

EXPORT void CALL wzSetViewerClearMode(Viewer* viewer, int mode) { viewer->clearmode = _Clamp(mode, CLEAR_NONE, CLEAR_SKYBOX); }

EXPORT int CALL wzGetViewerClearColor(const Viewer* viewer) { return viewer->clearcolor; }

EXPORT void CALL wzSetViewerClearColor(Viewer* viewer, int color) { viewer->clearcolor = color; }

EXPORT Texture* CALL wzGetViewerSkybox(const Viewer* viewer) { return viewer->skybox; }

EXPORT void CALL wzSetViewerSkybox(Viewer* viewer, Texture* texture) { viewer->skybox = texture; }

EXPORT bool_t CALL wzIsViewerOrtho(const Viewer* viewer) { return viewer->ortho; }

EXPORT void CALL wzSetViewerOrtho(Viewer* viewer, bool_t ortho) { viewer->ortho = ortho; }

EXPORT float CALL wzGetViewerFov(const Viewer* viewer) { return viewer->fov; }

EXPORT void CALL wzSetViewerFov(Viewer* viewer, float enable) { viewer->fov = enable; }

EXPORT float CALL wzGetViewerDistanceMin(const Viewer* viewer) { return viewer->min; }

EXPORT float CALL wzGetViewerDistanceMax(const Viewer* viewer) { return viewer->max; }

EXPORT void CALL wzSetViewerDistance(Viewer* viewer, float min, float max) {
    viewer->min = min;
    viewer->max = max;
}

EXPORT bool_t CALL wzIsViewerFogEnabled(const Viewer* viewer) { return viewer->fogenabled; }

EXPORT void CALL wzSetViewerFogEnabled(Viewer* viewer, bool_t enable) { viewer->fogenabled = enable; }

EXPORT int CALL wzGetViewerFogColor(const Viewer* viewer) { return viewer->fogcolor; }

EXPORT void CALL wzSetViewerFogColor(Viewer* viewer, int color) { viewer->fogcolor = color; }

EXPORT float CALL wzGetViewerFogDistanceMin(const Viewer* viewer) { return viewer->fogmin; }

EXPORT float CALL wzGetViewerFogDistanceMax(const Viewer* viewer) { return viewer->fogmax; }

EXPORT void CALL wzSetViewerFogDistance(Viewer* viewer, float min, float max) {
    viewer->fogmin = min;
    viewer->fogmax = max;
}

EXPORT void CALL wzPrepareViewer(const Viewer* viewer) {
    int vp_w;
    int vp_h;
    float ratio;
    float halfrange;
    lmat4_t proj;
    lmat4_t modelview;
    lquat_t q;

    /* set active viewer */
    _view_active_viewer = viewer;

    /* get real viewport size */
#ifndef PLATFORM_NULL
    vp_w = (viewer->vw != -1) ? viewer->vw : wzGetScreenWidth() - viewer->vx;
    vp_h = (viewer->vh != -1) ? viewer->vh : wzGetScreenHeight() - viewer->vy;
#else
    vp_w = viewer->vw;
    vp_h = viewer->vh;
#endif

    /* set viewport (must be done before setting projection) */
    lgfx_setup3d(0, 0);
    lgfx_setviewport(viewer->vx, viewer->vy, vp_w, vp_h);

    /* prepare projection */
    ratio = vp_w / (float)vp_h;
    if (viewer->ortho) {
        float width, height;
        height = viewer->min * tan(lm_deg2rad(viewer->fov)) * 2;
        width = height * ratio;
        proj = lmat4_ortholh(-width, width, -height, height, viewer->min, viewer->max);
    } else {
        proj = lmat4_perspectivelh(lm_deg2rad(viewer->fov), ratio, viewer->min, viewer->max);
    }
    lgfx_setprojection(proj.m);

    /* prepare view matrix */
    q = lquat_fromeuler(lvec3_rad(lvec3(viewer->pitch, viewer->yaw, viewer->roll)));
    _view_matrix = lmat4_identity();
    _view_matrix = lmat4_rotate(_view_matrix, -lquat_angle(q), lquat_axis(q));
    _view_matrix = lmat4_translate(_view_matrix, lvec3(-viewer->x, -viewer->y, -viewer->z));

    /* prepare lights */
    _PrepareLights();

    /* clear buffers */
    lgfx_setdepthwrite(TRUE);
    lgfx_cleardepthbuffer();
    switch (viewer->clearmode) {
        case CLEAR_COLOR:
            lgfx_clearcolorbuffer(
                wzGetRed(viewer->clearcolor) / 255.0f,
                wzGetGreen(viewer->clearcolor) / 255.0f,
                wzGetBlue(viewer->clearcolor) / 255.0f);
            break;
        case CLEAR_SKYBOX:
            halfrange = (viewer->max - viewer->min) * 0.5f;
            
            /* calculate modelview */
            modelview = lmat4_transform(
                lvec3(0, 0, 0),
                lquat(1, 0, 0, 0),
                lvec3(halfrange, halfrange, halfrange));
            modelview = lmat4_mul(_view_matrix, modelview);
            lgfx_setmodelview(modelview.m);

            /* draw skybox */
            _DrawMesh(_SetupViewerSkyboxMesh(viewer->skybox), NULL);

            break;
    }
}

const Viewer* _GetActiveViewer() {
    return _view_active_viewer;
}

const void* _GetActiveMatrix() {
    return &_view_matrix;
}

static Mesh* _SetupViewerSkyboxMesh(Texture* texture) {
    if (!_viewer_skybox) _viewer_skybox = _CreateSkyboxMesh();
    wzSetMaterialTexture(GetMeshMaterial(_viewer_skybox, 0), texture);
    return _viewer_skybox;
}
