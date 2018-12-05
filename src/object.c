#include "../lib/litelibs/litecol.h"
#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "../lib/stb/stretchy_buffer.h"
#include "colbox.h"
#include "color.h"
#include "material.h"
#include "mesh.h"
#include "object.h"
#include "screen.h"
#include "texture.h"
#include "util.h"
#include "viewer.h"
#include <string.h>

static float _object_animfps = 16;

void _object_setmaterials(struct object_t* object)
{
  sb_add(object->_materials, mesh_numbuffers(object->_mesh));
  memcpy(
    object->_materials,
    mesh_material(object->_mesh, 0), 
    sizeof(struct material_t) * mesh_numbuffers(object->_mesh));
}

struct object_t* object_new()
{
  struct object_t* object = _alloc(struct object_t);
  object->x = 0;
  object->y = 0;
  object->z = 0;
  object->pitch = 0;
  object->yaw = 0;
  object->roll = 0;
  object->sx = 1;
  object->sy = 1;
  object->sz = 1;
  object->billboard = _BILLBOARD_NONE;
  object->colmode = _COL_NONE;
  object->radius = 0;
  object->animmode = _ANIM_STOP;
  object->animspeed = 1;
  object->animframe = 0;
  object->animmin = 0;
  object->animmax = 0;
  object->_mesh = mesh_new();
  object->_materials = NULL;
  return object;
}

struct object_t* object_newcube()
{
  struct object_t* object;
  struct mesh_t* mesh;
  int buffer;

  object = object_new();
  mesh = object->_mesh;
  buffer = mesh_addbuffer(mesh);

  /* add front face */
  mesh_addvertex(mesh, buffer, -0.5f,  0.5f, -0.5f, 0, 0, -1, 0, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f, -0.5f, 0, 0, -1, 1, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 0, 0, -1, 1, 1, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, -1, 0, 1, _COLOR_WHITE);
  mesh_addtriangle(mesh, buffer, 0, 1, 2);
  mesh_addtriangle(mesh, buffer, 0, 2, 3);

  /* add right face */
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f, -0.5f, 1, 0, 0, 0, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f,  0.5f, 1, 0, 0, 1, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f,  0.5f, 1, 0, 0, 1, 1, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 1, 0, 0, 0, 1, _COLOR_WHITE);
  mesh_addtriangle(mesh, buffer, 4, 5, 6);
  mesh_addtriangle(mesh, buffer, 4, 6, 7);

  /* add back face */
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f, 0.5f, 0, 0, 1, 0, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f,  0.5f, 0.5f, 0, 0, 1, 1, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, 0.5f, 0, 0, 1, 1, 1, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, 0.5f, 0, 0, 1, 0, 1, _COLOR_WHITE);
  mesh_addtriangle(mesh, buffer, 8, 9, 10);
  mesh_addtriangle(mesh, buffer, 8, 10, 11);

  /* add left face */
  mesh_addvertex(mesh, buffer, -0.5f,  0.5f,  0.5f, -1, 0, 0, 0, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f,  0.5f, -0.5f, -1, 0, 0, 1, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, -0.5f, -1, 0, 0, 1, 1, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f,  0.5f, -1, 0, 0, 0, 1, _COLOR_WHITE);
  mesh_addtriangle(mesh, buffer, 12, 13, 14);
  mesh_addtriangle(mesh, buffer, 12, 14, 15);

  /* add top face */
  mesh_addvertex(mesh, buffer, -0.5f, 0.5f,  0.5f, 0, 1, 0, 0, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, 0.5f,  0.5f, 0, 1, 0, 1, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, 0.5f, -0.5f, 0, 1, 0, 1, 1, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f, 0.5f, -0.5f, 0, 1, 0, 0, 1, _COLOR_WHITE);
  mesh_addtriangle(mesh, buffer, 16, 17, 18);
  mesh_addtriangle(mesh, buffer, 16, 18, 19);

  /* add bottom face */
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, -1, 0, 0, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 0, -1, 0, 1, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f,  0.5f, 0, -1, 0, 1, 1, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f,  0.5f, 0, -1, 0, 0, 1, _COLOR_WHITE);
  mesh_addtriangle(mesh, buffer, 20, 21, 22);
  mesh_addtriangle(mesh, buffer, 20, 22, 23);

  object_rebuildmesh(object);
  _object_setmaterials(object);
  return object;
}

struct object_t* object_newquad()
{
  struct object_t* object;
  struct mesh_t* mesh;
  int buffer;

  object = object_new();
  mesh = object->_mesh;
  buffer = mesh_addbuffer(mesh);

  mesh_addvertex(mesh, buffer, -0.5f,  0.5f, 0, 0, 0, -1, 0, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f, 0, 0, 0, -1, 1, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, 0, 0, 0, -1, 1, 1, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 1, _COLOR_WHITE);
  mesh_addtriangle(mesh, buffer, 0, 1, 2);
  mesh_addtriangle(mesh, buffer, 0, 2, 3);

