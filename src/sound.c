#define STB_VORBIS_HEADER_ONLY
#include "../lib/stb/stb_vorbis.c"
#include "../lib/openal-soft/include/AL/alc.h"
#include "../lib/openal-soft/include/AL/al.h"
#include "sound.h"
#include "util.h"

struct channel_t
{
  
};

struct sound_t
{
  unsigned int buffer;
};

static ALCdevice* _device = NULL;
static ALCcontext* _context = NULL;
static struct channel_t* _music_channel = NULL;
static struct sound_t* _music_sound = NULL;

bool_t sound_playmusic(const char* filename, bool_t loop)
{

}

void sound_pausemusic()
{

}

void sound_resumemusic()
{

}

void sound_stopmusic()
{

}

bool_t sound_musicplaying()
{

}

struct sound_t* sound_load(const char* filename)
{
  char ext[STRING_SIZE];
  ext_extract(filename, ext, sizeof(ext));
  if (str_casecmp(ext, "ogg") == 0)
  {
    return _sound_load_ogg(filename);
  }
  else if (str_casecmp(ext, "wav") == 0)
  {
    return _sound_load_wav(filename);
  }
  else
  {
    return FALSE;
  }
}

void sound_free(struct sound_t* sound)
{
  alDeleteBuffers(1, &sound->buffer);
  free(sound);
}

struct channel_t* sound_play(const struct sound_t* sound, bool_t loop)
{

}

struct channel_t* sound_play3d(const struct sound_t* sound, bool_t loop)
{

}

void sound_pausechannel(const struct channel_t* channel)
{

}

void sound_resumechannel(const struct channel_t* channel)
{

}

void sound_stopchannel(const struct channel_t* channel)
{

}

bool_t sound_channelplaying(const struct channel_t* channel)
{

}

bool_t _sound_initaudio()
{
  if (!_device) _device = alcOpenDevice(NULL);
  if (!_context) _context = alcCreateContext(_device, NULL);
  if (_context) alcMakeContextCurrent(_context);
  return _device && _context;
}

void _sound_deinitaudio()
{
  if (_context) alcDestroyContext(_context);
  if (_device) alcCloseDevice(_device);
  _device = NULL;
  _context = NULL;
}

struct sound_t* _sound_load_ogg(const char* filename)
{
  struct sound_t* sound;
  stb_vorbis* file;
  stb_vorbis_info fileinfo;
  int length_samples;
  short* buffer;

  /* open file */
  file = stb_vorbis_open_filename((char*)filename, NULL, NULL);
  if (!file) return NULL;

  /* create sound */
  sound = _alloc(struct sound_t);

  /* load ogg */
  fileinfo = stb_vorbis_get_info(file);
  length_samples = stb_vorbis_stream_length_in_samples(file) * fileinfo.channels;
  buffer = _allocnum(short, length_samples);
  stb_vorbis_get_samples_short_interleaved(file, fileinfo.channels, buffer, length_samples);

  /* generate openal buffer */
  alGenBuffers(1, &sound->buffer);
  alBufferData(sound->buffer, fileinfo.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, buffer, length_samples * sizeof(short), fileinfo.sample_rate);

  free(buffer);
  stb_vorbis_close(file);

  return sound;
}

struct sound_t* _sound_load_wav(const char* filename)
{
  return NULL;
}
