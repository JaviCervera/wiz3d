#include "color.h"
#include "material.h"
#include "material_internal.h"
#include "texture.h"
#include "util.h"

static int _material_shininesspower = 128;

EXPORT Texture* CALL GetMaterialTexture(const Material* material) { return material->texture; }

EXPORT void CALL SetMaterialTexture(Material* material, Texture* texture) { material->texture = texture; }

EXPORT int CALL GetMaterialDiffuse(const Material* material) { return material->diffuse; }

EXPORT void CALL SetMaterialDiffuse(Material* material, int color) { material->diffuse = color; }

EXPORT int CALL GetMaterialEmissive(const Material* material) { return material->emissive; }

EXPORT void CALL SetMaterialEmissive(Material* material, int color) { material->emissive = color; }

EXPORT int CALL GetMaterialSpecular(const Material* material) { return material->specular; }

EXPORT void CALL SetMaterialSpecular(Material* material, int color) { material->specular = color; }

EXPORT float CALL GetMaterialShininess(const Material* material) { return material->shininess; }

EXPORT void CALL SetMaterialShininess(Material* material, float shininess) { material->shininess = shininess; }

EXPORT int CALL GetMaterialBlend(const Material* material) { return material->blend; }

EXPORT void CALL SetMaterialBlend(Material* material, int blend) { material->blend = blend; }

EXPORT int CALL GetMaterialFlags(const Material* material) { return material->flags; }

EXPORT void CALL SetMaterialFlags(Material* material, int flags) { material->flags = flags; }

EXPORT int CALL GetMaterialShininessPower(const Material* material) { return material->shininesspower; }

EXPORT void CALL SetMaterialShininessPower(Material* material, int power) { material->shininesspower = power; }

EXPORT int CALL GetDefaultShininessPower() { return _material_shininesspower; }

EXPORT void CALL SetDefaultShininessPower(int power) { _material_shininesspower = _Clamp(power, 0, 128); }

void _InitMaterial(Material* material) {
  material->texture = NULL;
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
