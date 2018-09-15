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

struct texture_t* texture_new(int width, int height);
struct texture_t* texture_newfrommemory(struct memory_t* memory);
struct texture_t* texture_newfrompixmap(struct pixmap_t* pixmap);
struct texture_t* texture_load(const char* filename);
#ifndef SWIG
void texture_retain(struct texture_t* texture);
void texture_release(struct texture_t* texture);
#endif
void texture_delete(struct texture_t* texture);
int texture_width(struct texture_t* texture);
int texture_height(struct texture_t* texture);
void texture_setpixels(struct texture_t* texture, struct pixmap_t* pixmap);
void texture_setfilter(bool_t filter);

#ifndef SWIG
void* _texture_ptr(struct texture_t* texture);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TEXTURE_H_INCLUDED */
