#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "types.h"

#define _LIGHT_DIRECTIONAL 0
#define _LIGHT_POINT       1

#ifdef __cplusplus
extern "C"
{
#endif

struct light_t
{
  float x, y, z;
  float pitch, yaw;
  int   type;
  int   color;
  float range;
};

struct light_t* light_new(int type);
void light_delete(struct light_t* light);
void light_move(struct light_t* light, float x, float y, float z);
void light_turn(struct light_t* light, float pitch, float yaw);
void light_setambient(int color);
int light_ambient();

#ifndef SWIG
void _light_prepare();
int _light_numlights();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIGHT_H_INCLUDED */
