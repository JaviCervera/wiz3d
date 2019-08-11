#include "../lib/litelibs/litecol.h"
#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "../lib/stb/stretchy_buffer.h"
#include "colbox.h"
#include "color.h"
#include "material.h"
#include "memblock.h"
#include "mesh.h"
#include "object.h"
#include "screen.h"
#include "texture.h"
#include "util.h"
#include "viewer.h"
#include <string.h>

static float _object_animfps = 16;

void _SetObjectMaterials(Object* object) {
  sb_free(object->_materials);
  object->_materials = NULL;
  sb_add(object->_materials, GetNumMeshBuffers(object->_mesh));
  memcpy(
    object->_materials,
    GetMeshMaterial(object->_mesh, 0), 
    sizeof(Material) * GetNumMeshBuffers(object->_mesh));
}

EXPORT Object* CALL CreateObject(const struct SMemblock* memblock) {
  struct SMesh* mesh;
  Object* object;

  mesh = CreateMesh(memblock);
  if (!mesh) return NULL;
  
  object = _Alloc(Object);
  object->x = 0;
  object->y = 0;
  object->z = 0;
  object->pitch = 0;
  object->yaw = 0;
  object->roll = 0;
  object->sx = 1;
  object->sy = 1;
  object->sz = 1;
  object->billboard = BILLBOARD_NONE;
  object->colmode = COL_NONE;
  object->radius = 0;
  object->animmode = ANIM_STOP;
  object->animspeed = 1;
  object->animframe = 0;
  object->animmin = 0;
  object->animmax = 0;
  object->_mesh = mesh;
  object->_materials = NULL;
  RebuildObjectMesh(object);
  _SetObjectMaterials(object);
  return object;
}

EXPORT Object* CALL CreateCube() {
  Object* object;
  struct SMesh* mesh;
  int buffer;

  object = CreateObject(NULL);
  mesh = object->_mesh;
  buffer = AddMeshBuffer(mesh);

  /* add front face */
  AddMeshVertex(mesh, buffer, -0.5f,  0.5f, -0.5f, 0, 0, -1, 0, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f,  0.5f, -0.5f, 0, 0, -1, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 0, 0, -1, 1, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, -1, 0, 1, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 0, 1, 2);
  AddMeshTriangle(mesh, buffer, 0, 2, 3);

  /* add right face */
  AddMeshVertex(mesh, buffer,  0.5f,  0.5f, -0.5f, 1, 0, 0, 0, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f,  0.5f,  0.5f, 1, 0, 0, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f,  0.5f, 1, 0, 0, 1, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 1, 0, 0, 0, 1, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 4, 5, 6);
  AddMeshTriangle(mesh, buffer, 4, 6, 7);

  /* add back face */
  AddMeshVertex(mesh, buffer,  0.5f,  0.5f, 0.5f, 0, 0, 1, 0, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f,  0.5f, 0.5f, 0, 0, 1, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f, 0.5f, 0, 0, 1, 1, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f, 0.5f, 0, 0, 1, 0, 1, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 8, 9, 10);
  AddMeshTriangle(mesh, buffer, 8, 10, 11);

  /* add left face */
  AddMeshVertex(mesh, buffer, -0.5f,  0.5f,  0.5f, -1, 0, 0, 0, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f,  0.5f, -0.5f, -1, 0, 0, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f, -0.5f, -1, 0, 0, 1, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f,  0.5f, -1, 0, 0, 0, 1, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 12, 13, 14);
  AddMeshTriangle(mesh, buffer, 12, 14, 15);

  /* add top face */
  AddMeshVertex(mesh, buffer, -0.5f, 0.5f,  0.5f, 0, 1, 0, 0, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, 0.5f,  0.5f, 0, 1, 0, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, 0.5f, -0.5f, 0, 1, 0, 1, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, 0.5f, -0.5f, 0, 1, 0, 0, 1, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 16, 17, 18);
  AddMeshTriangle(mesh, buffer, 16, 18, 19);

  /* add bottom face */
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, -1, 0, 0, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 0, -1, 0, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f,  0.5f, 0, -1, 0, 1, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f,  0.5f, 0, -1, 0, 0, 1, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 20, 21, 22);
  AddMeshTriangle(mesh, buffer, 20, 22, 23);

  RebuildObjectMesh(object);
  _SetObjectMaterials(object);
  return object;
}

EXPORT Object* CALL CreateQuad() {
  Object* object;
  struct SMesh* mesh;
  int buffer;

  object = CreateObject(NULL);
  mesh = object->_mesh;
  buffer = AddMeshBuffer(mesh);

  AddMeshVertex(mesh, buffer, -0.5f,  0.5f, 0, 0, 0, -1, 0, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f,  0.5f, 0, 0, 0, -1, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f, 0, 0, 0, -1, 1, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 1, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 0, 1, 2);
  AddMeshTriangle(mesh, buffer, 0, 2, 3);

  /* set object materials */
  _SetObjectMaterials(object);

  return object;
}

