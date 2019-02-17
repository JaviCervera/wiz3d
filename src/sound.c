#include "../lib/allegro/addons/audio/allegro5/allegro_audio.h"
#define STB_VORBIS_HEADER_ONLY
#include "../lib/stb/stb_vorbis.c"
#include "sound.h"
#include "util.h"

bool al_init_acodec_addon(void);
ALLEGRO_SAMPLE* _sound_load_ogg(const char* filename);
//ALLEGRO_SAMPLE* _sound_load_wav(const char* filename);

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
  return (struct sound_t*)al_load_sample(filename);
}

void sound_free(struct sound_t* sound)
{
  al_destroy_sample((ALLEGRO_SAMPLE*)sound);
}

struct channel_t* sound_play(const struct sound_t* sound, bool_t loop)
{
  ALLEGRO_SAMPLE_INSTANCE* inst;
  inst = al_create_sample_instance((ALLEGRO_SAMPLE*)sound);
  if (loop) al_set_sample_instance_playmode(inst, ALLEGRO_PLAYMODE_LOOP);
  al_play_sample_instance(inst);
  return (struct channel_t*)inst;
}

/*
struct channel_t* sound_play3d(const struct sound_t* sound, bool_t loop)
{
  return NULL;
}
*/

void sound_pausechannel(const struct channel_t* channel)
{
  al_set_sample_instance_playing((ALLEGRO_SAMPLE_INSTANCE*)channel, FALSE);
}

void sound_resumechannel(const struct channel_t* channel)
{
  al_set_sample_instance_playing((ALLEGRO_SAMPLE_INSTANCE*)channel, TRUE);
}

void sound_stopchannel(const struct channel_t* channel)
{
  al_stop_sample_instance((ALLEGRO_SAMPLE_INSTANCE*)channel);
}

bool_t sound_channelplaying(const struct channel_t* channel)
{
  return al_get_sample_instance_playing((ALLEGRO_SAMPLE_INSTANCE*)channel);
}

bool_t _sound_initaudio()
{
  bool_t ret;
  ret = al_init_acodec_addon();
  if (!ret) return FALSE;
  ret = al_register_sample_loader(".ogg", _sound_load_ogg);
  if (!ret) return FALSE;
  //ret = al_register_sample_loader(".wav", _sound_load_wav);
  //if (!ret) return FALSE;
  return ret != FALSE;
}

void _sound_deinitaudio()
{
}

ALLEGRO_SAMPLE* _sound_load_ogg(const char* filename)
{
  ALLEGRO_SAMPLE *sample;
  stb_vorbis* file;
  stb_vorbis_info fileinfo;
  int length_samples;
  short* buffer;

  /* open file */
  file = stb_vorbis_open_filename((char*)filename, NULL, NULL);
  if (!file) return NULL;

  /* load ogg */
  fileinfo = stb_vorbis_get_info(file);
  length_samples = stb_vorbis_stream_length_in_samples(file) * fileinfo.channels;
  buffer = al_malloc(sizeof(short) * length_samples);
  stb_vorbis_get_samples_short_interleaved(file, fileinfo.channels, buffer, length_samples);

  /* close file */
  stb_vorbis_close(file);

  /* create allegro sample */
  sample = al_create_sample(
    buffer,
    length_samples,
    fileinfo.sample_rate,
    ALLEGRO_AUDIO_DEPTH_INT16,
    fileinfo.channels == 1 ? ALLEGRO_CHANNEL_CONF_1 : ALLEGRO_CHANNEL_CONF_2,
    TRUE);
  if (!sample) al_free(buffer);

  return sample;
}

/*
ALLEGRO_SAMPLE* _sound_load_wav(const char* filename)
{
  return NULL;
}
*/
