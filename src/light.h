#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "types.h"

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT       1

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

EXPORT struct light_t* CALL light_new(int type);
EXPORT void CALL light_delete(struct light_t* light);
EXPORT void CALL light_move(struct light_t* light, float x, float y, float z);
EXPORT void CALL light_turn(struct light_t* light, float pitch, float yaw);
EXPORT void CALL light_setambient(int color);
EXPORT int CALL light_ambient();

#ifndef SWIG
void _light_prepare();
int _light_numlights();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIGHT_H_INCLUDED */
