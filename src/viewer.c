#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "viewer.h"
#include "color.h"
#include "light.h"
#include "screen.h"
#include "util.h"
#include <math.h>

static struct viewer_t* _view_active_viewer;
static lmat4_t _view_matrix;

struct viewer_t* viewer_new()
{
  struct viewer_t* viewer = alloc(struct viewer_t);
  viewer->x = 0;
  viewer->y = 0;
  viewer->z = 0;
  viewer->pitch = 0;
  viewer->yaw = 0;
  viewer->roll = 0;
  viewer->vx = 0;
  viewer->vy = 0;
  viewer->vw = -1;
  viewer->vh = -1;
  viewer->color = color_rgb(52, 73, 94);
  viewer->ortho = FALSE;
  viewer->fov = 60;
  viewer->min = 1;
  viewer->max = 1000;
  viewer->fogenabled = FALSE;
  viewer->fogcolor = _COLOR_DARKGRAY;
  viewer->fogmin = 0;
  viewer->fogmax = 1000;
  return viewer;
}

void viewer_delete(struct viewer_t* viewer)
{
  free(viewer);
}

void viewer_move(struct viewer_t* viewer, float x, float y, float z)
{
  lvec3_t vec;

  vec = lvec3_add(
    lvec3(viewer->x, viewer->y, viewer->z),
    lquat_mulvec3(lquat_fromeuler(lvec3_rad(lvec3(viewer->pitch, viewer->yaw, viewer->roll))), lvec3(x, y, z)));
  viewer->x = vec.x;
  viewer->y = vec.y;
  viewer->z = vec.z;
}

void viewer_turn(struct viewer_t* viewer, float pitch, float yaw, float roll)
{
  lvec3_t vec;

  vec = lvec3_add(lvec3(viewer->pitch, viewer->yaw, viewer->roll), lvec3(pitch, yaw, roll));
  viewer->pitch = vec.x;
  viewer->yaw = vec.y;
  viewer->roll = vec.z;
}

void viewer_prepare(struct viewer_t* viewer)
{
  int vp_w;
  int vp_h;
  float ratio;
  lmat4_t proj;
  lquat_t q;

  /* get real viewport size */
  vp_w = (viewer->vw != -1) ? viewer->vw : screen_width() - viewer->vx;
  vp_h = (viewer->vh != -1) ? viewer->vh : screen_height() - viewer->vy;

  /* set viewport (must be done before setting projection) */
  lgfx_setup3d(0, 0);
  lgfx_setviewport(viewer->vx, viewer->vy, vp_w, vp_h);

  /* prepare projection */
  ratio = vp_w / (float)vp_h;
  if ( viewer->ortho )
  {
    float width, height;
    height = viewer->min * tan(lm_deg2rad(viewer->fov)) * 2;
    width = height * ratio;
    proj = lmat4_ortholh(-width, width, -height, height, viewer->min, viewer->max);
  }
  else
  {
    proj = lmat4_perspectivelh(lm_deg2rad(viewer->fov), ratio, viewer->min, viewer->max);
  }
  lgfx_setprojection(proj.m);

  /* prepare view matrix */
  q = lquat_fromeuler(lvec3_rad(lvec3(viewer->pitch, viewer->yaw, viewer->roll)));
  _view_matrix = lmat4_identity();
  _view_matrix = lmat4_rotate(_view_matrix, -lquat_angle(q), lquat_axis(q));
  _view_matrix = lmat4_translate(_view_matrix, lvec3(-viewer->x, -viewer->y, -viewer->z));

  /* prepare lights */
  _light_prepare();

  /* clear buffers */
  lgfx_setdepthwrite(TRUE);
  lgfx_clearcolorbuffer(color_red(viewer->color) / 255.0f, color_green(viewer->color) / 255.0f, color_blue(viewer->color) / 255.0f);
  lgfx_cleardepthbuffer();

  /* set active viewer */
  _view_active_viewer = viewer;
}

struct viewer_t* _viewer_active()
{
  return _view_active_viewer;
}

void* _viewer_activematrix()
{
  return &_view_matrix;
}
