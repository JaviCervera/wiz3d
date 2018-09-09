#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "color.h"
#include "light.h"
#include "util.h"
#include "viewer.h"

static int _light_ambient;
static struct light_t* _lights[NUM_LIGHTS] = {};

struct light_t* light_new(int type)
{
  int i;
  struct light_t* light;

  /* make sure that there are lights available */
  for (i = 0; i < NUM_LIGHTS; ++i)
    if (!_lights[i])
      break;
  if (i == NUM_LIGHTS) return NULL;

  /* make sure that light type is in range */
  type = clamp(type, _LIGHT_DIRECTIONAL, _LIGHT_POINT);

  /* create light */
  light = alloc(struct light_t);
  light->x = 0;
  light->y = 0;
  light->z = 0;
  light->pitch = 0;
  light->yaw = 0;
  light->type = type;
  light->color = _COLOR_WHITE;
  light->att = 0;
  _lights[i] = light;
  return light;
}

void light_delete(struct light_t* light)
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

void light_move(struct light_t* light, float x, float y, float z)
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

void light_turn(struct light_t* light, float pitch, float yaw)
{
  lvec3_t vec;

  vec = lvec3_add(lvec3(light->pitch, light->yaw, 0), lvec3(pitch, yaw, 0));
  light->pitch = vec.x;
  light->yaw = vec.y;
}

void light_setambient(int color)
{
  _light_ambient = color;
  lgfx_setambient(
    color_red(color) / 255.0f,
    color_green(color) / 255.0f,
    color_blue(color) / 255.0f);
}

int light_ambient()
{
  return _light_ambient;
}

void _light_prepare()
{
  int i;
  for (i = 0; i < NUM_LIGHTS; ++i)
  {
    if (_lights[i])
    {
      struct light_t* light;
      lvec3_t pos;

      light = _lights[i];
      
      /* get position in viewer space */
      if ( light->type == _LIGHT_DIRECTIONAL ) {
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
      pos = lmat4_mulvec3(*(const lmat4_t*)_viewer_activematrix(), pos, 0);

      /* set light data */
      lgfx_setlight(
        i,
        pos.x,
        pos.y,
        pos.z,
        light->type,
        color_red(light->color) / 255.0f,
        color_green(light->color) / 255.0f,
        color_blue(light->color) / 255.0f,
        light->att);
    }
  }
}

int _light_numlights()
{
  int i;
  int num = 0;
  for (i = 0; i < NUM_LIGHTS; ++i)
    if (_lights[i]) ++num;
  return num;
}