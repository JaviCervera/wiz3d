#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SWIG
void _physics_init();
void _physics_update(float delta);
void _physics_finish();
void* _physics_createbox(float w, float h, float d);
void _physics_deleteshape(void* shape);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PHYSICS_H_INCLUDED */
