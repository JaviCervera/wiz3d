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

EXPORT Texture* CALL GetMaterialTexture(const Material* material);
EXPORT void CALL SetMaterialTexture(Material* material, Texture* texture);
EXPORT int CALL GetMaterialDiffuse(const Material* material);
EXPORT void CALL SetMaterialDiffuse(Material* material, int color);
EXPORT int CALL GetMaterialEmissive(const Material* material);
EXPORT void CALL SetMaterialEmissive(Material* material, int color);
EXPORT int CALL GetMaterialSpecular(const Material* material);
EXPORT void CALL SetMaterialSpecular(Material* material, int color);
EXPORT float CALL GetMaterialShininess(const Material* material);
EXPORT void CALL SetMaterialShininess(Material* material, float shininess);
EXPORT int CALL GetMaterialBlend(const Material* material);
EXPORT void CALL SetMaterialBlend(Material* material, int blend);
EXPORT int CALL GetMaterialFlags(const Material* material);
EXPORT void CALL SetMaterialFlags(Material* material, int flags);
EXPORT int CALL GetMaterialShininessPower(const Material* material);
EXPORT void CALL SetMaterialShininessPower(Material* material, int power);

EXPORT int CALL GetDefaultShininessPower();
EXPORT void CALL SetDefaultShininessPower(int power);

#ifndef SWIG
void _InitMaterial(Material* material);
void _FinishMaterial(Material* material);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MATERIAL_H_INCLUDED */
