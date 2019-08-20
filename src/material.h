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

EXPORT Texture* CALL spGetMaterialTexture(const Material* material);
EXPORT void CALL spSetMaterialTexture(Material* material, Texture* texture);
EXPORT int CALL spGetMaterialDiffuse(const Material* material);
EXPORT void CALL spSetMaterialDiffuse(Material* material, int color);
EXPORT int CALL spGetMaterialEmissive(const Material* material);
EXPORT void CALL spSetMaterialEmissive(Material* material, int color);
EXPORT int CALL spGetMaterialSpecular(const Material* material);
EXPORT void CALL spSetMaterialSpecular(Material* material, int color);
EXPORT float CALL spGetMaterialShininess(const Material* material);
EXPORT void CALL spSetMaterialShininess(Material* material, float shininess);
EXPORT int CALL spGetMaterialBlend(const Material* material);
EXPORT void CALL spSetMaterialBlend(Material* material, int blend);
EXPORT int CALL spGetMaterialFlags(const Material* material);
EXPORT void CALL spSetMaterialFlags(Material* material, int flags);
EXPORT int CALL spGetMaterialShininessPower(const Material* material);
EXPORT void CALL spSetMaterialShininessPower(Material* material, int power);

EXPORT int CALL spGetDefaultShininessPower();
EXPORT void CALL spSetDefaultShininessPower(int power);

#ifndef SWIG
void _InitMaterial(Material* material);
void _FinishMaterial(Material* material);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MATERIAL_H_INCLUDED */
