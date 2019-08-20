#include "spark_config.h"

#ifdef PLATFORM_NULL

#if defined(_WIN32)
//#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>
//#include <Mmsystem.h>
#elif defined(__APPLE__)
#include <CoreServices/CoreServices.h>
#elif defined(__linux__)
#include <sys/sysinfo.h>
#include <sys/time.h>
#endif
#include <time.h>
#include "../lib/tinyfiledialogs/tinyfiledialogs.h"
#include "platform.h"
#include <stdio.h>

bool_t p_Init() {
  return TRUE;
}

void p_Shutdown() {}

float p_GetTime() {
#if defined(_WIN32)
  return timeGetTime() / 1000.0f;
#elif defined(__linux__)
  static long basetime = -1;
  long t;
  struct timeval tv;
  gettimeofday(&tv, 0);
  t = tv.tv_sec * 1000;
  t += tv.tv_usec / 1000;
  if ( basetime == -1 )
  {
  struct sysinfo info;
  sysinfo(&info);
  basetime = t - info.uptime * 1000;
  }
  return (t - basetime) / 1000.0f;
#elif defined(__APPLE__)
  double t;
  UnsignedWide uw;
  Microseconds(&uw);
  t=(uw.hi<<(32-9))|(uw.lo>>9);
  return t/(1000.0/512.0) / 1000.0f;
#endif
}

void p_SetCursorVisible(void* win, bool_t visible) {}

void p_SetCursorPosition(void* win, int x, int y) {}

int p_GetCursorX(void* win) {
  return 0;
}

int p_GetCursorY(void* win) {
  return 0;
}

bool_t p_GetCursorPressed(void* win, int button) {
  return FALSE;
}

bool_t p_GetKeyPressed(void* win, int key) {
  return FALSE;
}

int p_GetDesktopWidth() {
  return 0;
}

int p_GetDesktopHeight() {
  return 0;
}

void* p_OpenScreen(int width, int height, bool_t fullscreen, int samples, bool_t vsync, bool_t resizable) {
  return NULL;
}

void p_CloseScreen(void* win) {}

bool_t p_IsScreenOpened(void* win) {
  return FALSE;
}

void p_RefreshScreen(void* win) {}

void p_SetScreenTitle(void* win, const char* title) {}

int p_GetScreenWidth(void* win) {
  return 0;
}

int p_GetScreenHeight(void* win) {
  return 0;
}

void p_MessageBox(const char* title, const char* message) {
#ifdef USE_TINYFILEDIALOGS
  tinyfd_messageBox(title, message, "ok", "info", 0);
#else
  printf("[%s] %s\n", title, message);
#endif
}

#ifdef USE_AUDIO

bool_t p_PlayMusic(const char* filename, bool_t loop) {
  return FALSE;
}

void p_PauseMusic() {}

void p_ResumeMusic() {}

void p_StopMusic() {}

void p_SetMusicVolume(float volume) {}

bool_t p_IsMusicPlaying() {
  return FALSE;
}

void* p_LoadSound(const char* filename) {
  return NULL;
}

void p_DeleteSound(void* sound) {}

void* p_PlaySound(void* sound, bool_t loop) {
  return NULL;
}

void p_PauseChannel(void* channel) {}

void p_ResumeChannel(void* channel) {}

void p_StopChannel(void* channel) {}

void p_PositionChannel(void* channel, float lx, float ly, float lz, float lyaw, float sx, float sy, float sz, float radius) {}

void p_SetChannelVolume(void* channel, float volume) {}

void p_SetChannelPan(void* channel, float pan) {}

void p_SetChannelPitch(void* channel, float pitch) {}

bool_t p_IsChannelPlaying(void* channel) {
  return FALSE;
}

#endif /* USE_AUDIO */

#endif /* PLATFORM_NULL */
