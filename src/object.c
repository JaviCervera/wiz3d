#include "../lib/litelibs/litecol.h"
#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "../lib/stb/stretchy_buffer.h"
#include "colbox.h"
#include "color.h"
#include "material.h"
#include "material_internal.h"
#include "memblock.h"
#include "mesh.h"
#include "object.h"
#include "screen.h"
#include "texture.h"
#include "time.h"
#include "util.h"
#include "viewer.h"
#include <math.h>
#include <string.h>

typedef struct SObject {
  float x, y, z;
  float pitch, yaw, roll;
  float sx, sy, sz;
  int   colmode;
  float radius;
  int   animmode;
  float animspeed;
  float animframe;
  int   animmin;
  int   animmax;
  Mesh* _mesh;
  Material* _materials;
} Object;

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

EXPORT Object* CALL spCreateObject(const Memblock* memblock) {
  Mesh* mesh;
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
  object->colmode = COL_NONE;
  object->radius = 0;
  object->animmode = ANIM_STOP;
  object->animspeed = 1;
  object->animframe = 0;
  object->animmin = 0;
  object->animmax = 0;
  object->_mesh = mesh;
  object->_materials = NULL;
  spRebuildObjectMesh(object);
  _SetObjectMaterials(object);
  return object;
}

EXPORT Object* CALL spCreateCube() {
  Object* object;
  Mesh* mesh;
  int buffer;

  object = spCreateObject(NULL);
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

  spRebuildObjectMesh(object);
  _SetObjectMaterials(object);
  return object;
}

EXPORT Object* CALL spCreateQuad() {
  Object* object;
  Mesh* mesh;
  int buffer;

  object = spCreateObject(NULL);
  mesh = object->_mesh;
  buffer = AddMeshBuffer(mesh);

  AddMeshVertex(mesh, buffer, -0.5f,  0.5f, 0, 0, 0, -1, 0, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f,  0.5f, 0, 0, 0, -1, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f, 0, 0, 0, -1, 1, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 1, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 0, 1, 2);
  AddMeshTriangle(mesh, buffer, 0, 2, 3);

  /* set object materials */
  spRebuildObjectMesh(object);
  _SetObjectMaterials(object);

  return object;
}

EXPORT Object* CALL spCreateTriangle() {
  Object* object;
  Mesh* mesh;
  int buffer;

  object = spCreateObject(NULL);
  mesh = object->_mesh;
  buffer = AddMeshBuffer(mesh);

  AddMeshVertex(mesh, buffer,     0,  0.5f, 0, 0, 0, -1, 0.5f, 1, COLOR_WHITE);
  AddMeshVertex(mesh, buffer,  0.5f, -0.5f, 0, 0, 0, -1, 1, 0, COLOR_WHITE);
  AddMeshVertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 0, COLOR_WHITE);
  AddMeshTriangle(mesh, buffer, 0, 1, 2);

  spRebuildObjectMesh(object);
  _SetObjectMaterials(object);
  return object;
}

EXPORT Object* CALL spLoadObject(const char* filename) {
  Memblock* memblock;
  Object* object = NULL;

  memblock = spLoadMemblock(filename);
  if (memblock) {
    object = spCreateObject(memblock);
    spDeleteMemblock(memblock);
  }

  return object;
}

