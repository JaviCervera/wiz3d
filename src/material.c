#include "color.h"
#include "material.h"
#include "material_internal.h"
#include "texture.h"
#include "util.h"

static int _material_shininesspower = 128;

EXPORT Texture* CALL spGetMaterialTexture(const Material* material) { return material->texture; }

EXPORT void CALL spSetMaterialTexture(Material* material, Texture* texture) { material->texture = texture; }

EXPORT Texture* CALL spGetMaterialLightmap(const Material* material) { return material->lightmap; }

EXPORT void CALL spSetMaterialLightmap(Material* material, Texture* lightmap) { material->lightmap = lightmap; }

EXPORT int CALL spGetMaterialDiffuse(const Material* material) { return material->diffuse; }

EXPORT void CALL spSetMaterialDiffuse(Material* material, int color) { material->diffuse = color; }

EXPORT int CALL spGetMaterialEmissive(const Material* material) { return material->emissive; }

EXPORT void CALL spSetMaterialEmissive(Material* material, int color) { material->emissive = color; }

EXPORT int CALL spGetMaterialSpecular(const Material* material) { return material->specular; }

EXPORT void CALL spSetMaterialSpecular(Material* material, int color) { material->specular = color; }

EXPORT float CALL spGetMaterialShininess(const Material* material) { return material->shininess; }

EXPORT void CALL spSetMaterialShininess(Material* material, float shininess) { material->shininess = shininess; }

EXPORT int CALL spGetMaterialBlend(const Material* material) { return material->blend; }

EXPORT void CALL spSetMaterialBlend(Material* material, int blend) { material->blend = blend; }

EXPORT int CALL spGetMaterialFlags(const Material* material) { return material->flags; }

EXPORT void CALL spSetMaterialFlags(Material* material, int flags) { material->flags = flags; }

EXPORT int CALL spGetMaterialShininessPower(const Material* material) { return material->shininesspower; }

EXPORT void CALL spSetMaterialShininessPower(Material* material, int power) { material->shininesspower = power; }

EXPORT int CALL spGetDefaultShininessPower() { return _material_shininesspower; }

EXPORT void CALL spSetDefaultShininessPower(int power) { _material_shininesspower = _Clamp(power, 0, 128); }

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
