#include "spark_config.h"

#ifndef PLATFORM_NULL

#include "input.h"
#include "platform.h"
#include "screen.h"

EXPORT void CALL spSetCursorVisible(bool_t visible) {
  p_SetCursorVisible(_GetScreenPtr(), visible);
}

EXPORT void CALL spSetCursorPosition(int x, int y) {
  p_SetCursorPosition(_GetScreenPtr(), x, y);
}

EXPORT int CALL spGetCursorX() {
  return p_GetCursorX(_GetScreenPtr());
}

EXPORT int CALL spGetCursorY() {
  return p_GetCursorY(_GetScreenPtr());
}

EXPORT bool_t CALL spIsCursorPressed(int b) {
  return p_GetCursorPressed(_GetScreenPtr(), b);
}

EXPORT bool_t CALL spIsKeyPressed(int k) {
  return p_GetKeyPressed(_GetScreenPtr(), k);
}

#endif /* PLATFORM_NULL */
