#include "beam_config.h"

#ifdef PLATFORM_SDL2

#include "../lib/litelibs/litemath3d.h"
#include "../lib/sdl2/include/SDL.h"
#include "platform.h"
#include "util.h"
#include <math.h>

typedef struct {
    SDL_Window* window;
    SDL_GLContext context;
    bool_t close_pressed;
} data_t;

#ifdef USE_AUDIO

typedef struct {
    int allocated;
    Uint8 *abuf;
    Uint32 alen;
    Uint8 volume; /* Per-sample volume, 0-128 */
} Chunk;

typedef enum {
        NO_FADING,
        FADING_OUT,
        FADING_IN
} FadingType;

typedef struct {
    Chunk* chunk;
    int playing;
    int paused;
    Uint8* samples;
    int volume;
    int looping;
    int tag;
    Uint32 expire;
    Uint32 start_time;
    FadingType fading;
    int fade_volume;
    int fade_volume_reset;
    Uint32 fade_length;
    Uint32 ticks_fade;
    effect_info* effects;
} Channel;

static Channel _channels[NUM_CHANNELS];
static SDL_AudioSpec _mixer;
static SDL_AudioDeviceID _audio_device;
static Mix_Music* _loaded_music = NULL;

static void SDLCALL _MixChannels(void *udata, Uint8 *stream, int len);

#endif

bool_t p_Init() {
    Uint32 flags;
    bool_t sdl_init;
    int i;

    flags = SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO;
#ifdef USE_AUDIO
    flags |= SDL_INIT_AUDIO;
#endif

    /*SDL_SetMainReady();*/
    sdl_init = SDL_Init(flags) == 0;
#ifdef USE_AUDIO
    if (sdl_init) {
        SDL_AudioSpec desired;

        //Mix_Init(MIX_INIT_OGG);

        /* Initialize audio device */
        desired.freq = 22050;
        desired.format = AUDIO_S16LSB;
        desired.channels = 2;
        desired.samples = 4096;
        desired.callback = _MixChannels;
        desired.userdata = NULL;
        if ((_audio_device = SDL_OpenAudioDevice(NULL, 0, &desired, &_mixer,
                SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE)) == 0) {
            return FALSE;
        }

        /* Initialize channels */
        for (i = 0; i < NUM_CHANNELS; ++i) {
            _channels[i].chunk = NULL;
            _channels[i].playing = FALSE;
            _channels[i].looping = FALSE;
            _channels[i].volume = SDL_MIX_MAXVOLUME;
            _channels[i].fade_volume = SDL_MIX_MAXVOLUME;
            _channels[i].fade_volume_reset = SDL_MIX_MAXVOLUME;
            _channels[i].fading = NO_FADING;
            _channels[i].tag = -1;
            _channels[i].expire = 0;
            _channels[i].effects = NULL;
            _channels[i].paused = FALSE;
        }

        
        //Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    }
#endif

    return sdl_init;
}

void p_Shutdown()
{
#ifdef USE_AUDIO
    Mix_Quit();
#endif
    SDL_Quit();
}

float p_GetTime() {
    return SDL_GetTicks() / 1000.0f;
}

void p_SetCursorVisible(void* win, bool_t visible) {
    SDL_ShowCursor(visible);
}

void p_SetCursorPosition(void* win, int x, int y) {
    SDL_WarpMouseInWindow(((data_t*)win)->window, x, y);
}

int p_GetCursorX(void* win) {
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}

int p_GetCursorY(void* win) {
    int y;
    SDL_GetMouseState(NULL, &y);
    return y;
}

bool_t p_GetCursorPressed(void* win, int button) {
    if (button == 0) return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
    else if (button == 1) return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);
    else if (button == 2) return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
    else return 0;
}

bool_t p_GetKeyPressed(void* win, int key) {
    return (bool_t)SDL_GetKeyboardState(NULL)[SDL_GetScancodeFromKey(key)];
}

int p_GetDesktopWidth() {
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(0, &mode);
    return mode.w;
}

int p_GetDesktopHeight() {
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(0, &mode);
    return mode.h;
}

void* p_OpenScreen(int width, int height, bool_t fullscreen, int samples, bool_t vsync, bool_t resizable) {
    Uint32 flags;
    data_t* win;

    /* gl attributes */
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, (samples > 0) ? 1 : 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, samples);

    /* flags */
    flags = SDL_WINDOW_OPENGL;
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    if (resizable) flags |= SDL_WINDOW_RESIZABLE;

    /* create window object */
    win = _Alloc(data_t);
    win->close_pressed = FALSE;
    win->window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    win->context = SDL_GL_CreateContext(win->window);
    SDL_GL_MakeCurrent(win->window, win->context);

    /* set vsync */
    SDL_GL_SetSwapInterval(vsync);

    return win;
}

