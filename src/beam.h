#ifndef BEAM_H_INCLUDED
#define BEAM_H_INCLUDED

#include "colbox.h"
#include "color.h"
#include "file_system.h"
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

EXPORT bool_t CALL beam_init();
EXPORT void CALL beam_finish();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BEAM_H_INCLUDED */
