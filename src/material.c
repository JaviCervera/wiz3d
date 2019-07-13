#include "color.h"
#include "material.h"
#include "texture.h"
#include "util.h"

static int _material_shininesspower = 128;

EXPORT int CALL material_shininesspower()
{
  return _material_shininesspower;
}

EXPORT void CALL material_setshininesspower(int power)
{
  _material_shininesspower = _clamp(power, 0, 128);
}

void _material_init(struct material_t* material)
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

void _material_deinit(struct material_t* material)
{
  if (material->texture) texture_release(material->texture);
}
