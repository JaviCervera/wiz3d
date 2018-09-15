#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "../lib/stretchy_buffer.h"
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

void _object_setmesh(struct object_t* object, struct mesh_t* mesh)
{
  object->_mesh = mesh;
  sb_add(object->_materials, mesh_numbuffers(mesh));
  memcpy(object->_materials, mesh_material(mesh, 0), sizeof(struct material_t) * mesh_numbuffers(mesh));
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
  object->animmode = _ANIM_STOP;
  object->animspeed = 1;
  object->animframe = 0;
  object->animmin = 0;
  object->animmax = 0;
  object->_mesh = NULL;
  object->_materials = NULL;
  return object;
}

struct object_t* object_newcube()
{
  struct object_t* object;
  struct mesh_t* mesh;
  int buffer;

  object = object_new();
  mesh = mesh_new();
  buffer = mesh_addbuffer(mesh);
    
  /* add front face */
  mesh_addvertex(mesh, buffer, -0.5f,  0.5f, -0.5f, 0, 0, -1, 0, 0);
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f, -0.5f, 0, 0, -1, 1, 0);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 0, 0, -1, 1, 1);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, -1, 0, 1);
  mesh_addtriangle(mesh, buffer, 0, 1, 2);
  mesh_addtriangle(mesh, buffer, 0, 2, 3);

  /* add right face */
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f, -0.5f, 1, 0, 0, 0, 0);
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f,  0.5f, 1, 0, 0, 1, 0);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f,  0.5f, 1, 0, 0, 1, 1);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 1, 0, 0, 0, 1);
  mesh_addtriangle(mesh, buffer, 4, 5, 6);
  mesh_addtriangle(mesh, buffer, 4, 6, 7);

  /* add back face */
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f, 0.5f, 0, 0, 1, 0, 0);
  mesh_addvertex(mesh, buffer, -0.5f,  0.5f, 0.5f, 0, 0, 1, 1, 0);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, 0.5f, 0, 0, 1, 1, 1);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, 0.5f, 0, 0, 1, 0, 1);
  mesh_addtriangle(mesh, buffer, 8, 9, 10);
  mesh_addtriangle(mesh, buffer, 8, 10, 11);

  /* add left face */
  mesh_addvertex(mesh, buffer, -0.5f,  0.5f,  0.5f, -1, 0, 0, 0, 0);
  mesh_addvertex(mesh, buffer, -0.5f,  0.5f, -0.5f, -1, 0, 0, 1, 0);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, -0.5f, -1, 0, 0, 1, 1);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f,  0.5f, -1, 0, 0, 0, 1);
  mesh_addtriangle(mesh, buffer, 12, 13, 14);
  mesh_addtriangle(mesh, buffer, 12, 14, 15);

  /* add top face */
  mesh_addvertex(mesh, buffer, -0.5f, 0.5f,  0.5f, 0, 1, 0, 0, 0);
  mesh_addvertex(mesh, buffer,  0.5f, 0.5f,  0.5f, 0, 1, 0, 1, 0);
  mesh_addvertex(mesh, buffer,  0.5f, 0.5f, -0.5f, 0, 1, 0, 1, 1);
  mesh_addvertex(mesh, buffer, -0.5f, 0.5f, -0.5f, 0, 1, 0, 0, 1);
  mesh_addtriangle(mesh, buffer, 16, 17, 18);
  mesh_addtriangle(mesh, buffer, 16, 18, 19);

  /* add bottom face */
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, -1, 0, 0, 0);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 0, -1, 0, 1, 0);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f,  0.5f, 0, -1, 0, 1, 1);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f,  0.5f, 0, -1, 0, 0, 1);
  mesh_addtriangle(mesh, buffer, 20, 21, 22);
  mesh_addtriangle(mesh, buffer, 20, 22, 23);

  /* set object mesh & materials */
  _object_setmesh(object, mesh);

  return object;
}

struct object_t* object_newquad()
{
  struct object_t* object;
  struct mesh_t* mesh;
  int buffer;

  object = object_new();
  mesh = mesh_new();
  buffer = mesh_addbuffer(mesh);

  mesh_addvertex(mesh, buffer, -0.5f,  0.5f, 0, 0, 0, -1, 0, 0);
  mesh_addvertex(mesh, buffer,  0.5f,  0.5f, 0, 0, 0, -1, 1, 0);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, 0, 0, 0, -1, 1, 1);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 1);
  mesh_addtriangle(mesh, buffer, 0, 1, 2);
  mesh_addtriangle(mesh, buffer, 0, 2, 3);

  /* set object mesh & materials */
  _object_setmesh(object, mesh);

  return object;
}

struct object_t* object_newtriangle()
{
  struct object_t* object;
  struct mesh_t* mesh;
  int buffer;

  object = object_new();
  mesh = mesh_new();
  buffer = mesh_addbuffer(mesh);

  mesh_addvertex(mesh, buffer,     0,  0.5f, 0, 0, 0, -1, 0.5f, 1);
  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, 0, 0, 0, -1, 1, 0);
  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 0);
  mesh_addtriangle(mesh, buffer, 0, 1, 2);

  /* set object mesh & materials */
  _object_setmesh(object, mesh);

  return object;
}

struct object_t* object_load(const char* filename)
{
  struct mesh_t* mesh;
  struct object_t* object;

  mesh = mesh_load(filename);
  if (mesh)
  {
    object = object_new();
    _object_setmesh(object, mesh); /* set object mesh & materials */
    return object;
  }
  else
  {
    return NULL;
  }
}

struct object_t* object_clone(struct object_t* object)
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
  if (object->_mesh) mesh_retain(object->_mesh);
  return new_object;
}

void object_delete(struct object_t* object)
{
  if (object->_mesh) mesh_release(object->_mesh);
  free(object);
}

int object_nummaterials(struct object_t* object)
{
  return sb_count(object->_materials);
}

struct material_t* object_material(struct object_t* object, int mat)
{
  return &object->_materials[mat];
}

void object_move(struct object_t* object, float x, float y, float z)
{
  lvec3_t vec;
  vec = lquat_mulvec3(lquat_fromeuler(lvec3_rad(lvec3(object->pitch, object->yaw, object->roll))), lvec3(x, y, z));
  vec = lvec3_add(lvec3(object->x, object->y, object->z), vec);
  object->x = vec.x;
  object->y = vec.y;
  object->z = vec.z;
}

void object_turn(struct object_t* object, float pitch, float yaw, float roll)
{
  lvec3_t vec;

  vec = lvec3_add(lvec3(object->pitch, object->yaw, object->roll), lvec3(pitch, yaw, roll));
  object->pitch = vec.x;
  object->yaw = vec.y;
  object->roll = vec.z;
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
  }
  else
  {
    _mesh_animate(object->_mesh, 0);
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

int object_numframes(struct object_t* object)
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
