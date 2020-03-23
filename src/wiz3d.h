#ifndef WIZ3D_H_INCLUDED
#define WIZ3D_H_INCLUDED

#include "audio.h"
#include "colbox.h"
#include "color.h"
#include "draw.h"
#include "file_system.h"
#include "input.h"
#include "light.h"
#include "log.h"
#include "material.h"
#include "memblock.h"
#include "object.h"
#include "pixmap.h"
#include "screen.h"
#include "texture.h"
#include "time.h"
#include "viewer.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT bool_t CALL wzInitWiz3D();
EXPORT void CALL wzShutdownWiz3D();
EXPORT bool_t CALL wzIsMultitexturingSupported();
EXPORT bool_t CALL wzIsMipmappingSupported();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* WIZ3D_H_INCLUDED */
