#ifndef TAU_H_INCLUDED
#define TAU_H_INCLUDED

#include "color.h"
#include "input.h"
#include "light.h"
#include "log.h"
#include "material.h"
#include "memory.h"
#include "object.h"
#include "physics.h"
#include "pixmap.h"
#include "screen.h"
#include "texture.h"
#include "viewer.h"

#ifdef __cplusplus
extern "C"
{
#endif

bool_t tau_init();
void tau_finish();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TAU_H_INCLUDED */
