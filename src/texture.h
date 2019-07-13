#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct memory_t;
struct pixmap_t;
struct texture_t;

EXPORT struct texture_t* CALL texture_new(int width, int height);
EXPORT struct texture_t* CALL texture_newfrommemory(const struct memory_t* memory);
EXPORT struct texture_t* CALL texture_newfrompixmap(const struct pixmap_t* pixmap);
EXPORT struct texture_t* CALL texture_load(const char* filename);
#ifndef SWIG
void texture_retain(struct texture_t* texture);
void texture_release(struct texture_t* texture);
#endif
EXPORT void CALL texture_delete(struct texture_t* texture);
EXPORT int CALL texture_width(const struct texture_t* texture);
EXPORT int CALL texture_height(const struct texture_t* texture);
EXPORT void CALL texture_setpixels(struct texture_t* texture, const struct pixmap_t* pixmap);
EXPORT void CALL texture_setfilter(bool_t filter);

#ifndef SWIG
const void* _texture_ptr(const struct texture_t* texture);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TEXTURE_H_INCLUDED */
