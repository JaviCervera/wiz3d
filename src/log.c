#include "log.h"
#include "platform.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

static bool_t _log_init                  = FALSE;
static char _log_filename[STRING_SIZE] = "";

static void _InitLog();

EXPORT void CALL bmLogInfo(const char* msg) {
  _InitLog();
  printf("[INFO] %s\n", msg);
  if (strcmp(_log_filename, "") != 0) WriteString("[INFO] ", _log_filename, TRUE);
  if (strcmp(_log_filename, "") != 0) WriteString(msg, _log_filename, TRUE);
  if (strcmp(_log_filename, "") != 0) WriteString("\r\n", _log_filename, TRUE);
}

EXPORT void CALL bmLogWarning(const char* msg) {
  _InitLog();
  printf("[WARNING] %s\n", msg);
  if (strcmp(_log_filename, "") != 0) WriteString("[WARNING] ", _log_filename, TRUE);
  if (strcmp(_log_filename, "") != 0) WriteString(msg, _log_filename, TRUE);
  if (strcmp(_log_filename, "") != 0) WriteString("\r\n", _log_filename, TRUE);
}

EXPORT void CALL bmLogError(const char* msg) {
  _InitLog();
  printf("[ERROR] %s\n", msg);
  if (strcmp(_log_filename, "") != 0) WriteString("[ERROR] ", _log_filename, TRUE);
  if (strcmp(_log_filename, "") != 0) WriteString(msg, _log_filename, TRUE);
  if (strcmp(_log_filename, "") != 0) WriteString("\r\n", _log_filename, TRUE);
  p_MessageBox("ERROR", msg);
  exit(-1);
}

void _SetLogFilename(const char* filename) {
  strncpy(_log_filename, filename, STRING_SIZE);
}

static void _InitLog() {
  if (!_log_init) {
    if (strcmp(_log_filename, "") != 0) WriteString("", _log_filename, FALSE);
    _log_init = TRUE;
  }
}
