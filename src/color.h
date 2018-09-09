#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include "types.h"

#define _COLOR_RED        -65536
#define _COLOR_GREEN      -16711936
#define _COLOR_BLUE       -16776961
#define _COLOR_CYAN       -16711681
#define _COLOR_MAGENTA    -65281
#define _COLOR_YELLOW     -256
#define _COLOR_BLACK      -16777216
#define _COLOR_WHITE      -1
#define _COLOR_GRAY       -8355712
#define _COLOR_LIGHTGRAY -4210753
#define _COLOR_DARKGRAY  -12566464
#define _COLOR_ORANGE     -23296
#define _COLOR_BROWN      -7650029

#ifdef __cplusplus
extern "C"
{
#endif

int color_rgb(int r, int g, int b);
int color_rgba(int r, int g, int b, int a);
int color_red(int color);
int color_green(int color);
int color_blue(int color);
int color_alpha(int color);
int color_changealpha(int color, int new_alpha);
int color_multiply(int color, float factor);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COLOR_H_INCLUDED */
