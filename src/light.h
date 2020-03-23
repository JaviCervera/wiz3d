#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "types.h"

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Light* CALL wzCreateLight(int type);
EXPORT void CALL wzDeleteLight(Light* light);
EXPORT int CALL wzGetLightType(const Light* light);
EXPORT void CALL wzSetLightType(Light* light, int type);
EXPORT int CALL wzGetLightColor(const Light* light);
EXPORT void CALL wzSetLightColor(Light* light, int color);
EXPORT bool_t CALL wzIsLightSpecularColored(const Light* light);
EXPORT void CALL wzSetLightSpecularColored(Light* light, bool_t has_color);
EXPORT float CALL wzGetLightLinearAttenuation(const Light* light);
EXPORT void CALL wzSetLightLinearAttenuation(Light* light, float att);
EXPORT float CALL wzGetLightX(const Light* light);
EXPORT float CALL wzGetLightY(const Light* light);
EXPORT float CALL wzGetLightZ(const Light* light);
EXPORT void CALL wzSetLightPosition(Light* light, float x, float y, float z);
EXPORT void CALL wzMoveLight(Light* light, float x, float y, float z);
EXPORT float CALL wzGetLightPitch(const Light* light);
EXPORT float CALL wzGetLightYaw(const Light* light);
EXPORT void CALL wzSetLightRotation(Light* light, float pitch, float yaw);
EXPORT void CALL wzTurnLight(Light* light, float pitch, float yaw);
EXPORT void CALL wzLightLookAt(Light* light, float x, float y, float z);
EXPORT int CALL wzGetAmbientColor();
EXPORT void CALL wzSetAmbientColor(int color);

#ifndef SWIG
void _PrepareLights();
int _GetNumLights();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIGHT_H_INCLUDED */
