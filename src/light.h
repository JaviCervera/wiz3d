#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "types.h"

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT       1

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Light* CALL CreateLight(int type);
EXPORT void CALL DeleteLight(Light* light);
EXPORT int CALL GetLightType(const Light* light);
EXPORT void CALL SetLightType(Light* light, int type);
EXPORT int CALL GetLightColor(const Light* light);
EXPORT void CALL SetLightColor(Light* light, int color);
EXPORT float CALL GetLightRange(const Light* light);
EXPORT void CALL SetLightRange(Light* light, float range);
EXPORT float CALL GetLightX(const Light* light);
EXPORT float CALL GetLightY(const Light* light);
EXPORT float CALL GetLightZ(const Light* light);
EXPORT void CALL SetLightPosition(Light* light, float x, float y, float z);
EXPORT void CALL MoveLight(Light* light, float x, float y, float z);
EXPORT float CALL GetLightPitch(const Light* light);
EXPORT float CALL GetLightYaw(const Light* light);
EXPORT void CALL SetLightRotation(Light* light, float pitch, float yaw);
EXPORT void CALL TurnLight(Light* light, float pitch, float yaw);
EXPORT void CALL LightLookAt(Light* light, float x, float y, float z);
EXPORT int CALL GetAmbientColor();
EXPORT void CALL SetAmbientColor(int color);

#ifndef SWIG
void _PrepareLights();
int _GetNumLights();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIGHT_H_INCLUDED */
