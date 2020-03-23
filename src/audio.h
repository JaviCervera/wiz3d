#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include "wiz3d_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

/* Music */
EXPORT bool_t CALL wzPlayMusic(const char* filename, bool_t loop);
EXPORT void CALL wzPauseMusic();
EXPORT void CALL wzResumeMusic();
EXPORT void CALL wzStopMusic();
EXPORT void CALL wzSetMusicVolume(float volume);
EXPORT bool_t CALL wzIsMusicPlaying();

/* Sound */
EXPORT void* CALL wzLoadSound(const char* filename);
EXPORT void CALL wzDeleteSound(void* sound);
EXPORT void* CALL wzPlaySound(void* sound, bool_t loop);

/* Listener */
EXPORT void CALL wzPositionListener(float x, float y, float z);
EXPORT float CALL wzGetListenerX();
EXPORT float CALL wzGetListenerY();
EXPORT float CALL wzGetListenerZ();
EXPORT void CALL wzRotateListener(float yaw);
EXPORT float CALL wzGetListenerYaw();

/* Channel */
EXPORT void CALL wzPauseChannel(void* channel);
EXPORT void CALL wzResumeChannel(void* channel);
EXPORT void CALL wzStopChannel(void* channel);
EXPORT void CALL wzPositionChannel(void* channel, float x, float y, float z, float radius);
EXPORT void CALL wzSetChannelVolume(void* channel, float volume);
EXPORT void CALL wzSetChannelPan(void* channel, float pan);
EXPORT void CALL wzSetChannelPitch(void* channel, float pitch);
EXPORT bool_t CALL wzIsChannelPlaying(void* channel);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* AUDIO_H_INCLUDED */
