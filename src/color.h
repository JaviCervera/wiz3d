#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include "types.h"

#define COLOR_RED                -65536
#define COLOR_GREEN            -16711936
#define COLOR_BLUE             -16776961
#define COLOR_CYAN             -16711681
#define COLOR_MAGENTA        -65281
#define COLOR_YELLOW         -256
#define COLOR_BLACK            -16777216
#define COLOR_WHITE            -1
#define COLOR_GRAY             -8355712
#define COLOR_LIGHTGRAY -4210753
#define COLOR_DARKGRAY    -12566464
#define COLOR_ORANGE         -23296
#define COLOR_BROWN            -7650029

#ifdef __cplusplus
extern "C" {
#endif

EXPORT int CALL bmGetRGB(int r, int g, int b);
EXPORT int CALL bmGetRGBA(int r, int g, int b, int a);
EXPORT int CALL bmGetRed(int color);
EXPORT int CALL bmGetGreen(int color);
EXPORT int CALL bmGetBlue(int color);
EXPORT int CALL bmGetAlpha(int color);
EXPORT int CALL bmChangeAlpha(int color, int new_alpha);
EXPORT int CALL bmMultiplyColor(int color, float factor);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COLOR_H_INCLUDED */
