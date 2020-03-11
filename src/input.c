#include "beam_config.h"

#ifndef PLATFORM_NULL

#include "input.h"
#include "platform.h"
#include "screen.h"

EXPORT void CALL bmSetCursorVisible(bool_t visible) {
  p_SetCursorVisible(_GetScreenPtr(), visible);
}

EXPORT void CALL bmSetCursorPosition(int x, int y) {
  p_SetCursorPosition(_GetScreenPtr(), x, y);
}

EXPORT int CALL bmGetCursorX() {
  return p_GetCursorX(_GetScreenPtr());
}

EXPORT int CALL bmGetCursorY() {
  return p_GetCursorY(_GetScreenPtr());
}

EXPORT bool_t CALL bmIsCursorPressed(int b) {
  return p_GetCursorPressed(_GetScreenPtr(), b);
}

EXPORT bool_t CALL bmIsKeyPressed(int k) {
  return p_GetKeyPressed(_GetScreenPtr(), k);
}

#endif /* PLATFORM_NULL */
