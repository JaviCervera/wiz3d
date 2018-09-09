#include "color.h"

int color_rgb(int r, int g, int b)
{
  return 0xff000000 | (r << 16) | (g << 8) | b;
}

int color_rgba(int r, int g, int b, int a)
{
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
  return (new_alpha << 24) | (color & 0x00ffffff);
}

int color_multiply(int color, float factor)
{
  return color_rgba(
    (int)(color_red(color) * factor),
    (int)(color_green(color) * factor),
    (int)(color_blue(color) * factor),
    color_alpha(color));
}
