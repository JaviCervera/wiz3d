#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "types.h"

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT       1

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Light* CALL spCreateLight(int type);
EXPORT void CALL spDeleteLight(Light* light);
EXPORT int CALL spGetLightType(const Light* light);
EXPORT void CALL spSetLightType(Light* light, int type);
EXPORT int CALL spGetLightColor(const Light* light);
EXPORT void CALL spSetLightColor(Light* light, int color);
EXPORT float CALL spGetLightRange(const Light* light);
EXPORT void CALL spSetLightRange(Light* light, float range);
EXPORT float CALL spGetLightX(const Light* light);
EXPORT float CALL spGetLightY(const Light* light);
EXPORT float CALL spGetLightZ(const Light* light);
EXPORT void CALL spSetLightPosition(Light* light, float x, float y, float z);
EXPORT void CALL spMoveLight(Light* light, float x, float y, float z);
EXPORT float CALL spGetLightPitch(const Light* light);
EXPORT float CALL spGetLightYaw(const Light* light);
EXPORT void CALL spSetLightRotation(Light* light, float pitch, float yaw);
EXPORT void CALL spTurnLight(Light* light, float pitch, float yaw);
EXPORT void CALL spLightLookAt(Light* light, float x, float y, float z);
EXPORT int CALL spGetAmbientColor();
EXPORT void CALL spSetAmbientColor(int color);

#ifndef SWIG
void _PrepareLights();
int _GetNumLights();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIGHT_H_INCLUDED */
