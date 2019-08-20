#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "spark_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL SetScreen(int width, int height, bool_t fullscreen, bool_t resizable);
EXPORT void CALL RefreshScreen();
EXPORT void CALL SetScreenTitle(const char* title);
EXPORT int CALL GetScreenWidth();
EXPORT int CALL GetScreenHeight();
EXPORT int CALL GetScreenFPS();
EXPORT bool_t CALL IsScreenOpened();

EXPORT int CALL GetDesktopWidth();
EXPORT int CALL GetDesktopHeight();

#ifndef SWIG
void* _GetScreenPtr();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* SCREEN_H_INCLUDED */