EXPORT Object* CALL spCloneObject(const Object* object) {
  Object* new_object = spCreateObject(NULL);
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

EXPORT void CALL spDeleteObject(Object* object) {
  ReleaseMesh(object->_mesh);
  free(object);
}

EXPORT float CALL spGetObjectX(const Object* object) { return object->x; }

EXPORT float CALL spGetObjectY(const Object* object) { return object->y; }

EXPORT float CALL spGetObjectZ(const Object* object) { return object->z; }

EXPORT void CALL spSetObjectPosition(Object* object, float x, float y, float z) {
  object->x = x;
  object->y = y;
  object->z = z;
}

EXPORT bool_t CALL spMoveObject(Object* object, float x, float y, float z) {
  lvec3_t vec;
  bool_t collided = FALSE;

  /* transform movement by object's rotation */
  vec = lquat_mulvec3(lquat_fromeuler(lvec3_rad(lvec3(object->pitch, object->yaw, object->roll))), lvec3(x, y, z));

  /* move x and check collision boxes */
  object->x += vec.x;
  if (spObjectCollidesBoxes(object)) {
    collided = TRUE;
    object->x -= vec.x;
  }

  /* move y and check collision boxes */
  object->y += vec.y;
  if (spObjectCollidesBoxes(object)) {
    collided = TRUE;
    object->y -= vec.y;
  }

  /* move z and check collision boxes */
  object->z += vec.z;
  if (spObjectCollidesBoxes(object)) {
    collided = TRUE;
    object->z -= vec.z;
  }

  return collided;
}

EXPORT float CALL spGetObjectPitch(const Object* object) { return object->pitch; }

EXPORT float CALL spGetObjectYaw(const Object* object) { return object->yaw; }

EXPORT float CALL spGetObjectRoll(const Object* object) { return object->roll; }

EXPORT void CALL spSetObjectRotation(Object* object, float pitch, float yaw, float roll) {
  object->pitch = pitch;
  object->yaw = yaw;
  object->roll = roll;
}

EXPORT void CALL spTurnObject(Object* object, float pitch, float yaw, float roll) {
  lvec3_t vec;

  vec = lvec3_add(lvec3(object->pitch, object->yaw, object->roll), lvec3(pitch, yaw, roll));
  object->pitch = vec.x;
  object->yaw = vec.y;
  object->roll = vec.z;
}

EXPORT void CALL spObjectLookAt(Object* object, float x, float y, float z) {
  lvec3_t dir;
  dir = lvec3_norm(lvec3_sub(lvec3(object->x, object->y, object->z), lvec3(x, y, z)));
  object->pitch = lm_rad2deg((float)asin(-dir.y));
  object->yaw = lm_rad2deg((float)atan2(dir.x, dir.z));
}

EXPORT float CALL spGetObjectScaleX(const Object* object) { return object->sx; }

EXPORT float CALL spGetObjectScaleY(const Object* object) { return object->sy; }

EXPORT float CALL spGetObjectScaleZ(const Object* object) { return object->sz; }

EXPORT float CALL spGetObjectWidth(const Object* object) { return GetMeshWidth(object->_mesh) * object->sx; }

EXPORT float CALL spGetObjectHeight(const Object* object) { return GetMeshHeight(object->_mesh) * object->sy; }

EXPORT float CALL spGetObjectDepth(const Object* object) { return GetMeshDepth(object->_mesh) * object->sz; }

EXPORT float CALL spGetObjectMinX(const Object* object) { return object->x + GetMeshBoxMinX(object->_mesh) * object->sx; }

EXPORT float CALL spGetObjectMinY(const Object* object) { return object->y + GetMeshBoxMinY(object->_mesh) * object->sy; }

EXPORT float CALL spGetObjectMinZ(const Object* object) { return object->z + GetMeshBoxMinZ(object->_mesh) * object->sz; }

EXPORT float CALL spGetObjectMaxX(const Object* object) { return object->x + GetMeshBoxMaxX(object->_mesh) * object->sx; }

EXPORT float CALL spGetObjectMaxY(const Object* object) { return object->y + GetMeshBoxMaxY(object->_mesh) * object->sy; }

EXPORT float CALL spGetObjectMaxZ(const Object* object) { return object->z + GetMeshBoxMaxZ(object->_mesh) * object->sz; }

EXPORT void CALL spSetObjectScale(Object* object, float sx, float sy, float sz) {
  object->sx = sx;
  object->sy = sy;
  object->sz = sz;
}

EXPORT int CALL spGetObjectCollision(const Object* object) { return object->colmode; }

EXPORT void CALL spSetObjectCollision(Object* object, int mode) { object->colmode = _Clamp(mode, COL_NONE, COL_BOX); }

EXPORT float CALL spGetObjectRadius(const Object* object) { return object->radius; }

EXPORT void CALL spSetObjectRadius(Object* object, float radius) { object->radius = radius; }

EXPORT bool_t CALL spObjectCollidesBoxes(Object* object) {
  if (object->colmode == COL_SPHERE) {
    return _CheckSphereCol(object->x, object->y, object->z, object->radius * object->radius);
  } else if (object->colmode == COL_BOX) {
    return _CheckBoxCol(
      spGetObjectMinX(object), spGetObjectMinY(object), spGetObjectMinZ(object),
      spGetObjectMaxX(object), spGetObjectMaxY(object), spGetObjectMaxZ(object)
    );
  } else {
    return FALSE;
  }
}

EXPORT bool_t CALL spObjectCollidesObject(Object* object, Object* object2) {
  if (object != object2 && object->colmode != COL_NONE && object2->colmode != COL_NONE) {
    if (object->colmode == COL_SPHERE && object2->colmode == COL_SPHERE) {
      return lcol_spheresphere(
        object->x, object->y, object->z, object->radius * object->radius,
        object2->x, object2->y, object2->z, object2->radius * object2->radius
      ) == 1;
    } else if (object->colmode == COL_SPHERE && object2->colmode == COL_BOX) {
      return lcol_boxsphere(
        spGetObjectMinX(object2), spGetObjectMinY(object2), spGetObjectMinZ(object2),
        spGetObjectMaxX(object2), spGetObjectMaxY(object2), spGetObjectMaxZ(object2),
        object->x, object->y, object->z, object->radius * object->radius
      ) == 1;
    } else if (object->colmode == COL_BOX && object2->colmode == COL_SPHERE) {
      return lcol_boxsphere(
        spGetObjectMinX(object), spGetObjectMinY(object), spGetObjectMinZ(object),
        spGetObjectMaxX(object), spGetObjectMaxY(object), spGetObjectMaxZ(object),
        object2->x, object2->y, object2->z, object2->radius * object2->radius
      ) == 1;
    } else if (object->colmode == COL_BOX && object2->colmode == COL_BOX) {
      return lcol_boxbox(
        spGetObjectMinX(object), spGetObjectMinY(object), spGetObjectMinZ(object),
        spGetObjectMaxX(object), spGetObjectMaxY(object), spGetObjectMaxZ(object),
        spGetObjectMinX(object2), spGetObjectMinY(object2), spGetObjectMinZ(object2),
        spGetObjectMaxX(object2), spGetObjectMaxY(object2), spGetObjectMaxZ(object2)
      ) == 1;
    } else {
      return FALSE; /* should not get here */
    }
  } else {
    return FALSE;
  }
}

EXPORT int CALL spGetObjectAnimMode(const Object* object) { return object->animmode; }

EXPORT void CALL spSetObjectAnimMode(Object* object, int mode) { object->animmode = _Clamp(mode, ANIM_STOP, ANIM_LOOP); }

EXPORT float CALL spGetObjectAnimSpeed(const Object* object) { return object->animspeed; }

EXPORT void CALL spSetObjectAnimSpeed(Object* object, float speed) { object->animspeed = speed; }

EXPORT int CALL spGetObjectFrame(const Object* object) { return object->animframe; }

EXPORT void CALL spSetObjectFrame(Object* object, int frame) { object->animframe = frame; }

EXPORT int CALL spGetObjectMinFrame(const Object* object) { return object->animmin; }

EXPORT int CALL spGetObjectMaxFrame(const Object* object) { return object->animmax; }

EXPORT void CALL spSetObjectAnimRange(Object* object, int min, int max) {
  object->animmin = min;
  object->animmax = max;
}

EXPORT int CALL spGetObjectNumFrames(const Object* object) { return _GetMeshLastFrame(object->_mesh); }

EXPORT int CALL spAddSurface(Object* object) {
  int buffer = AddMeshBuffer(object->_mesh);
  sb_add(object->_materials, 1);
  return buffer;
}

EXPORT int CALL spGetNumSurfaces(Object* object) { return GetNumMeshBuffers(object->_mesh); }

EXPORT int CALL spAddVertex(Object* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color) {
  return AddMeshVertex(object->_mesh, buffer, x, y, z, nx, ny, nz, u, v, color);
}

EXPORT int CALL spAddTriangle(Object* object, int buffer, int v0, int v1, int v2) {
  return AddMeshTriangle(object->_mesh, buffer, v0, v1, v2);
}

EXPORT void CALL spRebuildObjectMesh(Object* object) { RebuildMesh(object->_mesh); }

EXPORT Material* CALL spGetObjectMaterial(Object* object, int index) { return &object->_materials[index]; }

EXPORT void CALL spDrawObject(Object* object) {
  lmat4_t modelview;

  /* calculate animation */
  if (object->animmode != ANIM_STOP) {
    int lastframe = (object->animmax != 0) ? object->animmax : _GetMeshLastFrame(object->_mesh);
    object->animframe += object->animspeed * _object_animfps * spGetDeltaTime();
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
  modelview = lmat4_transform(
    lvec3(object->x, object->y, object->z),
    lquat_fromeuler(lvec3_rad(lvec3(object->pitch, object->yaw, object->roll))),
    lvec3(object->sx, object->sy, object->sz));
  modelview = lmat4_mul(*(const lmat4_t*)_GetActiveMatrix(), modelview);
  lgfx_setmodelview(modelview.m);

  /* set properties & draw */
  _DrawMesh(object->_mesh, object->_materials);
}

EXPORT float CALL spGetDefaultAnimFPS() { return _object_animfps; }

EXPORT void CALL spSetDefaultAnimFPS(float fps) { _object_animfps = fps; }
