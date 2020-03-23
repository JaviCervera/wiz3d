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

EXPORT Object* CALL wzCreateObject(const Memblock* memblock);
EXPORT Object* CALL wzCreateCube();
EXPORT Object* CALL wzCreateQuad();
EXPORT Object* CALL wzCreateTriangle();
EXPORT Object* CALL wzLoadObject(const char* filename);
EXPORT Object* CALL wzCloneObject(const Object* object);
EXPORT void CALL wzDeleteObject(Object* object);
EXPORT float CALL wzGetObjectX(const Object* object);
EXPORT float CALL wzGetObjectY(const Object* object);
EXPORT float CALL wzGetObjectZ(const Object* object);
EXPORT void CALL wzSetObjectPosition(Object* object, float x, float y, float z);
EXPORT bool_t CALL wzMoveObject(Object* object, float x, float y, float z);
EXPORT float CALL wzGetObjectPitch(const Object* object);
EXPORT float CALL wzGetObjectYaw(const Object* object);
EXPORT float CALL wzGetObjectRoll(const Object* object);
EXPORT void CALL wzSetObjectRotation(Object* object, float pitch, float yaw, float roll);
EXPORT void CALL wzTurnObject(Object* object, float pitch, float yaw, float roll);
EXPORT void CALL wzObjectLookAt(Object* object, float x, float y, float z);
EXPORT float CALL wzGetObjectScaleX(const Object* object);
EXPORT float CALL wzGetObjectScaleY(const Object* object);
EXPORT float CALL wzGetObjectScaleZ(const Object* object);
EXPORT float CALL wzGetObjectWidth(const Object* object);
EXPORT float CALL wzGetObjectHeight(const Object* object);
EXPORT float CALL wzGetObjectDepth(const Object* object);
EXPORT float CALL wzGetObjectMinX(const Object* object);
EXPORT float CALL wzGetObjectMinY(const Object* object);
EXPORT float CALL wzGetObjectMinZ(const Object* object);
EXPORT float CALL wzGetObjectMaxX(const Object* object);
EXPORT float CALL wzGetObjectMaxY(const Object* object);
EXPORT float CALL wzGetObjectMaxZ(const Object* object);
EXPORT void CALL wzSetObjectScale(Object* object, float sx, float sy, float sz);
EXPORT int CALL wzGetObjectCollision(const Object* object);
EXPORT void CALL wzSetObjectCollision(Object* object, int mode);
EXPORT float CALL wzGetObjectRadius(const Object* object);
EXPORT void CALL wzSetObjectRadius(Object* object, float radius);
EXPORT bool_t CALL wzObjectCollidesBoxes(Object* object);
EXPORT bool_t CALL wzObjectCollidesObject(Object* object, Object* object2);
EXPORT int CALL wzGetObjectAnimMode(const Object* object);
EXPORT void CALL wzSetObjectAnimMode(Object* object, int mode);
EXPORT float CALL wzGetObjectAnimSpeed(const Object* object);
EXPORT void CALL wzSetObjectAnimSpeed(Object* object, float speed);
EXPORT int CALL wzGetObjectFrame(const Object* object);
EXPORT void CALL wzSetObjectFrame(Object* object, int frame);
EXPORT int CALL wzGetObjectMinFrame(const Object* object);
EXPORT int CALL wzGetObjectMaxFrame(const Object* object);
EXPORT void CALL wzSetObjectAnimRange(Object* object, int min, int max);
EXPORT int CALL wzGetObjectNumFrames(const Object* object);
EXPORT int CALL wzAddSurface(Object* object);
EXPORT int CALL wzGetNumSurfaces(Object* object);
EXPORT int CALL wzAddVertex(Object* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
EXPORT int CALL wzAddTriangle(Object* object, int buffer, int v0, int v1, int v2);
EXPORT void CALL wzRebuildObjectMesh(Object* object);
EXPORT Material* CALL wzGetObjectMaterial(Object* object, int index);
EXPORT void CALL wzDrawObject(Object* object);

EXPORT float CALL wzGetDefaultAnimFPS();
EXPORT void CALL wzSetDefaultAnimFPS(float fps);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* OBJECT_H_INCLUDED */
