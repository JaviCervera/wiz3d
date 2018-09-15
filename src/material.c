#include "color.h"
#include "material.h"
#include "texture.h"

void material_init(struct material_t* material)
{
  material->texture = NULL;
  material->diffuse = _COLOR_WHITE;
  material->emissive = _COLOR_BLACK;
  material->specular = _COLOR_WHITE;
  material->shininess = 0;
  material->blend = _BLEND_SOLID;
  material->flags = _FLAG_ALL;
}

void material_deinit(struct material_t* material)
{
  if (material->texture) texture_release(material->texture);
}
