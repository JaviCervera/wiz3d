#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "wiz3d_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

/* this is defined on macos, so undefine it */
#ifdef _KEY_T
#undef _KEY_T
#endif

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 3

/* these files won't define anything unless the proper macro is defined */
#include "input_allegro.h"
#include "input_glfw.h"
#include "input_sdl.h"

EXPORT void CALL wzSetCursorVisible(bool_t visible);
EXPORT void CALL wzSetCursorPosition(int x, int y);
EXPORT int CALL wzGetCursorX();
EXPORT int CALL wzGetCursorY();
EXPORT bool_t CALL wzIsCursorPressed(int b);
EXPORT bool_t CALL wzIsKeyPressed(int k);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* INPUT_H_INCLUDED */
