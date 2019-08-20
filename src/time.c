#include "platform.h"
#include "time.h"

static float _delta_time = 0;
static float _last_time = 0;

EXPORT void CALL spUpdateTimer() {
  /* Update delta time */
  _delta_time = p_GetTime() - _last_time;
  _last_time = p_GetTime();
}

EXPORT float CALL spGetDeltaTime() {
  return _delta_time;
}
