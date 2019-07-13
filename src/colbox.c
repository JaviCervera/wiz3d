#include "../lib/litelibs/litecol.h"
#include "../lib/litelibs/litemath3d.h"
#include "../lib/stb/stretchy_buffer.h"
#include "colbox.h"

typedef struct
{
  lvec3_t min;
  lvec3_t max;
} colbox_t;

static colbox_t* _colboxes = NULL; /* array of boxes */

EXPORT void CALL colbox_add(float minx, float miny, float minz, float maxx, float maxy, float maxz)
{
  colbox_t box;
  box.min = lvec3(minx, miny, minz);
  box.max = lvec3(maxx, maxy, maxz);
  sb_push(_colboxes, box);
}

EXPORT void CALL colbox_clear()
{
  sb_free(_colboxes);
}

bool_t _colbox_checkbox(float minx, float miny, float minz, float maxx, float maxy, float maxz)
{
  int i;

  for (i = 0; i < sb_count(_colboxes); ++i)
  {
    if (lcol_boxbox(
      _colboxes[i].min.x, _colboxes[i].min.y, _colboxes[i].min.z,
      _colboxes[i].max.x, _colboxes[i].max.y, _colboxes[i].max.z,
      minx, miny, minz, maxx, maxy, maxz
    )) return TRUE;
  }
  return FALSE;
}

bool_t _colbox_checksphere(float x, float y, float z, float sq_radius)
{
  int i;

  for (i = 0; i < sb_count(_colboxes); ++i)
  {
    if (lcol_boxsphere(
      _colboxes[i].min.x, _colboxes[i].min.y, _colboxes[i].min.z,
      _colboxes[i].max.x, _colboxes[i].max.y, _colboxes[i].max.z,
      x, y, z, sq_radius
    )) return TRUE;
  }
  return FALSE;
}