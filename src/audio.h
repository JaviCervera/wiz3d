#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include "beam_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

/* Music */
EXPORT bool_t CALL bmPlayMusic(const char* filename, bool_t loop);
EXPORT void CALL bmPauseMusic();
EXPORT void CALL bmResumeMusic();
EXPORT void CALL bmStopMusic();
EXPORT void CALL bmSetMusicVolume(float volume);
EXPORT bool_t CALL bmIsMusicPlaying();

/* Sound */
EXPORT void* CALL bmLoadSound(const char* filename);
EXPORT void CALL bmDeleteSound(void* sound);
EXPORT void* CALL bmPlaySound(void* sound, bool_t loop);

/* Listener */
EXPORT void CALL bmPositionListener(float x, float y, float z);
EXPORT float CALL bmGetListenerX();
EXPORT float CALL bmGetListenerY();
EXPORT float CALL bmGetListenerZ();
EXPORT void CALL bmRotateListener(float yaw);
EXPORT float CALL bmGetListenerYaw();

/* Channel */
EXPORT void CALL bmPauseChannel(void* channel);
EXPORT void CALL bmResumeChannel(void* channel);
EXPORT void CALL bmStopChannel(void* channel);
EXPORT void CALL bmPositionChannel(void* channel, float x, float y, float z, float radius);
EXPORT void CALL bmSetChannelVolume(void* channel, float volume);
EXPORT void CALL bmSetChannelPan(void* channel, float pan);
EXPORT void CALL bmSetChannelPitch(void* channel, float pitch);
EXPORT bool_t CALL bmIsChannelPlaying(void* channel);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* AUDIO_H_INCLUDED */
