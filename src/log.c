#include "log.h"
#include "platform.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

static bool_t _log_init                  = FALSE;
static char _log_filename[STRING_SIZE] = "";

static void _log_initialize()
{
  if ( !_log_init )
  {
    if ( strcmp(_log_filename, "") != 0 ) string_write("", _log_filename, FALSE);
    _log_init = TRUE;
  }
}

void log_info(const char* msg)
{
  _log_initialize();
  printf("[INFO] %s\n", msg);
  if ( strcmp(_log_filename, "") != 0 ) string_write("[INFO] ", _log_filename, TRUE);
  if ( strcmp(_log_filename, "") != 0 ) string_write(msg, _log_filename, TRUE);
  if ( strcmp(_log_filename, "") != 0 ) string_write("\r\n", _log_filename, TRUE);
}

void log_warning(const char* msg)
{
  _log_initialize();
  printf("[WARNING] %s\n", msg);
  if ( strcmp(_log_filename, "") != 0 ) string_write("[WARNING] ", _log_filename, TRUE);
  if ( strcmp(_log_filename, "") != 0 ) string_write(msg, _log_filename, TRUE);
  if ( strcmp(_log_filename, "") != 0 ) string_write("\r\n", _log_filename, TRUE);
}

void log_error(const char* msg)
{
  _log_initialize();
  printf("[ERROR] %s\n", msg);
  if ( strcmp(_log_filename, "") != 0 ) string_write("[ERROR] ", _log_filename, TRUE);
  if ( strcmp(_log_filename, "") != 0 ) string_write(msg, _log_filename, TRUE);
  if ( strcmp(_log_filename, "") != 0 ) string_write("\r\n", _log_filename, TRUE);
  p_messagebox("ERROR", msg);
  exit(-1);
}

void _log_setfilename(const char* filename)
{
  strncpy(_log_filename, filename, STRING_SIZE);
}
