#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "types.h"

#define ANIM_STOP 0
#define ANIM_PLAY 1
#define ANIM_LOOP 2

#define BILLBOARD_NONE 0
#define BILLBOARD_FACE 1
#define BILLBOARD_UPRIGHT 2

#define COL_NONE 0
#define COL_SPHERE 1
#define COL_BOX 2

#ifdef __cplusplus
extern "C" {
#endif

struct SMaterial;
struct SMemblock;
struct SMesh;

typedef struct {
  float x, y, z;
  float pitch, yaw, roll;
  float sx, sy, sz;
  int   billboard;
  int   colmode;
  float radius;
  int   animmode;
  float animspeed;
  float animframe;
  int   animmin;
  int   animmax;
#ifndef SWIG
  struct SMesh*     _mesh;
  struct SMaterial* _materials;
#endif
} Object;

EXPORT Object* CALL CreateObject(const struct SMemblock* memblock);
EXPORT Object* CALL CreateCube();
EXPORT Object* CALL CreateQuad();
EXPORT Object* CALL CreateTriangle();
EXPORT Object* CALL LoadObject(const char* filename);
EXPORT Object* CALL CloneObject(const Object* object);
EXPORT void CALL DeleteObject(Object* object);
EXPORT int CALL AddSurface(Object* object);
EXPORT int CALL GetNumSurfaces(Object* object);
EXPORT int CALL AddVertex(Object* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
EXPORT int CALL AddTriangle(Object* object, int buffer, int v0, int v1, int v2);
EXPORT void CALL RebuildObjectMesh(Object* object);
EXPORT struct SMaterial* CALL GetObjectMaterial(Object* object, int index);
EXPORT float CALL GetObjectWidth(const Object* object);
EXPORT float CALL GetObjectHeight(const Object* object);
EXPORT float CALL GetObjectDepth(const Object* object);
EXPORT float CALL GetObjectMinX(const Object* object);
EXPORT float CALL GetObjectMinY(const Object* object);
EXPORT float CALL GetObjectMinZ(const Object* object);
EXPORT float CALL GetObjectMaxX(const Object* object);
EXPORT float CALL GetObjectMaxY(const Object* object);
EXPORT float CALL GetObjectMaxZ(const Object* object);
EXPORT bool_t CALL MoveObject(Object* object, float x, float y, float z);
EXPORT void CALL TurnObject(Object* object, float pitch, float yaw, float roll);
EXPORT bool_t CALL ObjectCollidesBoxes(Object* object);
EXPORT bool_t CALL ObjectCollidesObject(Object* object, Object* object2);
EXPORT void CALL DrawObject(Object* object);
EXPORT int CALL GetObjectNumFrames(const Object* object);
EXPORT void CALL object_setanimfps(float fps);
EXPORT float CALL GetObjectFPS();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* OBJECT_H_INCLUDED */