void p_CloseScreen(void* win) {
    data_t* pwin;
    pwin = (data_t*)win;
    SDL_GL_DeleteContext(pwin->context);
    SDL_DestroyWindow(pwin->window);
    free(pwin);
}

bool_t p_IsScreenOpened(void* win) {
    return win && !((data_t*)win)->close_pressed;
}

void p_RefreshScreen(void* win) {
    data_t* pwin;
    SDL_Event event;

    pwin = (data_t*)win;

    /* poll events */
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) pwin->close_pressed = TRUE;
                break;
            case SDL_QUIT:
                break;
        }
    }

    /* refresh screen */
    SDL_GL_SwapWindow(pwin->window);
}

void p_SetScreenTitle(void* win, const char* title) {
    SDL_SetWindowTitle(((data_t*)win)->window, title);
}

int p_GetScreenWidth(void* win) {
    int w;
    SDL_GetWindowSize(((data_t*)win)->window, &w, NULL);
    return w;
}

int p_GetScreenHeight(void* win) {
    int h;
    SDL_GetWindowSize(((data_t*)win)->window, NULL, &h);
    return h;
}

void p_MessageBox(const char* title, const char* message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
}

#ifdef USE_AUDIO

bool_t p_PlayMusic(const char* filename, bool_t loop) {
    if (_loaded_music) Mix_FreeMusic(_loaded_music);
    _loaded_music = Mix_LoadMUS(filename);
    if (_loaded_music) {
        Mix_PlayMusic(_loaded_music, loop ? -1 : 1);
    }
    return _loaded_music != NULL;
}

void p_PauseMusic() {
    Mix_PauseMusic();
}

void p_ResumeMusic() {
    Mix_ResumeMusic();
}

void p_StopMusic() {
    Mix_HaltMusic();
    if (_loaded_music) Mix_FreeMusic(_loaded_music);
    _loaded_music = NULL;
}

void p_SetMusicVolume(float volume) {
    Mix_VolumeMusic((int)(volume*128));
}

bool_t p_IsMusicPlaying() {
    return Mix_PlayingMusic();
}

void* p_LoadSound(const char* filename) {
    return Mix_LoadWAV(filename);
}

void p_DeleteSound(void* sound) {
    Mix_FreeChunk((Chunk*)sound);
}

void* p_PlaySound(void* sound, bool_t loop) {
    unsigned int* channel = _Alloc(unsigned int);
    *channel = Mix_PlayChannel(-1, (Chunk*)sound, loop ? -1 : 0);
    return channel;
}

void p_PauseChannel(void* channel) {
    Mix_Pause(*(unsigned int*)channel);
}

void p_ResumeChannel(void* channel) {
    Mix_Resume(*(unsigned int*)channel);
}

void p_StopChannel(void* channel) {
    Mix_HaltChannel(*(unsigned int*)channel);
    free(channel);
}

void p_PositionChannel(void* channel, float lx, float ly, float lz, float lyaw, float sx, float sy, float sz, float radius) {
    float distx, disty, distz;
    float angle;
    float dist;

    distx = lx - sx;
    disty = ly - sy;
    distz = lz - sz;
    angle = Wrap(-lm_rad2deg(atan2(distz, distx)) - 90 - lyaw, 360);
    dist = (float)sqrt(distx*distx + disty*disty + distz*distz);
    dist = dist * 255 / radius;    // Wrap in 0 .. 255
    if (dist > 255) dist = 255;
    Mix_SetPosition(*(unsigned int*)channel, (Sint16)angle, (Uint8)dist);
}

void p_SetChannelVolume(void* channel, float volume) {
    Mix_Volume(*(unsigned int*)channel, (int)(volume*128));
}

void p_SetChannelPan(void* channel, float pan) {
    Uint8 left = 255, right = 255;
    if (pan < 0) {
        right = 255 - (Uint8)(pan * -255);
    } else if (pan > 0) {
        left = 255 - (Uint8)(pan * 255);
    }
    Mix_SetPanning(*(unsigned int*)channel, left, right);
}

void p_SetChannelPitch(void* channel, float pitch) {}

bool_t p_IsChannelPlaying(void* channel) {
    return Mix_Playing(*(unsigned int*)channel);
}

