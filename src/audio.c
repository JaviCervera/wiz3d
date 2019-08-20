#include "spark_config.h"

#ifndef PLATFORM_NULL

#include "audio.h"
#include "platform.h"

#ifdef USE_AUDIO
static float _listener_x = 0;
static float _listener_y = 0;
static float _listener_z = 0;
static float _listener_yaw = 0;
#endif

EXPORT bool_t CALL PlayMusic(const char* filename, bool_t loop) {
#ifdef USE_AUDIO
  return p_PlayMusic(filename, loop);
#else
  return FALSE;
#endif
}

EXPORT void CALL PauseMusic() {
#ifdef USE_AUDIO
  p_PauseMusic();
#endif
}

EXPORT void CALL ResumeMusic() {
#ifdef USE_AUDIO
  p_ResumeMusic();
#endif
}

EXPORT void CALL StopMusic() {
#ifdef USE_AUDIO
  p_StopMusic();
#endif
}

EXPORT void CALL SetMusicVolume(float volume) {
#ifdef USE_AUDIO
  p_SetMusicVolume(volume);
#endif
}

EXPORT bool_t CALL IsMusicPlaying() {
#ifdef USE_AUDIO
  return p_IsMusicPlaying();
#else
  return FALSE;
#endif
}


EXPORT void* CALL LoadSound(const char* filename) {
#ifdef USE_AUDIO
  return p_LoadSound(filename);
#else
  return NULL;
#endif
}

EXPORT void CALL DeleteSound(void* sound) {
#ifdef USE_AUDIO
  p_DeleteSound(sound);
#endif
}

EXPORT void* CALL PlaySound(void* sound, bool_t loop) {
#ifdef USE_AUDIO
  return p_PlaySound(sound, loop);
#else
  return NULL;
#endif
}

EXPORT void CALL PositionListener(float x, float y, float z) {
#ifdef USE_AUDIO
  _listener_x = x;
  _listener_y = y;
  _listener_z = z;
#endif
}

EXPORT float CALL GetListenerX() {
#ifdef USE_AUDIO
  return _listener_x;
#else
  return 0;
#endif
}

EXPORT float CALL GetListenerY() {
#ifdef USE_AUDIO
  return _listener_y;
#else
  return 0;
#endif
}

EXPORT float CALL GetListenerZ() {
#ifdef USE_AUDIO
  return _listener_z;
#else
  return 0;
#endif
}

EXPORT void CALL RotateListener(float yaw) {
#ifdef USE_AUDIO
  _listener_yaw = yaw;
#endif
}

EXPORT float CALL GetListenerYaw() {
#ifdef USE_AUDIO
  return _listener_yaw;
#else
  return 0;
#endif
}

EXPORT void CALL PauseChannel(void* channel) {
#ifdef USE_AUDIO
  p_PauseChannel(channel);
#endif
}

EXPORT void CALL ResumeChannel(void* channel) {
#ifdef USE_AUDIO
  p_ResumeChannel(channel);
#endif
}

EXPORT void CALL StopChannel(void* channel) {
#ifdef USE_AUDIO
  p_StopChannel(channel);
#endif
}

EXPORT void CALL PositionChannel(void* channel, float x, float y, float z, float radius) {
#ifdef USE_AUDIO
  p_PositionChannel(channel, _listener_x, _listener_y, _listener_z, _listener_yaw, x, y, z, radius);
#endif
}

EXPORT void CALL SetChannelVolume(void* channel, float volume) {
#ifdef USE_AUDIO
  p_SetChannelVolume(channel, volume);
#endif
}

EXPORT void CALL SetChannelPan(void* channel, float pan) {
#ifdef USE_AUDIO
  p_SetChannelPan(channel, pan);
#endif
}

EXPORT void CALL SetChannelPitch(void* channel, float pitch) {
#ifdef USE_AUDIO
  p_SetChannelPitch(channel, pitch);
#endif
}

EXPORT bool_t CALL IsChannelPlaying(void* channel) {
#ifdef USE_AUDIO
  return p_IsChannelPlaying(channel);
#else
  return FALSE;
#endif
}

#endif /* PLATFORM_NULL */
