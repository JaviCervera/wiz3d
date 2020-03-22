#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "types.h"

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Light* CALL bmCreateLight(int type);
EXPORT void CALL bmDeleteLight(Light* light);
EXPORT int CALL bmGetLightType(const Light* light);
EXPORT void CALL bmSetLightType(Light* light, int type);
EXPORT int CALL bmGetLightColor(const Light* light);
EXPORT void CALL bmSetLightColor(Light* light, int color);
EXPORT bool_t CALL bmIsLightSpecularColored(const Light* light);
EXPORT void CALL bmSetLightSpecularColored(Light* light, bool_t has_color);
EXPORT float CALL bmGetLightLinearAttenuation(const Light* light);
EXPORT void CALL bmSetLightLinearAttenuation(Light* light, float att);
EXPORT float CALL bmGetLightX(const Light* light);
EXPORT float CALL bmGetLightY(const Light* light);
EXPORT float CALL bmGetLightZ(const Light* light);
EXPORT void CALL bmSetLightPosition(Light* light, float x, float y, float z);
EXPORT void CALL bmMoveLight(Light* light, float x, float y, float z);
EXPORT float CALL bmGetLightPitch(const Light* light);
EXPORT float CALL bmGetLightYaw(const Light* light);
EXPORT void CALL bmSetLightRotation(Light* light, float pitch, float yaw);
EXPORT void CALL bmTurnLight(Light* light, float pitch, float yaw);
EXPORT void CALL bmLightLookAt(Light* light, float x, float y, float z);
EXPORT int CALL bmGetAmbientColor();
EXPORT void CALL bmSetAmbientColor(int color);

#ifndef SWIG
void _PrepareLights();
int _GetNumLights();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIGHT_H_INCLUDED */
