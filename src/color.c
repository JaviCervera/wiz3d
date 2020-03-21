#include "color.h"
#include "util.h"

EXPORT int CALL bmGetRGB(int r, int g, int b) {
    r = _Clamp(r, 0, 255);
    g = _Clamp(g, 0, 255);
    b = _Clamp(b, 0, 255);
    return 0xff000000 | (r << 16) | (g << 8) | b;
}

EXPORT int CALL bmGetRGBA(int r, int g, int b, int a) {
    r = _Clamp(r, 0, 255);
    g = _Clamp(g, 0, 255);
    b = _Clamp(b, 0, 255);
    a = _Clamp(a, 0, 255);
    return (a << 24) | (r << 16) | (g << 8) | b;
}

EXPORT int CALL bmGetRed(int color) {
    return (color >> 16) & 0xff;
}

EXPORT int CALL bmGetGreen(int color) {
    return (color >> 8) & 0xff;
}

EXPORT int CALL bmGetBlue(int color) {
    return color & 0xff;
}

EXPORT int CALL bmGetAlpha(int color) {
    return (color >> 24) & 0xff;
}

EXPORT int CALL bmChangeAlpha(int color, int new_alpha) {
    new_alpha = _Clamp(new_alpha, 0, 255);
    return (new_alpha << 24) | (color & 0x00ffffff);
}

EXPORT int CALL bmMultiplyColor(int color, float factor) {
    return bmGetRGBA(
        (int)(bmGetRed(color) * factor),
        (int)(bmGetGreen(color) * factor),
        (int)(bmGetBlue(color) * factor),
        bmGetAlpha(color)
    );
}
