#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "beam_config.h"
#include "color.h"
#include "light.h"
#include "util.h"
#include "viewer.h"
#include <math.h>

typedef struct SLight {
  float x, y, z;
  float pitch, yaw;
  int   type;
  int   color;
  float range;
} Light;

static int _light_ambient;
static Light* _lights[NUM_LIGHTS] = {};

EXPORT Light* CALL bmCreateLight(int type) {
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
  light->range = 1000;
  _lights[i] = light;
  return light;
}

EXPORT void CALL bmDeleteLight(Light* light) {
  size_t i;

  /* find light index in array */
  for (i = 0; i < NUM_LIGHTS; ++i)
    if (light == _lights[i])
      break;
  if (i == NUM_LIGHTS) return;

  _lights[i] = NULL;
  free(light);
}

EXPORT int CALL bmGetLightType(const Light* light) { return light->type; }

EXPORT void CALL bmSetLightType(Light* light, int type) {
  light->type = _Clamp(type, LIGHT_DIRECTIONAL, LIGHT_POINT);
}

EXPORT int CALL bmGetLightColor(const Light* light) { return light->color; }

EXPORT void CALL bmSetLightColor(Light* light, int color) { light->color = color; }

EXPORT float CALL bmGetLightRange(const Light* light) { return light->range; }

EXPORT void CALL bmSetLightRange(Light* light, float range) { light->range = range; }

EXPORT float CALL bmGetLightX(const Light* light) { return light->x; }

EXPORT float CALL bmGetLightY(const Light* light) { return light->y; }

EXPORT float CALL bmGetLightZ(const Light* light) { return light->z; }

EXPORT void CALL bmSetLightPosition(Light* light, float x, float y, float z) {
  light->x = x;
  light->y = y;
  light->z = z;
}

EXPORT void CALL bmMoveLight(Light* light, float x, float y, float z) {
  lvec3_t vec;

  vec = lvec3_add(
    lvec3(light->x, light->y, light->z),
    lquat_mulvec3(
      lquat_fromeuler(lvec3_rad(lvec3(light->pitch, light->yaw, 0))),
      lvec3(x, y, z)));
  light->x = vec.x;
  light->y = vec.y;
  light->z = vec.z;
}

EXPORT float CALL bmGetLightPitch(const Light* light) { return light->pitch; }

EXPORT float CALL bmGetLightYaw(const Light* light) { return light->yaw; }

EXPORT void CALL bmSetLightRotation(Light* light, float pitch, float yaw) {
  light->pitch = pitch;
  light->yaw = yaw;
}

EXPORT void CALL bmTurnLight(Light* light, float pitch, float yaw) {
  lvec3_t vec;

  vec = lvec3_add(lvec3(light->pitch, light->yaw, 0), lvec3(pitch, yaw, 0));
  light->pitch = vec.x;
  light->yaw = vec.y;
}

EXPORT void CALL bmLightLookAt(Light* light, float x, float y, float z) {
  lvec3_t dir;
  dir = lvec3_norm(lvec3_sub(lvec3(x, y, z), lvec3(light->x, light->y, light->z)));
  light->pitch = lm_rad2deg((float)asin(-dir.y));
  light->yaw = lm_rad2deg((float)atan2(dir.x, dir.z));
}

EXPORT int CALL bmGetAmbientColor() { return _light_ambient; }

EXPORT void CALL bmSetAmbientColor(int color) {
  _light_ambient = color;
  lgfx_setambient(
    bmGetRed(color) / 255.0f,
    bmGetGreen(color) / 255.0f,
    bmGetBlue(color) / 255.0f);
}

void _PrepareLights() {
  int i;
  for (i = 0; i < NUM_LIGHTS; ++i) {
    if (_lights[i]) {
      Light* light;
      lvec3_t pos;

      light = _lights[i];

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
      pos = lmat4_mulvec3(*(const lmat4_t*)_GetActiveMatrix(), pos, 0);

      /* set light data */
      lgfx_setlight(
        i,
        pos.x,
        pos.y,
        pos.z,
        light->type,
        bmGetRed(light->color) / 255.0f,
        bmGetGreen(light->color) / 255.0f,
        bmGetBlue(light->color) / 255.0f,
        1.0f / light->range);
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
