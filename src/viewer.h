#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include "types.h"

#define CLEAR_NONE     0
#define CLEAR_COLOR    1
#define CLEAR_SKYBOX 2

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Viewer* CALL bmCreateViewer();
EXPORT void CALL bmDeleteViewer(Viewer* viewer);
EXPORT float CALL bmGetViewerX(const Viewer* viewer);
EXPORT float CALL bmGetViewerY(const Viewer* viewer);
EXPORT float CALL bmGetViewerZ(const Viewer* viewer);
EXPORT void CALL bmSetViewerPosition(Viewer* viewer, float x, float y, float z);
EXPORT void CALL bmMoveViewer(Viewer* viewer, float x, float y, float z);
EXPORT float CALL bmGetViewerPitch(const Viewer* viewer);
EXPORT float CALL bmGetViewerYaw(const Viewer* viewer);
EXPORT float CALL bmGetViewerRoll(const Viewer* viewer);
EXPORT void CALL bmSetViewerRotation(Viewer* viewer, float pitch, float yaw, float roll);
EXPORT void CALL bmTurnViewer(Viewer* viewer, float pitch, float yaw, float roll);
EXPORT void CALL bmViewerLookAt(Viewer* viewer, float x, float y, float z);
EXPORT int CALL bmGetViewerViewportX(const Viewer* viewer);
EXPORT int CALL bmGetViewerViewportY(const Viewer* viewer);
EXPORT int CALL bmGetViewerViewportWidth(const Viewer* viewer);
EXPORT int CALL bmGetViewerViewportHeight(const Viewer* viewer);
EXPORT void CALL bmSetViewerViewport(Viewer* viewer, int x, int y, int width, int height);
EXPORT int CALL bmGetViewerClearMode(const Viewer* viewer);
EXPORT void CALL bmSetViewerClearMode(Viewer* viewer, int mode);
EXPORT int CALL bmGetViewerClearColor(const Viewer* viewer);
EXPORT void CALL bmSetViewerClearColor(Viewer* viewer, int color);
EXPORT Texture* CALL bmGetViewerSkybox(const Viewer* viewer);
EXPORT void CALL bmSetViewerSkybox(Viewer* viewer, Texture* texture);
EXPORT bool_t CALL bmIsViewerOrtho(const Viewer* viewer);
EXPORT void CALL bmSetViewerOrtho(Viewer* viewer, bool_t ortho);
EXPORT float CALL bmGetViewerFov(const Viewer* viewer);
EXPORT void CALL bmSetViewerFov(Viewer* viewer, float enable);
EXPORT float CALL bmGetViewerDistanceMin(const Viewer* viewer);
EXPORT float CALL bmGetViewerDistanceMax(const Viewer* viewer);
EXPORT void CALL bmSetViewerDistance(Viewer* viewer, float min, float max);
EXPORT bool_t CALL bmIsViewerFogEnabled(const Viewer* viewer);
EXPORT void CALL bmSetViewerFogEnabled(Viewer* viewer, bool_t enable);
EXPORT int CALL bmGetViewerFogColor(const Viewer* viewer);
EXPORT void CALL bmSetViewerFogColor(Viewer* viewer, int color);
EXPORT float CALL bmGetViewerFogDistanceMin(const Viewer* viewer);
EXPORT float CALL bmGetViewerFogDistanceMax(const Viewer* viewer);
EXPORT void CALL bmSetViewerFogDistance(Viewer* viewer, float min, float max);
EXPORT void CALL bmPrepareViewer(const Viewer* viewer);

#ifndef SWIG
const Viewer* _GetActiveViewer();
const void* _GetActiveMatrix();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VIEWER_H_INCLUDED */
