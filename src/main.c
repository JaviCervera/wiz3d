#include "script.h"
#include "micron.h"
#include "util.h"
#include <string.h>

#define sizearr(A) (sizeof(A) / sizeof(A[0]))

int main(int argc, char* argv[])
{
  char working_dir[256];
  char script_file[256];

  /* get program path */
  dir_extract(argv[0], working_dir, sizearr(working_dir));

  /* get script filename */
  strncpy(script_file, argc > 1 ? argv[1] : "data/main.lua", sizearr(script_file));
  script_file[sizearr(script_file) - 1] = 0;

  /*  if argv[0] begins with / on macOS, we'll assume it has been launched
      by double clicking on the Finder, and we'll move to the app dir */
#ifdef __APPLE__
  if (argv[0][0] == '/') dir_change(working_dir);
#endif

  /* get working dir */
  dir_extract(script_file, working_dir, sizearr(working_dir));

  /* change to working directory */
  dir_change(working_dir);
  dir_current(working_dir, sizearr(working_dir));

  /* strip dir from script */
  dir_strip(script_file, script_file, sizearr(script_file));

  /* setup */
  micron_init();
  screen_set(640, 480, FALSE, FALSE);
  light_setambient(_COLOR_DARKGRAY);

  /* run script */
  if (!script_init()) log_error(script_error());
  if (!script_load(script_file)) log_error(script_error());

  /* shutdown */
  script_finish();
  micron_finish();

  return 0;
}
