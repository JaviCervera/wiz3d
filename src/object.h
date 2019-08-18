#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "types.h"

#define ANIM_STOP 0
#define ANIM_PLAY 1
#define ANIM_LOOP 2

#define COL_NONE 0
#define COL_SPHERE 1
#define COL_BOX 2

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Object* CALL CreateObject(const Memblock* memblock);
EXPORT Object* CALL CreateCube();
EXPORT Object* CALL CreateQuad();
EXPORT Object* CALL CreateTriangle();
EXPORT Object* CALL LoadObject(const char* filename);
EXPORT Object* CALL CloneObject(const Object* object);
EXPORT void CALL DeleteObject(Object* object);
EXPORT float CALL GetObjectX(const Object* object);
EXPORT float CALL GetObjectY(const Object* object);
EXPORT float CALL GetObjectZ(const Object* object);
EXPORT void CALL SetObjectPosition(Object* object, float x, float y, float z);
EXPORT bool_t CALL MoveObject(Object* object, float x, float y, float z);
EXPORT float CALL GetObjectPitch(const Object* object);
EXPORT float CALL GetObjectYaw(const Object* object);
EXPORT float CALL GetObjectRoll(const Object* object);
EXPORT void CALL SetObjectRotation(Object* object, float pitch, float yaw, float roll);
EXPORT void CALL TurnObject(Object* object, float pitch, float yaw, float roll);
EXPORT void CALL ObjectLookAt(Object* object, float x, float y, float z);
EXPORT float CALL GetObjectScaleX(const Object* object);
EXPORT float CALL GetObjectScaleY(const Object* object);
EXPORT float CALL GetObjectScaleZ(const Object* object);
EXPORT float CALL GetObjectWidth(const Object* object);
EXPORT float CALL GetObjectHeight(const Object* object);
EXPORT float CALL GetObjectDepth(const Object* object);
EXPORT float CALL GetObjectMinX(const Object* object);
EXPORT float CALL GetObjectMinY(const Object* object);
EXPORT float CALL GetObjectMinZ(const Object* object);
EXPORT float CALL GetObjectMaxX(const Object* object);
EXPORT float CALL GetObjectMaxY(const Object* object);
EXPORT float CALL GetObjectMaxZ(const Object* object);
EXPORT void CALL SetObjectScale(Object* object, float sx, float sy, float sz);
EXPORT int CALL GetObjectCollision(const Object* object);
EXPORT void CALL SetObjectCollision(Object* object, int mode);
EXPORT float CALL GetObjectRadius(const Object* object);
EXPORT void CALL SetObjectRadius(Object* object, float radius);
EXPORT bool_t CALL ObjectCollidesBoxes(Object* object);
EXPORT bool_t CALL ObjectCollidesObject(Object* object, Object* object2);
EXPORT int CALL GetObjectAnimMode(const Object* object);
EXPORT void CALL SetObjectAnimMode(Object* object, int mode);
EXPORT float CALL GetObjectAnimSpeed(const Object* object);
EXPORT void CALL SetObjectAnimSpeed(Object* object, float speed);
EXPORT int CALL GetObjectFrame(const Object* object);
EXPORT void CALL SetObjectFrame(Object* object, int frame);
EXPORT int CALL GetObjectMinFrame(const Object* object);
EXPORT int CALL GetObjectMaxFrame(const Object* object);
EXPORT void CALL SetObjectAnimRange(Object* object, int min, int max);
EXPORT int CALL GetObjectNumFrames(const Object* object);
EXPORT int CALL AddSurface(Object* object);
EXPORT int CALL GetNumSurfaces(Object* object);
EXPORT int CALL AddVertex(Object* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
EXPORT int CALL AddTriangle(Object* object, int buffer, int v0, int v1, int v2);
EXPORT void CALL RebuildObjectMesh(Object* object);
EXPORT Material* CALL GetObjectMaterial(Object* object, int index);
EXPORT void CALL DrawObject(Object* object);

EXPORT float CALL GetDefaultAnimFPS();
EXPORT void CALL SetDefaultAnimFPS(float fps);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* OBJECT_H_INCLUDED */
