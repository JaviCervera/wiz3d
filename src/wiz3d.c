#include "wiz3d_config.h"
#include "wiz3d.h"
#include "draw.h"
#include "platform.h"
#define LITE_ASSBIN_USE_GFX
#define LITE_MD2_USE_GFX
#define LITE_ASSBIN_IMPLEMENTATION
#include "../lib/litelibs/liteassbin.h"
#undef LITE_ASSBIN_IMPLEMENTATION
#define LITE_COL_IMPLEMENTATION
#include "../lib/litelibs/litecol.h"
#undef LITE_COL_IMPLEMENTATION
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
#include "../lib/stb/stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include "../lib/stb/stb_truetype.h"
#undef STB_TRUETYPE_IMPLEMENTATION
#ifdef USE_AUDIO
#include "../lib/stb/stb_vorbis.c"
#endif


EXPORT bool_t CALL wzInitWiz3D() {
    bool_t ret;
    ret = p_Init();
    if (!ret) return FALSE;
#ifdef PLATFORM_NULL
    lgfx_init();
    wzSetDefaultFont();
#endif
    return ret != FALSE;
}

EXPORT void CALL wzShutdownWiz3D() {
#ifndef PLATFORM_NULL
    if (_GetScreenPtr()) p_CloseScreen(_GetScreenPtr());
#endif
    p_Shutdown();
}

EXPORT bool_t CALL wzIsMultitexturingSupported() {
    return lgfx_multitexture_supported();
}

EXPORT bool_t CALL wzIsMipmappingSupported() {
    return lgfx_mipmapping_supported();
}