EXPORT Object* CALL CreateTriangle() {
  Object* object;
  struct SMesh* mesh;
  int buffer;

  object = CreateObject(NULL);
  mesh = object->_mesh;
  buffer = AddMeshBuffer(mesh);

  AddMeshVertex(mesh, buffer,     0,  0.5f, 0, 0, 0, -1, 0.5f, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f, 0, 0, 0, -1, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 0, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 0, 1, 2);

  RebuildObjectMesh(object);
  _SetObjectMaterials(object);
  return object;
}

EXPORT Object* CALL LoadObject(const char* filename) {
  struct SMemblock* memblock;
  Object* object = NULL;

  memblock = LoadMemblock(filename);
  if (memblock) {
    object = CreateObject(memblock);
    DeleteMemblock(memblock);
  }

  return object;
}

EXPORT Object* CALL CloneObject(const Object* object) {
  Object* new_object = CreateObject(NULL);
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
  memcpy(new_object->_materials, object->_materials, sizeof(Material) * sb_count(object->_materials));
  RetainMesh(object->_mesh);
  return new_object;
}

EXPORT void CALL DeleteObject(Object* object) {
  ReleaseMesh(object->_mesh);
  free(object);
}

EXPORT int CALL AddSurface(Object* object) {
  int buffer = AddMeshBuffer(object->_mesh);
  sb_add(object->_materials, 1);
  return buffer;
}

EXPORT int CALL GetNumSurfaces(Object* object) {
  return GetNumMeshBuffers(object->_mesh);
}

EXPORT int CALL AddVertex(Object* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color) {
  return AddMeshVertex(object->_mesh, buffer, x, y, z, nx, ny, nz, u, v, color);
}

EXPORT int CALL AddTriangle(Object* object, int buffer, int v0, int v1, int v2) {
  return AddMeshTriangle(object->_mesh, buffer, v0, v1, v2);
}

EXPORT void CALL RebuildObjectMesh(Object* object) {
  RebuildMesh(object->_mesh);
}

EXPORT Material* CALL GetObjectMaterial(Object* object, int index) {
  return &object->_materials[index];
}

EXPORT float CALL GetObjectWidth(const Object* object) {
  return GetMeshWidth(object->_mesh) * object->sx;
}

EXPORT float CALL GetObjectHeight(const Object* object) {
  return GetMeshHeight(object->_mesh) * object->sy;
}

EXPORT float CALL GetObjectDepth(const Object* object) {
  return GetMeshDepth(object->_mesh) * object->sz;
}

EXPORT float CALL GetObjectMinX(const Object* object) {
  return object->x + GetMeshBoxMinX(object->_mesh) * object->sx;
}

EXPORT float CALL GetObjectMinY(const Object* object) {
  return object->y + GetMeshBoxMinY(object->_mesh) * object->sy;
}

EXPORT float CALL GetObjectMinZ(const Object* object) {
  if (object->billboard == BILLBOARD_NONE)
    return object->z + GetMeshBoxMinZ(object->_mesh) * object->sz;
  else
    return GetObjectMinX(object);
}

EXPORT float CALL GetObjectMaxX(const Object* object) {
  return object->x + GetMeshBoxMaxX(object->_mesh) * object->sx;
}

EXPORT float CALL GetObjectMaxY(const Object* object) {
  return object->y + GetMeshBoxMaxY(object->_mesh) * object->sy;
}

EXPORT float CALL GetObjectMaxZ(const Object* object) {
  if (object->billboard == BILLBOARD_NONE)
    return object->z + GetMeshBoxMaxZ(object->_mesh) * object->sz;
  else
    return GetObjectMaxX(object);
}

EXPORT bool_t CALL MoveObject(Object* object, float x, float y, float z) {
  lvec3_t vec;
  bool_t collided = FALSE;

  /* transform movement by object's rotation */
  vec = lquat_mulvec3(lquat_fromeuler(lvec3_rad(lvec3(object->pitch, object->yaw, object->roll))), lvec3(x, y, z));

  /* move x and check collision boxes */
  object->x += vec.x;
  if (ObjectCollidesBoxes(object)) {
    collided = TRUE;
    object->x -= vec.x;
  }

  /* move y and check collision boxes */
  object->y += vec.y;
  if (ObjectCollidesBoxes(object)) {
    collided = TRUE;
    object->y -= vec.y;
  }

  /* move z and check collision boxes */
  object->z += vec.z;
  if (ObjectCollidesBoxes(object)) {
    collided = TRUE;
    object->z -= vec.z;
  }

  return collided;
}

