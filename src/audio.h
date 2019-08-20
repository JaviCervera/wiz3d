#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include "spark_config.h"
#include "types.h"

#ifndef PLATFORM_NULL

#ifdef __cplusplus
extern "C" {
#endif

/* Music */
EXPORT bool_t CALL PlayMusic(const char* filename, bool_t loop);
EXPORT void CALL PauseMusic();
EXPORT void CALL ResumeMusic();
EXPORT void CALL StopMusic();
EXPORT void CALL SetMusicVolume(float volume);
EXPORT bool_t CALL IsMusicPlaying();

/* Sound */
EXPORT void* CALL LoadSound(const char* filename);
EXPORT void CALL DeleteSound(void* sound);
EXPORT void* CALL PlaySound(void* sound, bool_t loop);

/* Listener */
EXPORT void CALL PositionListener(float x, float y, float z);
EXPORT float CALL GetListenerX();
EXPORT float CALL GetListenerY();
EXPORT float CALL GetListenerZ();
EXPORT void CALL RotateListener(float yaw);
EXPORT float CALL GetListenerYaw();

/* Channel */
EXPORT void CALL PauseChannel(void* channel);
EXPORT void CALL ResumeChannel(void* channel);
EXPORT void CALL StopChannel(void* channel);
EXPORT void CALL PositionChannel(void* channel, float x, float y, float z, float radius);
EXPORT void CALL SetChannelVolume(void* channel, float volume);
EXPORT void CALL SetChannelPan(void* channel, float pan);
EXPORT void CALL SetChannelPitch(void* channel, float pitch);
EXPORT bool_t CALL IsChannelPlaying(void* channel);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_NULL */

#endif /* AUDIO_H_INCLUDED */