  /* set object materials */
  _object_setmaterials(object);

  return object;
}

struct object_t* object_newtriangle()
{
  struct object_t* object;
  struct mesh_t* mesh;
  int buffer;

  object = object_new();
  mesh = object->_mesh;
  buffer = mesh_addbuffer(mesh);

  mesh_addvertex(mesh, buffer,     0,  0.5f, 0, 0, 0, -1, 0.5f, 1, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, 0, 0, 0, -1, 1, 0, _COLOR_WHITE);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 0, _COLOR_WHITE);
  mesh_addtriangle(mesh, buffer, 0, 1, 2);

  object_rebuildmesh(object);
  _object_setmaterials(object);
  return object;
}

struct object_t* object_load(const char* filename)
{
  struct object_t* object;
  struct mesh_t* mesh;

  object = object_new();
  mesh = object->_mesh;
  if (mesh_load(filename, mesh))
  {
    object_rebuildmesh(object);
    _object_setmaterials(object);
    return object;
  }
  else
  {
    object_delete(object);
    return NULL;
  }
}

struct object_t* object_clone(const struct object_t* object)
{
  struct object_t* new_object = object_new();
  new_object->x = object->x;
  new_object->y = object->y;
  new_object->z = object->z;
  new_object->pitch = object->pitch;
  new_object->yaw = object->yaw;
  new_object->roll = object->roll;
  new_object->sx = object->sx;
  new_object->sy = object->sy;
  new_object->sz = object->sz;
  new_object->_mesh = object->_mesh;
  sb_add(new_object->_materials, sb_count(object->_materials));
  memcpy(new_object->_materials, object->_materials, sizeof(struct material_t) * sb_count(object->_materials));
  mesh_retain(object->_mesh);
  return new_object;
}

void object_delete(struct object_t* object)
{
  mesh_release(object->_mesh);
  free(object);
}

int object_addbuffer(struct object_t* object)
{
  int buffer = mesh_addbuffer(object->_mesh);
  sb_add(object->_materials, 1);
  return buffer;
}

int object_numbuffers(struct object_t* object)
{
  return mesh_numbuffers(object->_mesh);
}

int object_addvertex(struct object_t* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color)
{
  return mesh_addvertex(object->_mesh, buffer, x, y, z, nx, ny, nz, u, v, color);
}

int object_addtriangle(struct object_t* object, int buffer, int v0, int v1, int v2)
{
  return mesh_addtriangle(object->_mesh, buffer, v0, v1, v2);
}

void object_rebuildmesh(struct object_t* object)
{
  mesh_rebuild(object->_mesh);
}

struct material_t* object_material(struct object_t* object, int index)
{
  return &object->_materials[index];
}

float object_width(const struct object_t* object)
{
  return mesh_width(object->_mesh) * object->sx;
}

float object_height(const struct object_t* object)
{
  return mesh_height(object->_mesh) * object->sy;
}

float object_depth(const struct object_t* object)
{
  return mesh_depth(object->_mesh) * object->sz;
}

float object_minx(const struct object_t* object)
{
  return object->x + mesh_boxminx(object->_mesh) * object->sx;
}

float object_miny(const struct object_t* object)
{
  return object->y + mesh_boxminy(object->_mesh) * object->sy;
}

float object_minz(const struct object_t* object)
{
  if (object->billboard == _BILLBOARD_NONE)
    return object->z + mesh_boxminz(object->_mesh) * object->sz;
  else
    return object_minx(object);
}

float object_maxx(const struct object_t* object)
{
  return object->x + mesh_boxmaxx(object->_mesh) * object->sx;
}

float object_maxy(const struct object_t* object)
{
  return object->y + mesh_boxmaxy(object->_mesh) * object->sy;
}

float object_maxz(const struct object_t* object)
{
  if (object->billboard == _BILLBOARD_NONE)
    return object->z + mesh_boxmaxz(object->_mesh) * object->sz;
  else
    return object_maxx(object);
}

bool_t object_move(struct object_t* object, float x, float y, float z)
{
  lvec3_t vec;
  bool_t collided = FALSE;

  /* transform movement by object's rotation */
  vec = lquat_mulvec3(lquat_fromeuler(lvec3_rad(lvec3(object->pitch, object->yaw, object->roll))), lvec3(x, y, z));

  /* move x and check collision boxes */
  object->x += vec.x;
  if (object_collidesboxes(object))
  {
    collided = TRUE;
    object->x -= vec.x;
  }

  /* move y and check collision boxes */
  object->y += vec.y;
  if (object_collidesboxes(object))
  {
    collided = TRUE;
    object->y -= vec.y;
  }

  /* move z and check collision boxes */
  object->z += vec.z;
  if (object_collidesboxes(object))
  {
    collided = TRUE;
    object->z -= vec.z;
  }

  return collided;
}

