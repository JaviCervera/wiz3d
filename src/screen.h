#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "spark_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL spSetScreen(int width, int height, bool_t fullscreen, bool_t resizable);
EXPORT void CALL spRefreshScreen();
EXPORT void CALL spSetScreenTitle(const char* title);
EXPORT int CALL spGetScreenWidth();
EXPORT int CALL spGetScreenHeight();
EXPORT int CALL spGetScreenFPS();
EXPORT bool_t CALL spIsScreenOpened();

EXPORT int CALL spGetDesktopWidth();
EXPORT int CALL spGetDesktopHeight();

#ifndef SWIG
void* _GetScreenPtr();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* SCREEN_H_INCLUDED */
