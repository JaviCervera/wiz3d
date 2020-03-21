#include "color.h"
#include "material.h"
#include "material_internal.h"
#include "texture.h"
#include "util.h"

static int _material_shininesspower = 128;

EXPORT Texture* CALL bmGetMaterialTexture(const Material* material) { return material->texture; }

EXPORT void CALL bmSetMaterialTexture(Material* material, Texture* texture) { material->texture = texture; }

EXPORT Texture* CALL bmGetMaterialLightmap(const Material* material) { return material->lightmap; }

EXPORT void CALL bmSetMaterialLightmap(Material* material, Texture* lightmap) { material->lightmap = lightmap; }

EXPORT int CALL bmGetMaterialDiffuse(const Material* material) { return material->diffuse; }

EXPORT void CALL bmSetMaterialDiffuse(Material* material, int color) { material->diffuse = color; }

EXPORT int CALL bmGetMaterialEmissive(const Material* material) { return material->emissive; }

EXPORT void CALL bmSetMaterialEmissive(Material* material, int color) { material->emissive = color; }

EXPORT int CALL bmGetMaterialSpecular(const Material* material) { return material->specular; }

EXPORT void CALL bmSetMaterialSpecular(Material* material, int color) { material->specular = color; }

EXPORT float CALL bmGetMaterialShininess(const Material* material) { return material->shininess; }

EXPORT void CALL bmSetMaterialShininess(Material* material, float shininess) { material->shininess = shininess; }

EXPORT int CALL bmGetMaterialBlend(const Material* material) { return material->blend; }

EXPORT void CALL bmSetMaterialBlend(Material* material, int blend) { material->blend = blend; }

EXPORT int CALL bmGetMaterialFlags(const Material* material) { return material->flags; }

EXPORT void CALL bmSetMaterialFlags(Material* material, int flags) { material->flags = flags; }

EXPORT int CALL bmGetMaterialShininessPower(const Material* material) { return material->shininesspower; }

EXPORT void CALL bmSetMaterialShininessPower(Material* material, int power) { material->shininesspower = power; }

EXPORT int CALL bmGetDefaultShininessPower() { return _material_shininesspower; }

EXPORT void CALL bmSetDefaultShininessPower(int power) { _material_shininesspower = _Clamp(power, 0, 128); }

void _InitMaterial(Material* material) {
    material->texture = NULL;
    material->lightmap = NULL;
    material->diffuse = COLOR_WHITE;
    material->emissive = COLOR_BLACK;
    material->specular = COLOR_WHITE;
    material->shininess = 0;
    material->blend = BLEND_SOLID;
    material->flags = FLAG_ALL;
    material->shininesspower = -1;
}

void _FinishMaterial(Material* material) {
    if (material->texture) ReleaseTexture(material->texture);
}
