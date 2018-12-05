#ifndef COLBOX_H_INCLUDED
#define COLBOX_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

void colbox_add(float minx, float miny, float minz, float maxx, float maxy, float maxz);
void colbox_clear();

#ifndef SWIG
bool_t _colbox_checkbox(float minx, float miny, float minz, float maxx, float maxy, float maxz);
bool_t _colbox_checksphere(float x, float y, float z, float sq_radius);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COLBOX_H_INCLUDED */