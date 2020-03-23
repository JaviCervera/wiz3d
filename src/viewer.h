#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include "types.h"

#define CLEAR_NONE     0
#define CLEAR_COLOR    1
#define CLEAR_SKYBOX 2

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Viewer* CALL wzCreateViewer();
EXPORT void CALL wzDeleteViewer(Viewer* viewer);
EXPORT float CALL wzGetViewerX(const Viewer* viewer);
EXPORT float CALL wzGetViewerY(const Viewer* viewer);
EXPORT float CALL wzGetViewerZ(const Viewer* viewer);
EXPORT void CALL wzSetViewerPosition(Viewer* viewer, float x, float y, float z);
EXPORT void CALL wzMoveViewer(Viewer* viewer, float x, float y, float z);
EXPORT float CALL wzGetViewerPitch(const Viewer* viewer);
EXPORT float CALL wzGetViewerYaw(const Viewer* viewer);
EXPORT float CALL wzGetViewerRoll(const Viewer* viewer);
EXPORT void CALL wzSetViewerRotation(Viewer* viewer, float pitch, float yaw, float roll);
EXPORT void CALL wzTurnViewer(Viewer* viewer, float pitch, float yaw, float roll);
EXPORT void CALL wzViewerLookAt(Viewer* viewer, float x, float y, float z);
EXPORT int CALL wzGetViewerViewportX(const Viewer* viewer);
EXPORT int CALL wzGetViewerViewportY(const Viewer* viewer);
EXPORT int CALL wzGetViewerViewportWidth(const Viewer* viewer);
EXPORT int CALL wzGetViewerViewportHeight(const Viewer* viewer);
EXPORT void CALL wzSetViewerViewport(Viewer* viewer, int x, int y, int width, int height);
EXPORT int CALL wzGetViewerClearMode(const Viewer* viewer);
EXPORT void CALL wzSetViewerClearMode(Viewer* viewer, int mode);
EXPORT int CALL wzGetViewerClearColor(const Viewer* viewer);
EXPORT void CALL wzSetViewerClearColor(Viewer* viewer, int color);
EXPORT Texture* CALL wzGetViewerSkybox(const Viewer* viewer);
EXPORT void CALL wzSetViewerSkybox(Viewer* viewer, Texture* texture);
EXPORT bool_t CALL wzIsViewerOrtho(const Viewer* viewer);
EXPORT void CALL wzSetViewerOrtho(Viewer* viewer, bool_t ortho);
EXPORT float CALL wzGetViewerFov(const Viewer* viewer);
EXPORT void CALL wzSetViewerFov(Viewer* viewer, float enable);
EXPORT float CALL wzGetViewerDistanceMin(const Viewer* viewer);
EXPORT float CALL wzGetViewerDistanceMax(const Viewer* viewer);
EXPORT void CALL wzSetViewerDistance(Viewer* viewer, float min, float max);
EXPORT bool_t CALL wzIsViewerFogEnabled(const Viewer* viewer);
EXPORT void CALL wzSetViewerFogEnabled(Viewer* viewer, bool_t enable);
EXPORT int CALL wzGetViewerFogColor(const Viewer* viewer);
EXPORT void CALL wzSetViewerFogColor(Viewer* viewer, int color);
EXPORT float CALL wzGetViewerFogDistanceMin(const Viewer* viewer);
EXPORT float CALL wzGetViewerFogDistanceMax(const Viewer* viewer);
EXPORT void CALL wzSetViewerFogDistance(Viewer* viewer, float min, float max);
EXPORT void CALL wzPrepareViewer(const Viewer* viewer);

#ifndef SWIG
const Viewer* _GetActiveViewer();
const void* _GetActiveMatrix();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VIEWER_H_INCLUDED */