EXPORT void CALL TurnObject(Object* object, float pitch, float yaw, float roll) {
  lvec3_t vec;

  vec = lvec3_add(lvec3(object->pitch, object->yaw, object->roll), lvec3(pitch, yaw, roll));
  object->pitch = vec.x;
  object->yaw = vec.y;
  object->roll = vec.z;
}

EXPORT bool_t CALL ObjectCollidesBoxes(Object* object) {
  if (object->colmode == COL_SPHERE) {
    return _CheckSphereCol(object->x, object->y, object->z, object->radius * object->radius);
  } else if (object->colmode == COL_BOX) {
    return _CheckBoxCol(
      GetObjectMinX(object), GetObjectMinY(object), GetObjectMinZ(object),
      GetObjectMaxX(object), GetObjectMaxY(object), GetObjectMaxZ(object)
    );
  } else {
    return FALSE;
  }
}

EXPORT bool_t CALL ObjectCollidesObject(Object* object, Object* object2) {
  if (object != object2 && object->colmode != COL_NONE && object2->colmode != COL_NONE) {
    if (object->colmode == COL_SPHERE && object2->colmode == COL_SPHERE) {
      return lcol_spheresphere(
        object->x, object->y, object->z, object->radius * object->radius,
        object2->x, object2->y, object2->z, object2->radius * object2->radius
      ) == 1;
    } else if (object->colmode == COL_SPHERE && object2->colmode == COL_BOX) {
      return lcol_boxsphere(
        GetObjectMinX(object2), GetObjectMinY(object2), GetObjectMinZ(object2),
        GetObjectMaxX(object2), GetObjectMaxY(object2), GetObjectMaxZ(object2),
        object->x, object->y, object->z, object->radius * object->radius
      ) == 1;
    } else if (object->colmode == COL_BOX && object2->colmode == COL_SPHERE) {
      return lcol_boxsphere(
        GetObjectMinX(object), GetObjectMinY(object), GetObjectMinZ(object),
        GetObjectMaxX(object), GetObjectMaxY(object), GetObjectMaxZ(object),
        object2->x, object2->y, object2->z, object2->radius * object2->radius
      ) == 1;
    } else if (object->colmode == COL_BOX && object2->colmode == COL_BOX) {
      return lcol_boxbox(
        GetObjectMinX(object), GetObjectMinY(object), GetObjectMinZ(object),
        GetObjectMaxX(object), GetObjectMaxY(object), GetObjectMaxZ(object),
        GetObjectMinX(object2), GetObjectMinY(object2), GetObjectMinZ(object2),
        GetObjectMaxX(object2), GetObjectMaxY(object2), GetObjectMaxZ(object2)
      ) == 1;
    } else {
      return FALSE; /* should not get here */
    }
  } else {
    return FALSE;
  }
}

EXPORT void CALL DrawObject(Object* object) {
  lmat4_t modelview;

  /* calculate animation */
  if (object->animmode != ANIM_STOP) {
    int lastframe = (object->animmax != 0) ? object->animmax : _GetMeshLastFrame(object->_mesh);
    object->animframe += object->animspeed * _object_animfps * GetDeltaTime();
    if (object->animframe > lastframe) {
      if (object->animmode == ANIM_LOOP) object->animframe -= (lastframe - object->animmin);
      else object->animframe = lastframe;
    }
    if (object->animframe < object->animmin) {
      if (object->animmode == ANIM_LOOP) object->animframe += (lastframe - object->animmin);
      else object->animframe = object->animmin;
    }
    _AnimateMesh(object->_mesh, object->animframe);
    RebuildMesh(object->_mesh);
  } else if (object->animframe != 0) {
    _AnimateMesh(object->_mesh, 0);
    RebuildMesh(object->_mesh);
    object->animframe = 0;
  }

  /* calculate modelview */
  switch (object->billboard) {
    case BILLBOARD_NONE:
      modelview = lmat4_transform(
        lvec3(object->x, object->y, object->z),
        lquat_fromeuler(lvec3_rad(lvec3(object->pitch, object->yaw, object->roll))),
        lvec3(object->sx, object->sy, object->sz));
      break;
    default:
      modelview = lmat4_billboard(
        *(const lmat4_t*)_GetActiveMatrix(),
        lvec3(object->x, object->y, object->z),
        lm_deg2rad(object->roll),
        object->sx, object->sy,
        object->billboard == BILLBOARD_UPRIGHT ? TRUE : FALSE);
      break;
  }
  modelview = lmat4_mul(*(const lmat4_t*)_GetActiveMatrix(), modelview);
  lgfx_setmodelview(modelview.m);

  /* set properties & draw */
  _DrawMesh(object->_mesh, object->_materials);
}

EXPORT int CALL GetObjectNumFrames(const Object* object) {
  return _GetMeshLastFrame(object->_mesh);
}

EXPORT void CALL object_setanimfps(float fps) {
  _object_animfps = fps;
}

EXPORT float CALL GetObjectFPS() {
  return _object_animfps;
}
