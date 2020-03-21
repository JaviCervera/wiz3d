#ifndef BEAM_CONFIG_H_INCLUDED
#define BEAM_CONFIG_H_INCLUDED

/* Beam can be embedded in an application that already uses an OpenGL
     context, or can be configured to embed Allegro, GLFW or SDL2, by
     defining ONE of this macros when compiling (you can define the macro
     in this file directly, or set it with -DPLATFORM_NAME on Make or CMake):
     - PLATFORM_NULL (to manage context yourself)
     - PLATFORM_ALLEGRO
     - PLATFORM_GLFW
     - PLATFORM_SDL2
     With the null platform screen, input and audio functions are not
     available, and you must deal with this functionality yourself.
 */

/*#define USE_AUDIO*/
#define USE_DEFAULT_FONT
#define USE_PAK
/*#define USE_RETINA*/
#define USE_TINYFILEDIALOGS /* Only used by GLFW and NULL platforms */

/* Some limits used by the engine */
#define STRING_SIZE         64
#define NUM_LIGHTS            8
#define NUM_CHANNELS        8

#endif /* BEAM_CONFIG_H_INCLUDED */
