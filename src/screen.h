#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "wiz3d_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL wzSetScreen(int width, int height, bool_t fullscreen, bool_t resizable);
EXPORT void CALL wzRefreshScreen();
EXPORT void CALL wzSetScreenTitle(const char* title);
EXPORT int CALL wzGetScreenWidth();
EXPORT int CALL wzGetScreenHeight();
EXPORT int CALL wzGetScreenFPS();
EXPORT bool_t CALL wzIsScreenOpened();

EXPORT int CALL wzGetDesktopWidth();
EXPORT int CALL wzGetDesktopHeight();

#ifndef SWIG
void* _GetScreenPtr();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* SCREEN_H_INCLUDED */
