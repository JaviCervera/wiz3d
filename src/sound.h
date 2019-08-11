#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct channel_t;
struct sound_t;

EXPORT bool_t CALL sound_playmusic(const char* filename, bool_t loop);
EXPORT void CALL sound_pausemusic();
EXPORT void CALL sound_resumemusic();
EXPORT void CALL sound_stopmusic();
EXPORT bool_t CALL sound_musicplaying();
EXPORT struct sound_t* CALL sound_load(const char* filename);
EXPORT void CALL sound_free(struct sound_t* sound);
EXPORT struct channel_t* CALL sound_play(const struct sound_t* sound, bool_t loop);
//EXPORT struct channel_t* CALL sound_play3d(const struct sound_t* sound, bool_t loop);
EXPORT void CALL sound_pausechannel(const struct channel_t* channel);
EXPORT void CALL sound_resumechannel(const struct channel_t* channel);
EXPORT void CALL sound_stopchannel(const struct channel_t* channel);
EXPORT bool_t CALL sound_channelplaying(const struct channel_t* channel);

#ifndef SWIG
bool_t _sound_initaudio();
void _sound_deinitaudio();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SOUND_H_INCLUDED */
