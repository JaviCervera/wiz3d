#include "color.h"
#include "util.h"

int color_rgb(int r, int g, int b)
{
  r = _clamp(r, 0, 255);
  g = _clamp(g, 0, 255);
  b = _clamp(b, 0, 255);
  return 0xff000000 | (r << 16) | (g << 8) | b;
}

int color_rgba(int r, int g, int b, int a)
{
  r = _clamp(r, 0, 255);
  g = _clamp(g, 0, 255);
  b = _clamp(b, 0, 255);
  a = _clamp(a, 0, 255);
  return (a << 24) | (r << 16) | (g << 8) | b;
}

int color_red(int color)
{
  return (color >> 16) & 0xff;
}
int color_green(int color)
{
  return (color >> 8) & 0xff;
}

int color_blue(int color)
{
  return color & 0xff;
}

int color_alpha(int color)
{
  return (color >> 24) & 0xff;
}

int color_changealpha(int color, int new_alpha)
{
  new_alpha = _clamp(new_alpha, 0, 255);
  return (new_alpha << 24) | (color & 0x00ffffff);
}

int color_multiply(int color, float factor)
{
  return color_rgba(
    (int)(color_red(color) * factor),
    (int)(color_green(color) * factor),
    (int)(color_blue(color) * factor),
    color_alpha(color)
  );
}
