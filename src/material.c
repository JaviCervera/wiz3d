#include "color.h"
#include "material.h"
#include "texture.h"
#include "util.h"

static int _material_shininesspower = 128;

EXPORT int CALL GetShininessPower()
{
  return _material_shininesspower;
}

EXPORT void CALL SetShininessPower(int power)
{
  _material_shininesspower = _Clamp(power, 0, 128);
}

void _InitMaterial(Material* material)
{
  material->texture = NULL;
  material->diffuse = COLOR_WHITE;
  material->emissive = COLOR_BLACK;
  material->specular = COLOR_WHITE;
  material->shininess = 0;
  material->blend = BLEND_SOLID;
  material->flags = FLAG_ALL;
  material->shininesspower = -1;
}

void _FinishMaterial(Material* material)
{
  if (material->texture) ReleaseTexture(material->texture);
}
