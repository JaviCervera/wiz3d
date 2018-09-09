#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "types.h"

#define _BLEND_SOLID  0
#define _BLEND_ALPHA  1
#define _BLEND_ADD    2
#define _BLEND_MUL    3

#define _FLAG_CULL        1
#define _FLAG_DEPTHWRITE  2
#define _FLAG_LIGHTING    4
#define _FLAG_FOG         8
#define _FLAG_ALL         15

#ifdef __cplusplus
extern "C"
{
#endif

struct texture_t;

struct material_t
{
  struct texture_t* texture;
  int               color;
  int               emissive;
  int               specular;
  float             shininess;
  int               blend;
  int               flags;
};

#ifndef SWIG
void material_init(struct material_t* material);
void material_deinit(struct material_t* material);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MATERIAL_H_INCLUDED */
