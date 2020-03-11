#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "beam_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL bmSetScreen(int width, int height, bool_t fullscreen, bool_t resizable);
EXPORT void CALL bmRefreshScreen();
EXPORT void CALL bmSetScreenTitle(const char* title);
EXPORT int CALL bmGetScreenWidth();
EXPORT int CALL bmGetScreenHeight();
EXPORT int CALL bmGetScreenFPS();
EXPORT bool_t CALL bmIsScreenOpened();

EXPORT int CALL bmGetDesktopWidth();
EXPORT int CALL bmGetDesktopHeight();

#ifndef SWIG
void* _GetScreenPtr();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* SCREEN_H_INCLUDED */
