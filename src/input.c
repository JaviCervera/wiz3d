#include "input.h"
#include "platform.h"
#include "screen.h"

EXPORT void CALL SetCursorVisible(bool_t visible) {
  p_SetCursorVisible(_GetScreenPtr(), visible);
}

EXPORT void CALL SetCursorPosition(int x, int y) {
  p_SetCursorPosition(_GetScreenPtr(), x, y);
}

EXPORT int CALL GetCursorX() {
  return p_GetCursorX(_GetScreenPtr());
}

EXPORT int CALL GetCursorY() {
  return p_GetCursorY(_GetScreenPtr());
}

EXPORT bool_t CALL IsCursorPressed(int b) {
  return p_GetCursorPressed(_GetScreenPtr(), b);
}

EXPORT bool_t CALL IsKeyPressed(int k) {
  return p_GetKeyPressed(_GetScreenPtr(), k);
}
