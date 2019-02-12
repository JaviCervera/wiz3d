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

`int color_rgb(int r, int g, int b)`

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

Creates a new light of the given type and returns a pointer to it. Supported types are `_LIGHT_DIRECTIONAL` and `_LIGHT_POINT`.

`void light_delete(struct light_t* light)`

Deletes the given light. You should not use the pointer after this.

`void light_move(struct light_t* light, float x, float y, float z)`

Moves the specified light by the given amount in local coordinates. For example, a positive z value will move the light forward in the direction that it is facing.

`void light_turn(struct light_t* light, float pitch, float yaw)`

Turns the light by the given pitch and yaw amounts.

`void light_setambient(int color)`
Sets the global ambient color of the scene.

`int light_ambient()`
Gets the global ambient color of the scene.

## log
The log module allows to print messages to the log file (which is the file "log.txt" that will be automatically created on the game folder).

`void log_info(const char* msg)`

Writes information to the log file.

`void log_warning(const char* msg)`

Writes a warning to the log file.

`void log_error(const char* msg)`

Writes an error to the log file. This will show a message box with the error message and will cause the program to abort.

## material

Materials define the way that 3D objects look. A material is defined by the following structure:

```
struct material_t
{
  struct texture_t* texture;
  int               diffuse;
  int               emissive;
  int               specular;
  float             shininess;
  int               blend;
  int               flags;
  int               shininesspower;
};
```

* `texture`: Color texture.
* `diffuse`: Diffuse color that indicates how it responds to lighting.
* `emissive`: Color that the object emits by itself, without the need to receive lighting.
* `specular`: Color of the specular reflections that this object produces.
* `shininess` A floating point value in the range 0...1 that indicates how shiny the object is. The shinier an object is, the more intense and concentrated its specular reflections are.
* `blend`: Specified how the object blends with its surroundings. Can be:
  * `_BLEND_SOLID`: The material is fully opaque.
  * `_BLEND_ALPHA`: Parts of the object can appear as transparent depending on the alpha of the texture and diffuse color.
  * `_BLEND_ADD`: The material is added to whatever is behind it. It looks as a transparent object (except for the white parts that would look opaque), and this mode is usually used on elements such as fire or sparks, because it makes the object appear brighter.
  * `_BLEND_MUL`: The material is multiplied with whatever is beneath it. Rarely used, but it is useful to darken or tint the background using the material.
* `flags`: Enables or disables some visual properties of the material. It can be a bitwise combination of:
  * `_FLAG_CULL`: Enables backface culling. This makes the backside of objects visible. Normally disabled with transparent objects.
  * `_FLAG_DEPTHWRITE`: Enables writing to the depth buffer. Normally disabled for some transparent materials like glass.
  * `_FLAG_LIGHTING`: Enables the material ability to respond to lighting.
  * `_FLAG_FOG`: Enables the material sensitivity to fog.
  * `_FLAG_ALL`: Enables all flags. This is the default setting.
* `shininesspower`: Indicates how fast the specular reflections vanish. It is a value in the range 0...128 that, multiplied by the shininess of the object, is used as exponent in the Blinn-Phong specular calculation. The default value is -1, which means that the global shininess power set by `material_setshininesspower` will be used.

You can get the material that an object uses and modify any of these properties.

`int material_shininesspower()`

Returns the default shininess power for all materials whose shininess power value is -1.


`void material_setshininesspower(int power)`

Sets the default shininess power for all materials whose shininess power value is -1. It has to be in the range 0..128, and initially has the value 128.
