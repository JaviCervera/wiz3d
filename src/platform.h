#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "beam_config.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

bool_t p_Init();
void p_Shutdown();

float p_GetTime();

void p_SetCursorVisible(void* win, bool_t visible);
void p_SetCursorPosition(void* win, int x, int y);
int p_GetCursorX(void* win);
int p_GetCursorY(void* win);

bool_t p_GetCursorPressed(void* win, int button);
bool_t p_GetKeyPressed(void* win, int key);

int p_GetDesktopWidth();
int p_GetDesktopHeight();

void* p_OpenScreen(int width, int height, bool_t fullscreen, int samples, bool_t vsync, bool_t resizable);
void p_CloseScreen(void* win);
bool_t p_IsScreenOpened(void* win);
void p_RefreshScreen(void* win);
void p_SetScreenTitle(void* win, const char* title);
int p_GetScreenWidth(void* win);
int p_GetScreenHeight(void* win);

void p_MessageBox(const char* title, const char* message);

#ifdef USE_AUDIO
bool_t p_PlayMusic(const char* filename, bool_t loop);
void p_PauseMusic();
void p_ResumeMusic();
void p_StopMusic();
void p_SetMusicVolume(float volume);
bool_t p_IsMusicPlaying();
void* p_LoadSound(const char* filename);
void p_DeleteSound(void* sound);
void* p_PlaySound(void* sound, bool_t loop);
void p_PauseChannel(void* channel);
void p_ResumeChannel(void* channel);
void p_StopChannel(void* channel);
void p_PositionChannel(void* channel, float lx, float ly, float lz, float lyaw, float sx, float sy, float sz, float radius);
void p_SetChannelVolume(void* channel, float volume);
void p_SetChannelPan(void* channel, float pan);
void p_SetChannelPitch(void* channel, float pitch);
bool_t p_IsChannelPlaying(void* channel);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLATFORM_H_INCLUDED */
