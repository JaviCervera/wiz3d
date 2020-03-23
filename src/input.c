#include "wiz3d_config.h"

#ifndef PLATFORM_NULL

#include "input.h"
#include "platform.h"
#include "screen.h"

EXPORT void CALL wzSetCursorVisible(bool_t visible) {
    p_SetCursorVisible(_GetScreenPtr(), visible);
}

EXPORT void CALL wzSetCursorPosition(int x, int y) {
    p_SetCursorPosition(_GetScreenPtr(), x, y);
}

EXPORT int CALL wzGetCursorX() {
    return p_GetCursorX(_GetScreenPtr());
}

EXPORT int CALL wzGetCursorY() {
    return p_GetCursorY(_GetScreenPtr());
}

EXPORT bool_t CALL wzIsCursorPressed(int b) {
    return p_GetCursorPressed(_GetScreenPtr(), b);
}

EXPORT bool_t CALL wzIsKeyPressed(int k) {
    return p_GetKeyPressed(_GetScreenPtr(), k);
}

#endif /* PLATFORM_NULL */
