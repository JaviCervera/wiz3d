#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "types.h"

#define BLEND_SOLID 0
#define BLEND_ALPHA 1
#define BLEND_ADD 2
#define BLEND_MUL 3

#define FLAG_CULL 1
#define FLAG_DEPTHWRITE 2
#define FLAG_LIGHTING 4
#define FLAG_FOG 8
#define FLAG_ALL 15

#ifdef __cplusplus
extern "C"
{
#endif

struct texture_t;

struct material_t
{
  struct texture_t* texture;
  int diffuse;
  int emissive;
  int specular;
  float shininess;
  int blend;
  int flags;
  int shininesspower;
};

EXPORT int CALL material_shininesspower();
EXPORT void CALL material_setshininesspower(int power);

#ifndef SWIG
void _material_init(struct material_t* material);
void _material_deinit(struct material_t* material);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MATERIAL_H_INCLUDED */
