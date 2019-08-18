#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include "types.h"

#define CLEAR_NONE   0
#define CLEAR_COLOR  1
#define CLEAR_SKYBOX 2

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Viewer* CALL CreateViewer();
EXPORT void CALL DeleteViewer(Viewer* viewer);
EXPORT float CALL GetViewerX(const Viewer* viewer);
EXPORT float CALL GetViewerY(const Viewer* viewer);
EXPORT float CALL GetViewerZ(const Viewer* viewer);
EXPORT void CALL SetViewerPosition(Viewer* viewer, float x, float y, float z);
EXPORT void CALL MoveViewer(Viewer* viewer, float x, float y, float z);
EXPORT float CALL GetViewerPitch(const Viewer* viewer);
EXPORT float CALL GetViewerYaw(const Viewer* viewer);
EXPORT float CALL GetViewerRoll(const Viewer* viewer);
EXPORT void CALL SetViewerRotation(Viewer* viewer, float pitch, float yaw, float roll);
EXPORT void CALL TurnViewer(Viewer* viewer, float pitch, float yaw, float roll);
EXPORT void CALL ViewerLookAt(Viewer* viewer, float x, float y, float z);
EXPORT int CALL GetViewerViewportX(const Viewer* viewer);
EXPORT int CALL GetViewerViewportY(const Viewer* viewer);
EXPORT int CALL GetViewerViewportWidth(const Viewer* viewer);
EXPORT int CALL GetViewerViewportHeight(const Viewer* viewer);
EXPORT void CALL SetViewerViewport(Viewer* viewer, int x, int y, int width, int height);
EXPORT int CALL GetViewerClearMode(const Viewer* viewer);
EXPORT void CALL SetViewerClearMode(Viewer* viewer, int mode);
EXPORT int CALL GetViewerClearColor(const Viewer* viewer);
EXPORT void CALL SetViewerClearColor(Viewer* viewer, int color);
EXPORT Texture* CALL GetViewerSkybox(const Viewer* viewer);
EXPORT void CALL SetViewerSkybox(Viewer* viewer, Texture* texture);
EXPORT bool_t CALL IsViewerOrtho(const Viewer* viewer);
EXPORT void CALL SetViewerOrtho(Viewer* viewer, bool_t ortho);
EXPORT float CALL GetViewerFov(const Viewer* viewer);
EXPORT void CALL SetViewerFov(Viewer* viewer, float enable);
EXPORT float CALL GetViewerDistanceMin(const Viewer* viewer);
EXPORT float CALL GetViewerDistanceMax(const Viewer* viewer);
EXPORT void CALL SetViewerDistance(Viewer* viewer, float min, float max);
EXPORT bool_t CALL IsViewerFogEnabled(const Viewer* viewer);
EXPORT void CALL SetViewerFogEnabled(Viewer* viewer, bool_t enable);
EXPORT int CALL GetViewerFogColor(const Viewer* viewer);
EXPORT void CALL SetViewerFogColor(Viewer* viewer, int color);
EXPORT float CALL GetViewerFogDistanceMin(const Viewer* viewer);
EXPORT float CALL GetViewerFogDistanceMax(const Viewer* viewer);
EXPORT void CALL SetViewerFogDistance(Viewer* viewer, float min, float max);
EXPORT void CALL PrepareViewer(const Viewer* viewer);

#ifndef SWIG
const Viewer* _GetActiveViewer();
const void* _GetActiveMatrix();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VIEWER_H_INCLUDED */
