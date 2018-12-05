#ifndef MICRON_H_INCLUDED
#define MICRON_H_INCLUDED

#include "color.h"
#include "input.h"
#include "light.h"
#include "log.h"
#include "material.h"
#include "memory.h"
#include "object.h"
#include "pixmap.h"
#include "screen.h"
#include "texture.h"
#include "viewer.h"

#ifdef __cplusplus
extern "C"
{
#endif

bool_t micron_init();
void micron_finish();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MICRON_H_INCLUDED */
