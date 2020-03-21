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

EXPORT Viewer* CALL bmCreateViewer() {
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
    viewer->clearcolor = bmGetRGB(52, 73, 94);
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

EXPORT void CALL bmDeleteViewer(Viewer* viewer) { free(viewer); }

EXPORT float CALL bmGetViewerX(const Viewer* viewer) { return viewer->x; }

EXPORT float CALL bmGetViewerY(const Viewer* viewer) { return viewer->y; }

EXPORT float CALL bmGetViewerZ(const Viewer* viewer) { return viewer->z; }

EXPORT void CALL bmSetViewerPosition(Viewer* viewer, float x, float y, float z) {
    viewer->x = x;
    viewer->y = y;
    viewer->z = z;
}

EXPORT void CALL bmMoveViewer(Viewer* viewer, float x, float y, float z) {
    lvec3_t vec;

    vec = lvec3_add(
        lvec3(viewer->x, viewer->y, viewer->z),
        lquat_mulvec3(lquat_fromeuler(lvec3_rad(lvec3(viewer->pitch, viewer->yaw, viewer->roll))), lvec3(x, y, z)));
    viewer->x = vec.x;
    viewer->y = vec.y;
    viewer->z = vec.z;
}

EXPORT float CALL bmGetViewerPitch(const Viewer* viewer) { return viewer->pitch; }

EXPORT float CALL bmGetViewerYaw(const Viewer* viewer) { return viewer->yaw; }

EXPORT float CALL bmGetViewerRoll(const Viewer* viewer) { return viewer->roll; }

EXPORT void CALL bmSetViewerRotation(Viewer* viewer, float pitch, float yaw, float roll) {
    viewer->pitch = pitch;
    viewer->yaw = yaw;
    viewer->roll = roll;
}

EXPORT void CALL bmTurnViewer(Viewer* viewer, float pitch, float yaw, float roll) {
    lvec3_t vec;

    vec = lvec3_add(lvec3(viewer->pitch, viewer->yaw, viewer->roll), lvec3(pitch, yaw, roll));
    viewer->pitch = vec.x;
    viewer->yaw = vec.y;
    viewer->roll = vec.z;
}

EXPORT void CALL bmViewerLookAt(Viewer* viewer, float x, float y, float z) {
    lvec3_t dir;
    dir = lvec3_norm(lvec3_sub(lvec3(x, y, z), lvec3(viewer->x, viewer->y, viewer->z)));
    viewer->pitch = lm_rad2deg((float)asin(-dir.y));
    viewer->yaw = lm_rad2deg((float)atan2(dir.x, dir.z));
}

EXPORT int CALL bmGetViewerViewportX(const Viewer* viewer) { return viewer->vx; }

EXPORT int CALL bmGetViewerViewportY(const Viewer* viewer) { return viewer->vy; }

EXPORT int CALL bmGetViewerViewportWidth(const Viewer* viewer) { return viewer->vw; }

EXPORT int CALL bmGetViewerViewportHeight(const Viewer* viewer) { return viewer->vh; }

EXPORT void CALL bmSetViewerViewport(Viewer* viewer, int x, int y, int width, int height) {
    viewer->vx = x;
    viewer->vy = y;
    viewer->vw = width;
    viewer->vh = height;
}

EXPORT int CALL bmGetViewerClearMode(const Viewer* viewer) { return viewer->clearmode; }

EXPORT void CALL bmSetViewerClearMode(Viewer* viewer, int mode) { viewer->clearmode = _Clamp(mode, CLEAR_NONE, CLEAR_SKYBOX); }

EXPORT int CALL bmGetViewerClearColor(const Viewer* viewer) { return viewer->clearcolor; }

EXPORT void CALL bmSetViewerClearColor(Viewer* viewer, int color) { viewer->clearcolor = color; }

EXPORT Texture* CALL bmGetViewerSkybox(const Viewer* viewer) { return viewer->skybox; }

EXPORT void CALL bmSetViewerSkybox(Viewer* viewer, Texture* texture) { viewer->skybox = texture; }

EXPORT bool_t CALL bmIsViewerOrtho(const Viewer* viewer) { return viewer->ortho; }

EXPORT void CALL bmSetViewerOrtho(Viewer* viewer, bool_t ortho) { viewer->ortho = ortho; }

EXPORT float CALL bmGetViewerFov(const Viewer* viewer) { return viewer->fov; }

EXPORT void CALL bmSetViewerFov(Viewer* viewer, float enable) { viewer->fov = enable; }

EXPORT float CALL bmGetViewerDistanceMin(const Viewer* viewer) { return viewer->min; }

EXPORT float CALL bmGetViewerDistanceMax(const Viewer* viewer) { return viewer->max; }

EXPORT void CALL bmSetViewerDistance(Viewer* viewer, float min, float max) {
    viewer->min = min;
    viewer->max = max;
}

EXPORT bool_t CALL bmIsViewerFogEnabled(const Viewer* viewer) { return viewer->fogenabled; }

EXPORT void CALL bmSetViewerFogEnabled(Viewer* viewer, bool_t enable) { viewer->fogenabled = enable; }

EXPORT int CALL bmGetViewerFogColor(const Viewer* viewer) { return viewer->fogcolor; }

EXPORT void CALL bmSetViewerFogColor(Viewer* viewer, int color) { viewer->fogcolor = color; }

EXPORT float CALL bmGetViewerFogDistanceMin(const Viewer* viewer) { return viewer->fogmin; }

EXPORT float CALL bmGetViewerFogDistanceMax(const Viewer* viewer) { return viewer->fogmax; }

EXPORT void CALL bmSetViewerFogDistance(Viewer* viewer, float min, float max) {
    viewer->fogmin = min;
    viewer->fogmax = max;
}

EXPORT void CALL bmPrepareViewer(const Viewer* viewer) {
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
    vp_w = (viewer->vw != -1) ? viewer->vw : bmGetScreenWidth() - viewer->vx;
    vp_h = (viewer->vh != -1) ? viewer->vh : bmGetScreenHeight() - viewer->vy;
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
                bmGetRed(viewer->clearcolor) / 255.0f,
                bmGetGreen(viewer->clearcolor) / 255.0f,
                bmGetBlue(viewer->clearcolor) / 255.0f);
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
    bmSetMaterialTexture(GetMeshMaterial(_viewer_skybox, 0), texture);
    return _viewer_skybox;
}
