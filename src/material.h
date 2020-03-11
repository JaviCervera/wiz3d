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

EXPORT Texture* CALL bmGetMaterialTexture(const Material* material);
EXPORT void CALL bmSetMaterialTexture(Material* material, Texture* texture);
EXPORT Texture* CALL bmGetMaterialLightmap(const Material* material);
EXPORT void CALL bmSetMaterialLightmap(Material* material, Texture* lightmap);
EXPORT int CALL bmGetMaterialDiffuse(const Material* material);
EXPORT void CALL bmSetMaterialDiffuse(Material* material, int color);
EXPORT int CALL bmGetMaterialEmissive(const Material* material);
EXPORT void CALL bmSetMaterialEmissive(Material* material, int color);
EXPORT int CALL bmGetMaterialSpecular(const Material* material);
EXPORT void CALL bmSetMaterialSpecular(Material* material, int color);
EXPORT float CALL bmGetMaterialShininess(const Material* material);
EXPORT void CALL bmSetMaterialShininess(Material* material, float shininess);
EXPORT int CALL bmGetMaterialBlend(const Material* material);
EXPORT void CALL bmSetMaterialBlend(Material* material, int blend);
EXPORT int CALL bmGetMaterialFlags(const Material* material);
EXPORT void CALL bmSetMaterialFlags(Material* material, int flags);
EXPORT int CALL bmGetMaterialShininessPower(const Material* material);
EXPORT void CALL bmSetMaterialShininessPower(Material* material, int power);

EXPORT int CALL bmGetDefaultShininessPower();
EXPORT void CALL bmSetDefaultShininessPower(int power);

#ifndef SWIG
void _InitMaterial(Material* material);
void _FinishMaterial(Material* material);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MATERIAL_H_INCLUDED */
