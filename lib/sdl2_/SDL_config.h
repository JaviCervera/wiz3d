#ifdef _WIN32
#include "SDL_config_win32.h"
#elif defined(__linux__)
#include "SDL_config_linux.h"
#elif defined(__APPLE__)
#include "SDL_config_macos.h"
#else
#error "Please add an appropriate SDL config file for this platform"
#endif

