#include "color.h"
#include "util.h"

EXPORT int CALL spGetRGB(int r, int g, int b) {
  r = _Clamp(r, 0, 255);
  g = _Clamp(g, 0, 255);
  b = _Clamp(b, 0, 255);
  return 0xff000000 | (r << 16) | (g << 8) | b;
}

EXPORT int CALL spGetRGBA(int r, int g, int b, int a) {
  r = _Clamp(r, 0, 255);
  g = _Clamp(g, 0, 255);
  b = _Clamp(b, 0, 255);
  a = _Clamp(a, 0, 255);
  return (a << 24) | (r << 16) | (g << 8) | b;
}

EXPORT int CALL spGetRed(int color) {
  return (color >> 16) & 0xff;
}

EXPORT int CALL spGetGreen(int color) {
  return (color >> 8) & 0xff;
}

EXPORT int CALL spGetBlue(int color) {
  return color & 0xff;
}

EXPORT int CALL spGetAlpha(int color) {
  return (color >> 24) & 0xff;
}

EXPORT int CALL spChangeAlpha(int color, int new_alpha) {
  new_alpha = _Clamp(new_alpha, 0, 255);
  return (new_alpha << 24) | (color & 0x00ffffff);
}

EXPORT int CALL spMultiplyColor(int color, float factor) {
  return spGetRGBA(
    (int)(spGetRed(color) * factor),
    (int)(spGetGreen(color) * factor),
    (int)(spGetBlue(color) * factor),
    spGetAlpha(color)
  );
}
