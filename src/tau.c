#include "color.h"
#include "light.h"
#include "platform.h"
#include "screen.h"
#include "tau.h"
#define LITE_MD2_USE_GFX
#define LITE_GFX_IMPLEMENTATION
#include "../lib/litelibs/litegfx.h"
#undef LITE_GFX_IMPLEMENTATION
#define LITE_MATH3D_IMPLEMENTATION
#include "../lib/litelibs/litemath3d.h"
#undef LITE_MATH3D_IMPLEMENTATION
#define LITE_MD2_IMPLEMENTATION
#include "../lib/litelibs/litemd2.h"
#undef LITE_MD2_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include "../lib/stb_truetype.h"
#undef STB_TRUETYPE_IMPLEMENTATION

#ifdef __cplusplus
extern "C"
{
#endif

bool_t tau_init()
{
  if ( p_init() )
  {
    _physics_init();
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

void tau_finish()
{
  if ( _screen_pointer() ) p_close_screen(_screen_pointer());
  _physics_finish();
  p_shutdown();
}

#ifdef __cplusplus
} /* extern "C" */
#endif
