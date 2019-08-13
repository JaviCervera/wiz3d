#ifndef BEAM_CONFIG_H_INCLUDED
#define BEAM_CONFIG_H_INCLUDED

/* Some limits used by the engine */
#define STRING_SIZE     64
#define NUM_LIGHTS      8
#define NUM_CHANNELS    8

/* Supported platforms (enable ONLY ONE) */
/*#define USE_ALLEGRO*/ /*** NOT FINISHED ***/
/*#define USE_GLFW*/
#define USE_SDL2

/*#define USE_AUDIO*/
#define USE_DEFAULT_FONT
#define USE_PAK
/*#define USE_RETINA*/
/*#define USE_TINYFILEDIALOGS*/ /* Only used by GLFW platform */

#endif /* BEAM_CONFIG_H_INCLUDED */
