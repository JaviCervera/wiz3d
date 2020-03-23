#include "color.h"
#include "material.h"
#include "material_internal.h"
#include "texture.h"
#include "util.h"

EXPORT Texture* CALL wzGetMaterialTexture(const Material* material) { return material->texture; }

EXPORT void CALL wzSetMaterialTexture(Material* material, Texture* texture) { material->texture = texture; }

EXPORT Texture* CALL wzGetMaterialLightmap(const Material* material) { return material->lightmap; }

EXPORT void CALL wzSetMaterialLightmap(Material* material, Texture* lightmap) { material->lightmap = lightmap; }

EXPORT int CALL wzGetMaterialDiffuse(const Material* material) { return material->diffuse; }

EXPORT void CALL wzSetMaterialDiffuse(Material* material, int color) { material->diffuse = color; }

EXPORT int CALL wzGetMaterialEmissive(const Material* material) { return material->emissive; }

EXPORT void CALL wzSetMaterialEmissive(Material* material, int color) { material->emissive = color; }

EXPORT int CALL wzGetMaterialSpecular(const Material* material) { return material->specular; }

EXPORT void CALL wzSetMaterialSpecular(Material* material, int color) { material->specular = color; }

EXPORT float CALL wzGetMaterialShininess(const Material* material) { return material->shininess; }

EXPORT void CALL wzSetMaterialShininess(Material* material, float shininess) { material->shininess = _Clamp(shininess, 0.0f, 1.0f); }

EXPORT int CALL wzGetMaterialBlend(const Material* material) { return material->blend; }

EXPORT void CALL wzSetMaterialBlend(Material* material, int blend) { material->blend = blend; }

EXPORT int CALL wzGetMaterialFlags(const Material* material) { return material->flags; }

EXPORT void CALL wzSetMaterialFlags(Material* material, int flags) { material->flags = flags; }

void _InitMaterial(Material* material) {
    material->texture = NULL;
    material->lightmap = NULL;
    material->diffuse = COLOR_WHITE;
    material->emissive = COLOR_BLACK;
    material->specular = COLOR_WHITE;
    material->shininess = 0.0f;
    material->blend = BLEND_SOLID;
    material->flags = FLAG_ALL;
}

void _FinishMaterial(Material* material) {
    if (material->texture) ReleaseTexture(material->texture);
}
