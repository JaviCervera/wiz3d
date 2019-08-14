#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include "beam_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

/* Music */
bool_t PlayMusic(const char* filename, bool_t loop);
void PauseMusic();
void ResumeMusic();
void StopMusic();
void SetMusicVolume(float volume);
bool_t IsMusicPlaying();

/* Sound */
void* LoadSound(const char* filename);
void DeleteSound(void* sound);
void* PlaySound(void* sound, bool_t loop);

/* Listener */
void PositionListener(float x, float y, float z);
float GetListenerX();
float GetListenerY();
float GetListenerZ();
void RotateListener(float yaw);
float GetListenerYaw();

/* Channel */
void PauseChannel(void* channel);
void ResumeChannel(void* channel);
void StopChannel(void* channel);
void PositionChannel(void* channel, float x, float y, float z, float radius);
void SetChannelVolume(void* channel, float volume);
void SetChannelPan(void* channel, float pan);
void SetChannelPitch(void* channel, float pitch);
bool_t IsChannelPlaying(void* channel);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* AUDIO_H_INCLUDED */
