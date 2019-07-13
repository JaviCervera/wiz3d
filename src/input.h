#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
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

EXPORT void CALL input_setmousevisible(bool_t visible);
EXPORT void CALL input_setmouseposition(int x, int y);
EXPORT int CALL input_mousex();
EXPORT int CALL input_mousey();
EXPORT bool_t CALL input_mousedown(int b);
EXPORT bool_t CALL input_keydown(int k);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* INPUT_H_INCLUDED */
