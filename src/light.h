#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "types.h"

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT       1

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
  float x, y, z;
  float pitch, yaw;
  int   type;
  int   color;
  float range;
} Light;

EXPORT Light* CALL CreateLight(int type);
EXPORT void CALL DeleteLight(Light* light);
EXPORT void CALL MoveLight(Light* light, float x, float y, float z);
EXPORT void CALL TurnLight(Light* light, float pitch, float yaw);
EXPORT void CALL SetAmbientColor(int color);
EXPORT int CALL GetAmbientColor();

#ifndef SWIG
void _PrepareLights();
int _GetNumLights();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIGHT_H_INCLUDED */
