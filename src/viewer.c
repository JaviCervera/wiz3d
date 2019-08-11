#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "viewer.h"
#include "color.h"
#include "light.h"
#include "material.h"
#include "mesh.h"
#include "screen.h"
#include "texture.h"
#include "util.h"
#include <math.h>

static const Viewer* _view_active_viewer = NULL;
static lmat4_t _view_matrix;
static struct SMesh* _viewer_skybox = NULL;

static struct SMesh* _SetupViewerSkyboxMesh(struct STexture* texture);

EXPORT Viewer* CALL CreateViewer()
{
  Viewer* viewer = _Alloc(Viewer);
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
  viewer->clearmode = CLEAR_COLOR;
  viewer->clearcolor = GetRGB(52, 73, 94);
  viewer->skybox = NULL;
  viewer->ortho = FALSE;
  viewer->fov = 60;
  viewer->min = 1;
  viewer->max = 1000;
  viewer->fogenabled = FALSE;
  viewer->fogcolor = COLOR_DARKGRAY;
  viewer->fogmin = 0;
  viewer->fogmax = 1000;
  return viewer;
}

EXPORT void CALL DeleteViewer(Viewer* viewer)
{
  free(viewer);
}

EXPORT void CALL MoveViewer(Viewer* viewer, float x, float y, float z)
{
  lvec3_t vec;

  vec = lvec3_add(
    lvec3(viewer->x, viewer->y, viewer->z),
    lquat_mulvec3(lquat_fromeuler(lvec3_rad(lvec3(viewer->pitch, viewer->yaw, viewer->roll))), lvec3(x, y, z)));
  viewer->x = vec.x;
  viewer->y = vec.y;
  viewer->z = vec.z;
}

EXPORT void CALL TurnViewer(Viewer* viewer, float pitch, float yaw, float roll)
{
  lvec3_t vec;

  vec = lvec3_add(lvec3(viewer->pitch, viewer->yaw, viewer->roll), lvec3(pitch, yaw, roll));
  viewer->pitch = vec.x;
  viewer->yaw = vec.y;
  viewer->roll = vec.z;
}

EXPORT void CALL PrepareViewer(const Viewer* viewer)
{
  int vp_w;
  int vp_h;
  float ratio;
  float halfrange;
  lmat4_t proj;
  lmat4_t modelview;
  lquat_t q;

  /* set active viewer */
  _view_active_viewer = viewer;

  /* get real viewport size */
  vp_w = (viewer->vw != -1) ? viewer->vw : GetScreenWidth() - viewer->vx;
  vp_h = (viewer->vh != -1) ? viewer->vh : GetScreenHeight() - viewer->vy;

  /* set viewport (must be done before setting projection) */
  lgfx_setup3d(0, 0);
  lgfx_setviewport(viewer->vx, viewer->vy, vp_w, vp_h);

  /* prepare projection */
  ratio = vp_w / (float)vp_h;
  if (viewer->ortho)
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
  _PrepareLights();

  /* clear buffers */
  lgfx_setdepthwrite(TRUE);
  lgfx_cleardepthbuffer();
  switch (viewer->clearmode)
  {
    case CLEAR_COLOR:
      lgfx_clearcolorbuffer(
        GetRed(viewer->clearcolor) / 255.0f,
        GetGreen(viewer->clearcolor) / 255.0f,
        GetBlue(viewer->clearcolor) / 255.0f);
      break;
    case CLEAR_SKYBOX:
      halfrange = (viewer->max - viewer->min) * 0.5f;
      
      /* calculate modelview */
      modelview = lmat4_transform(
        lvec3(0, 0, 0),
        lquat(1, 0, 0, 0),
        lvec3(halfrange, halfrange, halfrange));
      modelview = lmat4_mul(_view_matrix, modelview);
      lgfx_setmodelview(modelview.m);

      /* draw skybox */
      _DrawMesh(_SetupViewerSkyboxMesh(viewer->skybox), NULL);

      break;
  }
}

const Viewer* _GetActiveViewer()
{
  return _view_active_viewer;
}

const void* _GetActiveMatrix()
{
  return &_view_matrix;
}

static struct SMesh* _SetupViewerSkyboxMesh(struct STexture* texture)
{
  if (!_viewer_skybox) _viewer_skybox = _CreateSkyboxMesh();
  GetMeshMaterial(_viewer_skybox, 0)->texture = texture;
  return _viewer_skybox;
}
