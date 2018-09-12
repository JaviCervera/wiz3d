#ifndef PIXMAP_H_INCLUDED
#define PIXMAP_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct pixmap_t;

struct pixmap_t* pixmap_new(int width, int height);
struct pixmap_t* pixmap_load(const char* filename);
void pixmap_delete(struct pixmap_t* pixmap);
int pixmap_width(struct pixmap_t* pixmap);
int pixmap_height(struct pixmap_t* pixmap);
int pixmap_color(struct pixmap_t* pixmap, int x, int y);
void pixmap_setcolor(struct pixmap_t* pixmap, int x, int y, int color);

#ifndef SWIG
void* _pixmap_ptr(struct pixmap_t* pixmap);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PIXMAP_H_INCLUDED */
