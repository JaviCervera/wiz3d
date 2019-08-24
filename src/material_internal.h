#ifndef MATERIAL_INTERNAL_H_INCLUDED
#define MATERIAL_INTERNAL_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SMaterial {
  Texture* texture;
  Texture* lightmap;
  int diffuse;
  int emissive;
  int specular;
  float shininess;
  int blend;
  int flags;
  int shininesspower;
} Material;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MATERIAL_INTERNAL_H_INCLUDED */
