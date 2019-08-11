#ifndef COLBOX_H_INCLUDED
#define COLBOX_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL AddColbox(float minx, float miny, float minz, float maxx, float maxy, float maxz);
EXPORT void CALL ClearColboxes();

#ifndef SWIG
bool_t _CheckBoxCol(float minx, float miny, float minz, float maxx, float maxy, float maxz);
bool_t _CheckSphereCol(float x, float y, float z, float sq_radius);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COLBOX_H_INCLUDED */
