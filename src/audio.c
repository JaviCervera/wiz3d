#include "beam_config.h"

#ifndef PLATFORM_NULL

#include "audio.h"
#include "platform.h"

#ifdef USE_AUDIO
static float _listener_x = 0;
static float _listener_y = 0;
static float _listener_z = 0;
static float _listener_yaw = 0;
#endif

bool_t PlayMusic(const char* filename, bool_t loop) {
#ifdef USE_AUDIO
  return p_PlayMusic(filename, loop);
#else
  return FALSE;
#endif
}

void PauseMusic() {
#ifdef USE_AUDIO
  p_PauseMusic();
#endif
}

void ResumeMusic() {
#ifdef USE_AUDIO
  p_ResumeMusic();
#endif
}

void StopMusic() {
#ifdef USE_AUDIO
  p_StopMusic();
#endif
}

void SetMusicVolume(float volume) {
#ifdef USE_AUDIO
  p_SetMusicVolume(volume);
#endif
}

bool_t IsMusicPlaying() {
#ifdef USE_AUDIO
  return p_IsMusicPlaying();
#else
  return FALSE;
#endif
}


void* LoadSound(const char* filename) {
#ifdef USE_AUDIO
  return p_LoadSound(filename);
#else
  return NULL;
#endif
}

void DeleteSound(void* sound) {
#ifdef USE_AUDIO
  p_DeleteSound(sound);
#endif
}

void* PlaySound(void* sound, bool_t loop) {
#ifdef USE_AUDIO
  return p_PlaySound(sound, loop);
#else
  return NULL;
#endif
}

void PositionListener(float x, float y, float z) {
#ifdef USE_AUDIO
  _listener_x = x;
  _listener_y = y;
  _listener_z = z;
#endif
}

float GetListenerX() {
#ifdef USE_AUDIO
  return _listener_x;
#else
  return 0;
#endif
}

float GetListenerY() {
#ifdef USE_AUDIO
  return _listener_y;
#else
  return 0;
#endif
}

float GetListenerZ() {
#ifdef USE_AUDIO
  return _listener_z;
#else
  return 0;
#endif
}

void RotateListener(float yaw) {
#ifdef USE_AUDIO
  _listener_yaw = yaw;
#endif
}

float GetListenerYaw() {
#ifdef USE_AUDIO
  return _listener_yaw;
#else
  return 0;
#endif
}

void PauseChannel(void* channel) {
#ifdef USE_AUDIO
  p_PauseChannel(channel);
#endif
}

void ResumeChannel(void* channel) {
#ifdef USE_AUDIO
  p_ResumeChannel(channel);
#endif
}

void StopChannel(void* channel) {
#ifdef USE_AUDIO
  p_StopChannel(channel);
#endif
}

void PositionChannel(void* channel, float x, float y, float z, float radius) {
#ifdef USE_AUDIO
  p_PositionChannel(channel, _listener_x, _listener_y, _listener_z, _listener_yaw, x, y, z, radius);
#endif
}

void SetChannelVolume(void* channel, float volume) {
#ifdef USE_AUDIO
  p_SetChannelVolume(channel, volume);
#endif
}

void SetChannelPan(void* channel, float pan) {
#ifdef USE_AUDIO
  p_SetChannelPan(channel, pan);
#endif
}

void SetChannelPitch(void* channel, float pitch) {
#ifdef USE_AUDIO
  p_SetChannelPitch(channel, pitch);
#endif
}

bool_t IsChannelPlaying(void* channel) {
#ifdef USE_AUDIO
  return p_IsChannelPlaying(channel);
#else
  return FALSE;
#endif
}

#endif /* PLATFORM_NULL */
