#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include "spark_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

/* Music */
EXPORT bool_t CALL spPlayMusic(const char* filename, bool_t loop);
EXPORT void CALL spPauseMusic();
EXPORT void CALL spResumeMusic();
EXPORT void CALL spStopMusic();
EXPORT void CALL spSetMusicVolume(float volume);
EXPORT bool_t CALL spIsMusicPlaying();

/* Sound */
EXPORT void* CALL spLoadSound(const char* filename);
EXPORT void CALL spDeleteSound(void* sound);
EXPORT void* CALL spPlaySound(void* sound, bool_t loop);

/* Listener */
EXPORT void CALL spPositionListener(float x, float y, float z);
EXPORT float CALL spGetListenerX();
EXPORT float CALL spGetListenerY();
EXPORT float CALL spGetListenerZ();
EXPORT void CALL spRotateListener(float yaw);
EXPORT float CALL spGetListenerYaw();

/* Channel */
EXPORT void CALL spPauseChannel(void* channel);
EXPORT void CALL spResumeChannel(void* channel);
EXPORT void CALL spStopChannel(void* channel);
EXPORT void CALL spPositionChannel(void* channel, float x, float y, float z, float radius);
EXPORT void CALL spSetChannelVolume(void* channel, float volume);
EXPORT void CALL spSetChannelPan(void* channel, float pan);
EXPORT void CALL spSetChannelPitch(void* channel, float pitch);
EXPORT bool_t CALL spIsChannelPlaying(void* channel);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* AUDIO_H_INCLUDED */
