#include "wiz3d_config.h"

#ifndef PLATFORM_NULL

#include "audio.h"
#include "platform.h"

#ifdef USE_AUDIO
static float _listener_x = 0;
static float _listener_y = 0;
static float _listener_z = 0;
static float _listener_yaw = 0;
#endif

EXPORT bool_t CALL wzPlayMusic(const char* filename, bool_t loop) {
#ifdef USE_AUDIO
    return p_PlayMusic(filename, loop);
#else
    return FALSE;
#endif
}

EXPORT void CALL wzPauseMusic() {
#ifdef USE_AUDIO
    p_PauseMusic();
#endif
}

EXPORT void CALL wzResumeMusic() {
#ifdef USE_AUDIO
    p_ResumeMusic();
#endif
}

EXPORT void CALL wzStopMusic() {
#ifdef USE_AUDIO
    p_StopMusic();
#endif
}

EXPORT void CALL wzSetMusicVolume(float volume) {
#ifdef USE_AUDIO
    p_SetMusicVolume(volume);
#endif
}

EXPORT bool_t CALL wzIsMusicPlaying() {
#ifdef USE_AUDIO
    return p_IsMusicPlaying();
#else
    return FALSE;
#endif
}


EXPORT void* CALL wzLoadSound(const char* filename) {
#ifdef USE_AUDIO
    return p_LoadSound(filename);
#else
    return NULL;
#endif
}

EXPORT void CALL wzDeleteSound(void* sound) {
#ifdef USE_AUDIO
    p_DeleteSound(sound);
#endif
}

EXPORT void* CALL wzPlaySound(void* sound, bool_t loop) {
#ifdef USE_AUDIO
    return p_PlaySound(sound, loop);
#else
    return NULL;
#endif
}

EXPORT void CALL wzPositionListener(float x, float y, float z) {
#ifdef USE_AUDIO
    _listener_x = x;
    _listener_y = y;
    _listener_z = z;
#endif
}

EXPORT float CALL wzGetListenerX() {
#ifdef USE_AUDIO
    return _listener_x;
#else
    return 0;
#endif
}

EXPORT float CALL wzGetListenerY() {
#ifdef USE_AUDIO
    return _listener_y;
#else
    return 0;
#endif
}

EXPORT float CALL wzGetListenerZ() {
#ifdef USE_AUDIO
    return _listener_z;
#else
    return 0;
#endif
}

EXPORT void CALL wzRotateListener(float yaw) {
#ifdef USE_AUDIO
    _listener_yaw = yaw;
#endif
}

EXPORT float CALL wzGetListenerYaw() {
#ifdef USE_AUDIO
    return _listener_yaw;
#else
    return 0;
#endif
}

EXPORT void CALL wzPauseChannel(void* channel) {
#ifdef USE_AUDIO
    p_PauseChannel(channel);
#endif
}

EXPORT void CALL wzResumeChannel(void* channel) {
#ifdef USE_AUDIO
    p_ResumeChannel(channel);
#endif
}

EXPORT void CALL wzStopChannel(void* channel) {
#ifdef USE_AUDIO
    p_StopChannel(channel);
#endif
}

EXPORT void CALL wzPositionChannel(void* channel, float x, float y, float z, float radius) {
#ifdef USE_AUDIO
    p_PositionChannel(channel, _listener_x, _listener_y, _listener_z, _listener_yaw, x, y, z, radius);
#endif
}

EXPORT void CALL wzSetChannelVolume(void* channel, float volume) {
#ifdef USE_AUDIO
    p_SetChannelVolume(channel, volume);
#endif
}

EXPORT void CALL wzSetChannelPan(void* channel, float pan) {
#ifdef USE_AUDIO
    p_SetChannelPan(channel, pan);
#endif
}

EXPORT void CALL wzSetChannelPitch(void* channel, float pitch) {
#ifdef USE_AUDIO
    p_SetChannelPitch(channel, pitch);
#endif
}

EXPORT bool_t CALL wzIsChannelPlaying(void* channel) {
#ifdef USE_AUDIO
    return p_IsChannelPlaying(channel);
#else
    return FALSE;
#endif
}

#endif /* PLATFORM_NULL */
