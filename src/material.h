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
extern "C" {
#endif

struct STexture;

typedef struct SMaterial
{
  struct STexture* texture;
  int diffuse;
  int emissive;
  int specular;
  float shininess;
  int blend;
  int flags;
  int shininesspower;
} Material;

EXPORT int CALL GetShininessPower();
EXPORT void CALL SetShininessPower(int power);

#ifndef SWIG
void _InitMaterial(Material* material);
void _FinishMaterial(Material* material);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MATERIAL_H_INCLUDED */