void object_turn(struct object_t* object, float pitch, float yaw, float roll)
{
  lvec3_t vec;

  vec = lvec3_add(lvec3(object->pitch, object->yaw, object->roll), lvec3(pitch, yaw, roll));
  object->pitch = vec.x;
  object->yaw = vec.y;
  object->roll = vec.z;
}

bool_t object_collidesboxes(struct object_t* object)
{
  if (object->colmode == _COL_SPHERE)
  {
    return _colbox_checksphere(object->x, object->y, object->z, object->radius * object->radius);
  }
  else if (object->colmode == _COL_BOX)
  {
    return _colbox_checkbox(
      object_minx(object), object_miny(object), object_minz(object),
      object_maxx(object), object_maxy(object), object_maxz(object)
    );
  }
  else
  {
    return FALSE;
  }
}

bool_t object_collidesobject(struct object_t* object, struct object_t* object2)
{
  if (object != object2 && object->colmode != _COL_NONE && object2->colmode != _COL_NONE)
  {
    if (object->colmode == _COL_SPHERE && object2->colmode == _COL_SPHERE)
    {
      return lcol_spheresphere(
        object->x, object->y, object->z, object->radius * object->radius,
        object2->x, object2->y, object2->z, object2->radius * object2->radius
      ) == 1;
    }
    else if (object->colmode == _COL_SPHERE && object2->colmode == _COL_BOX)
    {
      return lcol_boxsphere(
        object_minx(object2), object_miny(object2), object_minz(object2),
        object_maxx(object2), object_maxy(object2), object_maxz(object2),
        object->x, object->y, object->z, object->radius * object->radius
      ) == 1;
    }
    else if (object->colmode == _COL_BOX && object2->colmode == _COL_SPHERE)
    {
      return lcol_boxsphere(
        object_minx(object), object_miny(object), object_minz(object),
        object_maxx(object), object_maxy(object), object_maxz(object),
        object2->x, object2->y, object2->z, object2->radius * object2->radius
      ) == 1;
    }
    else if (object->colmode == _COL_BOX && object2->colmode == _COL_BOX)
    {
      return lcol_boxbox(
        object_minx(object), object_miny(object), object_minz(object),
        object_maxx(object), object_maxy(object), object_maxz(object),
        object_minx(object2), object_miny(object2), object_minz(object2),
        object_maxx(object2), object_maxy(object2), object_maxz(object2)
      ) == 1;
    }
  }
  else
  {
    return FALSE;
  }
}

void object_draw(struct object_t* object)
{
  lmat4_t modelview;

  /* calculate animation */
  if (object->animmode != _ANIM_STOP)
  {
    int lastframe = (object->animmax != 0) ? object->animmax : _mesh_lastframe(object->_mesh);
    object->animframe += object->animspeed * _object_animfps * screen_delta();
    if (object->animframe > lastframe)
    {
      if (object->animmode == _ANIM_LOOP) object->animframe -= (lastframe - object->animmin);
      else object->animframe = lastframe;
    }
    if (object->animframe < object->animmin)
    {
      if (object->animmode == _ANIM_LOOP) object->animframe += (lastframe - object->animmin);
      else object->animframe = object->animmin;
    }
    _mesh_animate(object->_mesh, object->animframe);
    mesh_rebuild(object->_mesh);
  }
  else if (object->animframe != 0)
  {
    _mesh_animate(object->_mesh, 0);
    mesh_rebuild(object->_mesh);
    object->animframe = 0;
  }

  /* calculate modelview */
  switch (object->billboard)
  {
    case _BILLBOARD_NONE:
      modelview = lmat4_transform(
        lvec3(object->x, object->y, object->z),
        lquat_fromeuler(lvec3_rad(lvec3(object->pitch, object->yaw, object->roll))),
        lvec3(object->sx, object->sy, object->sz));
      break;
    default:
      modelview = lmat4_billboard(
        *(const lmat4_t*)_viewer_activematrix(),
        lvec3(object->x, object->y, object->z),
        lm_deg2rad(object->roll),
        object->sx, object->sy,
        object->billboard == _BILLBOARD_UPRIGHT ? TRUE : FALSE);
      break;
  }
  modelview = lmat4_mul(*(const lmat4_t*)_viewer_activematrix(), modelview);
  lgfx_setmodelview(modelview.m);

  /* set properties & draw */
  _mesh_draw(object->_mesh, object->_materials);
}

int object_numframes(const struct object_t* object)
{
  return _mesh_lastframe(object->_mesh);
}

void object_setanimfps(float fps)
{
  _object_animfps = fps;
}

float object_animfps()
{
  return _object_animfps;
}
