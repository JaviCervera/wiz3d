#include "color.h"
#include "util.h"

EXPORT int CALL wzGetRGB(int r, int g, int b) {
    r = _Clamp(r, 0, 255);
    g = _Clamp(g, 0, 255);
    b = _Clamp(b, 0, 255);
    return 0xff000000 | (r << 16) | (g << 8) | b;
}

EXPORT int CALL wzGetRGBA(int r, int g, int b, int a) {
    r = _Clamp(r, 0, 255);
    g = _Clamp(g, 0, 255);
    b = _Clamp(b, 0, 255);
    a = _Clamp(a, 0, 255);
    return (a << 24) | (r << 16) | (g << 8) | b;
}

EXPORT int CALL wzGetRed(int color) {
    return (color >> 16) & 0xff;
}

EXPORT int CALL wzGetGreen(int color) {
    return (color >> 8) & 0xff;
}

EXPORT int CALL wzGetBlue(int color) {
    return color & 0xff;
}

EXPORT int CALL wzGetAlpha(int color) {
    return (color >> 24) & 0xff;
}

EXPORT int CALL wzChangeAlpha(int color, int new_alpha) {
    new_alpha = _Clamp(new_alpha, 0, 255);
    return (new_alpha << 24) | (color & 0x00ffffff);
}

EXPORT int CALL wzMultiplyColor(int color, float factor) {
    return wzGetRGBA(
        (int)(wzGetRed(color) * factor),
        (int)(wzGetGreen(color) * factor),
        (int)(wzGetBlue(color) * factor),
        wzGetAlpha(color)
    );
}
