#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct channel_t;
struct sound_t;

bool_t sound_playmusic(const char* filename, bool_t loop);
void sound_pausemusic();
void sound_resumemusic();
void sound_stopmusic();
bool_t sound_musicplaying();
struct sound_t* sound_load(const char* filename);
void sound_free(struct sound_t* sound);
struct channel_t* sound_play(const struct sound_t* sound, bool_t loop);
//struct channel_t* sound_play3d(const struct sound_t* sound, bool_t loop);
void sound_pausechannel(const struct channel_t* channel);
void sound_resumechannel(const struct channel_t* channel);
void sound_stopchannel(const struct channel_t* channel);
bool_t sound_channelplaying(const struct channel_t* channel);

#ifndef SWIG
bool_t _sound_initaudio();
void _sound_deinitaudio();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SOUND_H_INCLUDED */
