#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include "types.h"

#define CLEAR_NONE   0
#define CLEAR_COLOR  1
#define CLEAR_SKYBOX 2

#ifdef __cplusplus
extern "C" {
#endif

struct STexture;

typedef struct {
  float             x, y, z;
  float             pitch, yaw, roll;
  int               vx;
  int               vy;
  int               vw;
  int               vh;
  int               clearmode;
  int               clearcolor;
  struct STexture* skybox;
  bool_t            ortho;
  float             fov;
  float             min;
  float             max;
  bool_t            fogenabled;
  int               fogcolor;
  float             fogmin;
  float             fogmax;
} Viewer;

EXPORT Viewer* CALL CreateViewer();
EXPORT void CALL DeleteViewer(Viewer* viewer);
EXPORT void CALL MoveViewer(Viewer* viewer, float x, float y, float z);
EXPORT void CALL TurnViewer(Viewer* viewer, float pitch, float yaw, float roll);
EXPORT void CALL ViewerLookAt(Viewer* viewer, float x, float y, float z);
EXPORT void CALL PrepareViewer(const Viewer* viewer);

#ifndef SWIG
const Viewer* _GetActiveViewer();
const void* _GetActiveMatrix();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VIEWER_H_INCLUDED */