static void SDLCALL _MixChannels(void *udata, Uint8 *stream, int len) {
    Uint8 *mix_input;
    int i, mixable, volume = MIX_MAX_VOLUME;
    Uint32 sdl_ticks;

#if SDL_VERSION_ATLEAST(1, 3, 0)
    /* Need to initialize the stream in SDL 1.3+ */
    SDL_memset(stream, mixer.silence, len);
#endif

    /* Mix the music (must be done before the channels are added) */
    mix_music(music_data, stream, len);

    /* Mix any playing channels... */
    sdl_ticks = SDL_GetTicks();
    for (i=0; i<num_channels; ++i) {
        if (!mix_channel[i].paused) {
            if (mix_channel[i].expire > 0 && mix_channel[i].expire < sdl_ticks) {
                /* Expiration delay for that channel is reached */
                mix_channel[i].playing = 0;
                mix_channel[i].looping = 0;
                mix_channel[i].fading = MIX_NO_FADING;
                mix_channel[i].expire = 0;
                _Mix_channel_done_playing(i);
            } else if (mix_channel[i].fading != MIX_NO_FADING) {
                Uint32 ticks = sdl_ticks - mix_channel[i].ticks_fade;
                if (ticks >= mix_channel[i].fade_length) {
                    Mix_Volume(i, mix_channel[i].fade_volume_reset); /* Restore the volume */
                    if(mix_channel[i].fading == MIX_FADING_OUT) {
                        mix_channel[i].playing = 0;
                        mix_channel[i].looping = 0;
                        mix_channel[i].expire = 0;
                        _Mix_channel_done_playing(i);
                    }
                    mix_channel[i].fading = MIX_NO_FADING;
                } else {
                    if (mix_channel[i].fading == MIX_FADING_OUT) {
                        Mix_Volume(i, (mix_channel[i].fade_volume * (mix_channel[i].fade_length-ticks))
                                     / mix_channel[i].fade_length);
                    } else {
                        Mix_Volume(i, (mix_channel[i].fade_volume * ticks) / mix_channel[i].fade_length);
                    }
                }
            }
            if (mix_channel[i].playing > 0) {
                int index = 0;
                int remaining = len;
                while (mix_channel[i].playing > 0 && index < len) {
                    remaining = len - index;
                    volume = (mix_channel[i].volume*mix_channel[i].chunk->volume) / MIX_MAX_VOLUME;
                    mixable = mix_channel[i].playing;
                    if (mixable > remaining) {
                        mixable = remaining;
                    }

                    mix_input = Mix_DoEffects(i, mix_channel[i].samples, mixable);
                    SDL_MixAudioFormat(stream+index,mix_input,mixer.format,mixable,volume);
                    if (mix_input != mix_channel[i].samples)
                        SDL_free(mix_input);

                    mix_channel[i].samples += mixable;
                    mix_channel[i].playing -= mixable;
                    index += mixable;

                    /* rcg06072001 Alert app if channel is done playing. */
                    if (!mix_channel[i].playing && !mix_channel[i].looping) {
                        _Mix_channel_done_playing(i);
                    }
                }

                /* If looping the sample and we are at its end, make sure
                     we will still return a full buffer */
                while (mix_channel[i].looping && index < len) {
                    int alen = mix_channel[i].chunk->alen;
                    remaining = len - index;
                    if (remaining > alen) {
                        remaining = alen;
                    }

                    mix_input = Mix_DoEffects(i, mix_channel[i].chunk->abuf, remaining);
                    SDL_MixAudioFormat(stream+index, mix_input, mixer.format, remaining, volume);
                    if (mix_input != mix_channel[i].chunk->abuf)
                        SDL_free(mix_input);

                    if (mix_channel[i].looping > 0) {
                        --mix_channel[i].looping;
                    }
                    mix_channel[i].samples = mix_channel[i].chunk->abuf + remaining;
                    mix_channel[i].playing = mix_channel[i].chunk->alen - remaining;
                    index += remaining;
                }
                if (! mix_channel[i].playing && mix_channel[i].looping) {
                    if (mix_channel[i].looping > 0) {
                        --mix_channel[i].looping;
                    }
                    mix_channel[i].samples = mix_channel[i].chunk->abuf;
                    mix_channel[i].playing = mix_channel[i].chunk->alen;
                }
            }
        }
    }

    /* rcg06122001 run posteffects... */
    Mix_DoEffects(MIX_CHANNEL_POST, stream, len);

    if (mix_postmix) {
        mix_postmix(mix_postmix_data, stream, len);
    }
}

#endif /* USE_AUDIO */

#endif /* PLATFORM_SDL2 */
