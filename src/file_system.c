#include "../lib/stb/stretchy_buffer.h"
#include "micron_config.h"
#include "file_system.h"
#include <stdio.h>
#include <string.h>

#define PAK_NAME_SIZE 56
#define PAK_ENTRY_SIZE 64

typedef struct
{
  char filename[PAK_NAME_SIZE];
  int offset;
  int size;
} pakentry_t;

typedef struct
{
  char filename[STRING_SIZE];
  pakentry_t* entries;
} pakfile_t;

static pakfile_t* _pak_files = NULL;

bool_t _fs_initpak(pakfile_t* pak, const char* pakname);
const pakfile_t* _fs_pakforfile(const char* filename);
const pakentry_t* _fs_pakentry(const pakfile_t* pak, const char* entryname);
size_t _fs_pakentrysize(const pakfile_t* pak, const char* entryname);
bool_t _fs_pakentrycontents(const pakfile_t* pak, const char* entryname, void* buffer);

bool_t fs_addpak(const char* pakname)
{
#ifdef USE_PAK
  pakfile_t pak;
  int i;

  /* search for pak in list */
  for (i = 0; i < sb_count(_pak_files); ++i)
  {
    if (strcmp(_pak_files[i].filename, pakname) == 0)
    {
      return TRUE;
    }
  }

  /* try to initialize new pak */
  if (_fs_initpak(&pak, pakname))
  {
    sb_push(_pak_files, pak);
    return TRUE;
  }
  else
  {
    return FALSE;
  }
#else
  return FALSE;
#endif
}

bool_t fs_fileinpak(const char* filename)
{
#ifdef USE_PAK
  return _fs_pakforfile(filename) != NULL;
#else
  return FALSE;
#endif
}

size_t fs_filesize(const char* filename)
{
  const pakfile_t* pak;
  pak = _fs_pakforfile(filename);
  if (pak)
  {
    return _fs_pakentrysize(pak, filename);
  }
  else
  {
    FILE* fhandle;
    fhandle = fopen(filename, "rb");
    if (fhandle)
    {
      size_t size;
      fseek(fhandle, 0, SEEK_END);
      size = ftell(fhandle);
      fclose(fhandle);
      return size;
    }
    else
    {
      return 0;
    }
  }
}

bool_t fs_filecontents(const char* filename, void* buffer)
{
  const pakfile_t* pak;
  pak = _fs_pakforfile(filename);
  if (pak)
  {
    return _fs_pakentrycontents(pak, filename, buffer);
  }
  else
  {
    FILE* fhandle;
    fhandle = fopen(filename, "rb");
    if (fhandle)
    {
      size_t size;
      fseek(fhandle, 0, SEEK_END);
      size = ftell(fhandle);
      fseek(fhandle, 0, SEEK_SET);
      fread(buffer, size, 1, fhandle);
      fclose(fhandle);
      return size;
    }
    else
    {
      return 0;
    }
  }
}


/****************************
    pak files
 ****************************/


#ifdef USE_PAK

typedef struct
{
  char id[4];
  int offset;
  int size;
} pakheader_t;

bool_t _fs_initpak(pakfile_t* pak, const char* pakname)
{
  FILE* fhandle;
  fhandle = fopen(pakname, "rb");
  if (fhandle)
  {
    pakheader_t header;
    size_t num_entries;
    size_t i;

    /* read header */
    fread(&header, sizeof(pakheader_t), 1, fhandle);
    if (strncmp(header.id, "PACK", 4) != 0)
    {
      fclose(fhandle);
      return FALSE;
    }

    /* set filename */
    strncpy(pak->filename, pakname, STRING_SIZE);
    pak->filename[STRING_SIZE-1] = 0;

    /* get number of entries */
    num_entries = header.size / PAK_ENTRY_SIZE;

    /* read all entries */
    pak->entries = NULL;
    for (i = 0; i < num_entries; ++i)
    {
      pakentry_t entry;
      fread(&entry, sizeof(pakentry_t), 1, fhandle);
      sb_push(pak->entries, entry);
    }

    fclose(fhandle);
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

const pakfile_t* _fs_pakforfile(const char* filename)
{
  int i;

  for (i = sb_count(_pak_files) - 1; i >= 0; --i)
  {
    if (_fs_pakentry(&_pak_files[i], filename) != NULL)
    {
      return &_pak_files[i];
    }
  }

  return NULL;
}

const pakentry_t* _fs_pakentry(const pakfile_t* pak, const char* entryname)
{
  int i;

  for (i = 0; i < sb_count(pak->entries); ++i)
  {
    if (strcmp(pak->entries[i].filename, entryname) == 0)
    {
      return &(pak->entries[i]);
    }
  }
  return NULL;
}

size_t _fs_pakentrysize(const pakfile_t* pak, const char* entryname)
{
  const pakentry_t* entry;
  entry = _fs_pakentry(pak, entryname);
  if (entry)
  {
    return (size_t)entry->size;
  }
  else
  {
    return 0;
  }
}

bool_t _fs_pakentrycontents(const pakfile_t* pak, const char* entryname, void* buffer)
{
  const pakentry_t* entry;
  entry = _fs_pakentry(pak, entryname);
  if (entry)
  {
    FILE* fhandle;
    fhandle = fopen(pak->filename, "rb");
    if (fhandle)
    {
      fseek(fhandle, entry->offset, SEEK_SET);
      fread(buffer, entry->size, 1, fhandle);
      fclose(fhandle);
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }
}

#endif /* USE_PAK */
