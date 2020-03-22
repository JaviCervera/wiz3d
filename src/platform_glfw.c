#include "beam_config.h"

#ifdef PLATFORM_GLFW

#include "../lib/glfw3/include/GLFW/glfw3.h"
#include "../lib/tinyfiledialogs/tinyfiledialogs.h"
#include "platform.h"
#include "util.h"
#ifdef USE_AUDIO
#if defined(__APPLE__)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif
#define STB_VORBIS_HEADER_ONLY
#include "../lib/stb/stb_vorbis.c"
#endif /* USE_AUDIO */
#include <math.h>
#include <stdio.h>

#ifdef USE_AUDIO
static ALCdevice* _audio_device = NULL;
static ALCcontext* _audio_context = NULL;
#endif

bool_t p_Init() {
    bool_t ret;
    ret = glfwInit();

#ifdef USE_AUDIO
    _audio_device = alcOpenDevice(NULL);
    if (_audio_device) _audio_context = alcCreateContext(_audio_device, NULL);
    if (_audio_context) alcMakeContextCurrent(_audio_context);
#endif

    return ret;
}

void p_Shutdown() {
    glfwTerminate();
#ifdef USE_AUDIO
    if (_audio_context) alcDestroyContext(_audio_context);
    if (_audio_device) alcCloseDevice(_audio_device);
    _audio_device = NULL;
    _audio_context = NULL;
#endif
}

float p_GetTime() {
    return (float)glfwGetTime();
}

void p_SetCursorVisible(void* win, bool_t visible) {
    glfwSetInputMode((GLFWwindow*)win, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void p_SetCursorPosition(void* win, int x, int y) {
    glfwSetCursorPos((GLFWwindow*)win, x, y);
}

int p_GetCursorX(void* win) {
    double x;
    glfwGetCursorPos((GLFWwindow*)win, &x, NULL);
    return (int)floor(x);
}

int p_GetCursorY(void* win) {
    double y;
    glfwGetCursorPos((GLFWwindow*)win, NULL, &y);
    return (int)floor(y);
}

bool_t p_GetCursorPressed(void* win, int button) {
    return glfwGetMouseButton((GLFWwindow*)win, button) == GLFW_PRESS;
}

bool_t p_GetKeyPressed(void* win, int key) {
    return glfwGetKey((GLFWwindow*)win, key) == GLFW_PRESS;
}

int p_GetDesktopWidth() {
    return glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
}

int p_GetDesktopHeight() {
    return glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
}

void* p_OpenScreen(int width, int height, bool_t fullscreen, int samples, bool_t vsync, bool_t resizable) {
    GLFWwindow* win;

    /* set flags */
    glfwWindowHint(GLFW_SAMPLES, samples);
    glfwWindowHint(GLFW_RESIZABLE, resizable);
#ifdef USE_RETINA
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#else
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif

    /* create window */
    win = glfwCreateWindow(width, height, "", fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    glfwMakeContextCurrent(win);

    /* set vsync */
    glfwSwapInterval(vsync ? 1 : 0);

    return win;
}

void p_CloseScreen(void* win) {
    glfwDestroyWindow((GLFWwindow*)win);
}

bool_t p_IsScreenOpened(void* win) {
    return win && !glfwWindowShouldClose((GLFWwindow*)win);
}

void p_RefreshScreen(void* win) {
    glfwSwapBuffers((GLFWwindow*)win);
    glfwPollEvents();
}

void p_SetScreenTitle(void* win, const char* title) {
    glfwSetWindowTitle((GLFWwindow*)win, title);
}

int p_GetScreenWidth(void* win) {
    int w;
#ifdef USE_RETINA
    glfwGetFramebufferSize((GLFWwindow*)win, &w, NULL);
#else
    glfwGetWindowSize((GLFWwindow*)win, &w, NULL);
#endif
    return w;
}

int p_GetScreenHeight(void* win) {
    int h;
#ifdef USE_RETINA
    glfwGetFramebufferSize((GLFWwindow*)win, NULL, &h);
#else
    glfwGetWindowSize((GLFWwindow*)win, NULL, &h);
#endif
    return h;
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

#endif /* PLATFORM_GLFW */
