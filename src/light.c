#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "wiz3d_config.h"
#include "color.h"
#include "light.h"
#include "util.h"
#include "viewer.h"
#include <math.h>


typedef struct SLight {
    float x, y, z;
    float pitch, yaw;
    int type;
    int color;
    bool_t colorSpecular;
    float constAtt;
    float linearAtt;
    float quadraticAtt;
} Light;

static int _light_ambient;
static Light* _lights[NUM_LIGHTS] = {};

EXPORT Light* CALL wzCreateLight(int type) {
    int i;
    Light* light;

    /* make sure that there are lights available */
    for (i = 0; i < NUM_LIGHTS; ++i)
        if (!_lights[i])
            break;
    if (i == NUM_LIGHTS) return NULL;

    /* make sure that light type is in range */
    type = _Clamp(type, LIGHT_DIRECTIONAL, LIGHT_POINT);

    /* create light */
    light = _Alloc(Light);
    light->x = 0;
    light->y = 0;
    light->z = 0;
    light->pitch = 0;
    light->yaw = 0;
    light->type = type;
    light->color = COLOR_WHITE;
    light->colorSpecular = TRUE;
    light->linearAtt = 0;
    _lights[i] = light;
    return light;
}

EXPORT void CALL wzDeleteLight(Light* light) {
    size_t i;

    /* find light index in array */
    for (i = 0; i < NUM_LIGHTS; ++i)
        if (light == _lights[i])
            break;
    if (i == NUM_LIGHTS) return;

    _lights[i] = NULL;
    free(light);
}

EXPORT int CALL wzGetLightType(const Light* light) { return light->type; }

EXPORT void CALL wzSetLightType(Light* light, int type) {
    light->type = _Clamp(type, LIGHT_DIRECTIONAL, LIGHT_POINT);
}

EXPORT int CALL wzGetLightColor(const Light* light) { return light->color; }

EXPORT void CALL wzSetLightColor(Light* light, int color) { light->color = color; }

EXPORT bool_t CALL wzIsLightSpecularColored(const Light* light) { return light->colorSpecular; }

EXPORT void CALL wzSetLightSpecularColored(Light* light, bool_t has_color) { light->colorSpecular = _Clamp(has_color, FALSE, TRUE); }

EXPORT float CALL wzGetLightLinearAttenuation(const Light* light) { return light->linearAtt; }

EXPORT void CALL wzSetLightLinearAttenuation(Light* light, float att) { light->linearAtt = att; }

EXPORT float CALL wzGetLightX(const Light* light) { return light->x; }

EXPORT float CALL wzGetLightY(const Light* light) { return light->y; }

EXPORT float CALL wzGetLightZ(const Light* light) { return light->z; }

EXPORT void CALL wzSetLightPosition(Light* light, float x, float y, float z) {
    light->x = x;
    light->y = y;
    light->z = z;
}

EXPORT void CALL wzMoveLight(Light* light, float x, float y, float z) {
    lvec3_t vec;

    vec = lquat_mulvec3(
        lquat_fromeuler(lvec3_rad(lvec3(light->pitch, light->yaw, 0))),
        lvec3(x, y, z));
    light->x += vec.x;
    light->y += vec.y;
    light->z += vec.z;
}

EXPORT float CALL wzGetLightPitch(const Light* light) { return light->pitch; }

EXPORT float CALL wzGetLightYaw(const Light* light) { return light->yaw; }

EXPORT void CALL wzSetLightRotation(Light* light, float pitch, float yaw) {
    light->pitch = pitch;
    light->yaw = yaw;
}

EXPORT void CALL wzTurnLight(Light* light, float pitch, float yaw) {
    light->pitch += pitch;
    light->yaw += yaw;
}

EXPORT void CALL wzLightLookAt(Light* light, float x, float y, float z) {
    lvec3_t dir;
    dir = lvec3_norm(lvec3_sub(lvec3(x, y, z), lvec3(light->x, light->y, light->z)));
    light->pitch = lm_rad2deg((float)asin(-dir.y));
    light->yaw = lm_rad2deg((float)atan2(dir.x, dir.z));
}

EXPORT int CALL wzGetAmbientColor() { return _light_ambient; }

EXPORT void CALL wzSetAmbientColor(int color) {
    _light_ambient = color;
    lgfx_setambient(
        wzGetRed(color) / 255.0f,
        wzGetGreen(color) / 255.0f,
        wzGetBlue(color) / 255.0f);
}

void _PrepareLights() {
    int i;
    for (i = 0; i < NUM_LIGHTS; ++i) {
        if (_lights[i]) {
            Light* light;
            lvec3_t pos;
            float w;

            light = _lights[i];
            w = (light->type == LIGHT_DIRECTIONAL) ? 0 : 1;

            /* get position in viewer space */
            if (light->type == LIGHT_DIRECTIONAL) {
                pos = lquat_mulvec3(
                    lquat_fromeuler(lvec3_rad(lvec3(light->pitch, light->yaw, 0))),
                    lvec3(0, 0, -1));
            } else {
                pos = lvec3(
                    light->x,
                    light->y,
                    light->z);
            }
            pos = lmat4_mulvec3(*(const lmat4_t*)_GetActiveMatrix(), pos, w);

            /* set light data */
            lgfx_setlight(
                i,
                pos.x,
                pos.y,
                pos.z,
                w,
                wzGetRed(light->color) / 255.0f,
                wzGetGreen(light->color) / 255.0f,
                wzGetBlue(light->color) / 255.0f,
                light->colorSpecular,
                light->linearAtt);
        }
    }
}

int _GetNumLights() {
    int i;
    int num = 0;
    for (i = 0; i < NUM_LIGHTS; ++i)
        if (_lights[i]) ++num;
    return num;
}
