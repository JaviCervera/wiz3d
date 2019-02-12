# Introduction
...

# Modules

## colbox
This module allows the addition of static collision boxes to your scene.

`void colbox_add(float minx, float miny, float minz, float maxx, float maxy, float maxz)`
Adds a new collision box to the scene within the given boundaries.

`void colbox_clear()`
Clears all collision boxes.

## color
Colors are stored as standard integers. Using this module, you can extract the RGBA components from a given color, multiply the components by a given factor and change the alpha alone. The following constants with common colors are also predefined:

| Color values |
| ---------- |
| `_COLOR_RED` |
| `_COLOR_GREEN` |
| `_COLOR_BLUE` |
| `_COLOR_CYAN` |
| `_COLOR_MAGENTA` |
| `_COLOR_YELLOW` |
| `_COLOR_BLACK` |
| `_COLOR_WHITE` |
| `_COLOR_GRAY` |
| `_COLOR_LIGHTGRAY` |
| `_COLOR_DARKGRAY` |
| `_COLOR_ORANGE` |
| `_COLOR_BROWN` |

```int color_rgb(int r, int g, int b)```
Returns a fully opaque color with the given RGB values. Each component should be given in the range 0...255.

`int color_rgba(int r, int g, int b, int a)`
Returns a color with the given RGBA values. Each component should be given in the range 0...255.

`int color_red(int color)`
Returns the red value of the given color, in the range 0...255.

`int color_green(int color)`
Returns the green value of the given color, in the range 0...255.

`int color_blue(int color)`
Returns the blue value of the given color, in the range 0...255.

`int color_alpha(int color)`
Returns the alpha value of the given color, in the range 0...255.

`int color_changealpha(int color, int new_alpha)`
Returns a color with the same RGB values of the given color and the specified alpha value, which should be in the range 0...255.

`int color_multiply(int color, float factor)`
Multiplies the RGBA values of the given color by the specified factor. All values are clamped to the range 0...255.

## input
Support keyboard and mouse input. Mouse buttons are represented by the following constants:

| Mouse buttons |
| ------------- |
| `_MOUSE_LEFT` |
| `_MOUSE_RIGHT` |
| `_MOUSE_MIDDLE` |

There are also constants defined for every key, i.e. `_KEY_ESC`, `_KEY_SPACE`, `_KEY_ENTER`, `_KEY_UP`, `_KEY_A`, `_KEY_LEFT_CONTROL`, `_KEY_LEFT_SUPER`, etc.

`void input_setmousevisible(bool_t visible)`
Shows or hides the mouse pointer.

`void input_setmouseposition(int x, int y)`
Moves the mouse pointer to the specified coordinates.

`int input_mousex()`
Returns the x coordinate of the mouse pointer, measured as the distance from the left of the screen.

`int input_mousey()`
Returns the y coordinate of the mouse pointer, measured as the distance from the top of the screen.

`bool_t input_mousedown(int b)`
Tells whether the given mouse button is pressed or not.

`bool_t input_keydown(int k)`
Tells whether the given key is pressed or not.

## light
Micron allows the definition of up to 8 lights in the scene. Directional and point lights are supported. Each light is represented by the following structure:

```
struct light_t
{
  float x, y, z;
  float pitch, yaw;
  int   type;
  int   color;
  float range;
};
```

`struct light_t* light_new(int type)`

void light_delete(struct light_t* light);
void light_move(struct light_t* light, float x, float y, float z);
void light_turn(struct light_t* light, float pitch, float yaw);
void light_setambient(int color);
int light_ambient();
