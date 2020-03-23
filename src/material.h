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

EXPORT Texture* CALL wzGetMaterialTexture(const Material* material);
EXPORT void CALL wzSetMaterialTexture(Material* material, Texture* texture);
EXPORT Texture* CALL wzGetMaterialLightmap(const Material* material);
EXPORT void CALL wzSetMaterialLightmap(Material* material, Texture* lightmap);
EXPORT int CALL wzGetMaterialDiffuse(const Material* material);
EXPORT void CALL wzSetMaterialDiffuse(Material* material, int color);
EXPORT int CALL wzGetMaterialEmissive(const Material* material);
EXPORT void CALL wzSetMaterialEmissive(Material* material, int color);
EXPORT int CALL wzGetMaterialSpecular(const Material* material);
EXPORT void CALL wzSetMaterialSpecular(Material* material, int color);
EXPORT float CALL wzGetMaterialShininess(const Material* material);
EXPORT void CALL wzSetMaterialShininess(Material* material, float shininess);
EXPORT int CALL wzGetMaterialBlend(const Material* material);
EXPORT void CALL wzSetMaterialBlend(Material* material, int blend);
EXPORT int CALL wzGetMaterialFlags(const Material* material);
EXPORT void CALL wzSetMaterialFlags(Material* material, int flags);

#ifndef SWIG
void _InitMaterial(Material* material);
void _FinishMaterial(Material* material);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MATERIAL_H_INCLUDED */
