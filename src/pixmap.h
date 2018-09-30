#ifndef PIXMAP_H_INCLUDED
#define PIXMAP_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct memory_t;
struct pixmap_t;

struct pixmap_t* pixmap_new(int width, int height);
struct pixmap_t* pixmap_newfrommemory(const struct memory_t* memory);
struct pixmap_t* pixmap_load(const char* filename);
void pixmap_delete(struct pixmap_t* pixmap);
int pixmap_width(const struct pixmap_t* pixmap);
int pixmap_height(const struct pixmap_t* pixmap);
int pixmap_color(const struct pixmap_t* pixmap, int x, int y);
void pixmap_setcolor(struct pixmap_t* pixmap, int x, int y, int color);

#ifndef SWIG
struct pixmap_t* _pixmap_newfromdata(const unsigned char* data, size_t len);
const void* _pixmap_ptr(const struct pixmap_t* pixmap);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PIXMAP_H_INCLUDED */
