#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "color.h"
#include "light.h"
#include "util.h"
#include "viewer.h"

static int _light_ambient;
static Light* _lights[NUM_LIGHTS] = {};

EXPORT Light* CALL CreateLight(int type)
{
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

EXPORT void CALL DeleteLight(Light* light)
{
  size_t i;

  /* find light index in array */
  for (i = 0; i < NUM_LIGHTS; ++i)
    if (light == _lights[i])
      break;
  if (i == NUM_LIGHTS) return;

  _lights[i] = NULL;
  free(light);
}

EXPORT void CALL MoveLight(Light* light, float x, float y, float z)
{
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

EXPORT void CALL TurnLight(Light* light, float pitch, float yaw)
{
  lvec3_t vec;

  vec = lvec3_add(lvec3(light->pitch, light->yaw, 0), lvec3(pitch, yaw, 0));
  light->pitch = vec.x;
  light->yaw = vec.y;
}

EXPORT void CALL SetAmbientColor(int color)
{
  _light_ambient = color;
  lgfx_setambient(
    GetRed(color) / 255.0f,
    GetGreen(color) / 255.0f,
    GetBlue(color) / 255.0f);
}

EXPORT int CALL GetAmbientColor()
{
  return _light_ambient;
}

void _PrepareLights()
{
  int i;
  for (i = 0; i < NUM_LIGHTS; ++i)
  {
    if (_lights[i])
    {
      Light* light;
      lvec3_t pos;

      light = _lights[i];

      /* get position in viewer space */
      if (light->type == LIGHT_DIRECTIONAL)
      {
        pos = lquat_mulvec3(
          lquat_fromeuler(lvec3_rad(lvec3(light->pitch, light->yaw, 0))),
          lvec3(0, 0, -1));
      }
      else
      {
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
        GetRed(light->color) / 255.0f,
        GetGreen(light->color) / 255.0f,
        GetBlue(light->color) / 255.0f,
        1.0f / light->range);
    }
  }
}

int _GetNumLights()
{
  int i;
  int num = 0;
  for (i = 0; i < NUM_LIGHTS; ++i)
    if (_lights[i]) ++num;
  return num;
}
