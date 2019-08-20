#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include "types.h"

#define CLEAR_NONE   0
#define CLEAR_COLOR  1
#define CLEAR_SKYBOX 2

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Viewer* CALL spCreateViewer();
EXPORT void CALL spDeleteViewer(Viewer* viewer);
EXPORT float CALL spGetViewerX(const Viewer* viewer);
EXPORT float CALL spGetViewerY(const Viewer* viewer);
EXPORT float CALL spGetViewerZ(const Viewer* viewer);
EXPORT void CALL spSetViewerPosition(Viewer* viewer, float x, float y, float z);
EXPORT void CALL spMoveViewer(Viewer* viewer, float x, float y, float z);
EXPORT float CALL spGetViewerPitch(const Viewer* viewer);
EXPORT float CALL spGetViewerYaw(const Viewer* viewer);
EXPORT float CALL spGetViewerRoll(const Viewer* viewer);
EXPORT void CALL spSetViewerRotation(Viewer* viewer, float pitch, float yaw, float roll);
EXPORT void CALL spTurnViewer(Viewer* viewer, float pitch, float yaw, float roll);
EXPORT void CALL spViewerLookAt(Viewer* viewer, float x, float y, float z);
EXPORT int CALL spGetViewerViewportX(const Viewer* viewer);
EXPORT int CALL spGetViewerViewportY(const Viewer* viewer);
EXPORT int CALL spGetViewerViewportWidth(const Viewer* viewer);
EXPORT int CALL spGetViewerViewportHeight(const Viewer* viewer);
EXPORT void CALL spSetViewerViewport(Viewer* viewer, int x, int y, int width, int height);
EXPORT int CALL spGetViewerClearMode(const Viewer* viewer);
EXPORT void CALL spSetViewerClearMode(Viewer* viewer, int mode);
EXPORT int CALL spGetViewerClearColor(const Viewer* viewer);
EXPORT void CALL spSetViewerClearColor(Viewer* viewer, int color);
EXPORT Texture* CALL spGetViewerSkybox(const Viewer* viewer);
EXPORT void CALL spSetViewerSkybox(Viewer* viewer, Texture* texture);
EXPORT bool_t CALL spIsViewerOrtho(const Viewer* viewer);
EXPORT void CALL spSetViewerOrtho(Viewer* viewer, bool_t ortho);
EXPORT float CALL spGetViewerFov(const Viewer* viewer);
EXPORT void CALL spSetViewerFov(Viewer* viewer, float enable);
EXPORT float CALL spGetViewerDistanceMin(const Viewer* viewer);
EXPORT float CALL spGetViewerDistanceMax(const Viewer* viewer);
EXPORT void CALL spSetViewerDistance(Viewer* viewer, float min, float max);
EXPORT bool_t CALL spIsViewerFogEnabled(const Viewer* viewer);
EXPORT void CALL spSetViewerFogEnabled(Viewer* viewer, bool_t enable);
EXPORT int CALL spGetViewerFogColor(const Viewer* viewer);
EXPORT void CALL spSetViewerFogColor(Viewer* viewer, int color);
EXPORT float CALL spGetViewerFogDistanceMin(const Viewer* viewer);
EXPORT float CALL spGetViewerFogDistanceMax(const Viewer* viewer);
EXPORT void CALL spSetViewerFogDistance(Viewer* viewer, float min, float max);
EXPORT void CALL spPrepareViewer(const Viewer* viewer);

#ifndef SWIG
const Viewer* _GetActiveViewer();
const void* _GetActiveMatrix();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VIEWER_H_INCLUDED */
