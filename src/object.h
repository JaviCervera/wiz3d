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

EXPORT Object* CALL bmCreateObject(const Memblock* memblock);
EXPORT Object* CALL bmCreateCube();
EXPORT Object* CALL bmCreateQuad();
EXPORT Object* CALL bmCreateTriangle();
EXPORT Object* CALL bmLoadObject(const char* filename);
EXPORT Object* CALL bmCloneObject(const Object* object);
EXPORT void CALL bmDeleteObject(Object* object);
EXPORT float CALL bmGetObjectX(const Object* object);
EXPORT float CALL bmGetObjectY(const Object* object);
EXPORT float CALL bmGetObjectZ(const Object* object);
EXPORT void CALL bmSetObjectPosition(Object* object, float x, float y, float z);
EXPORT bool_t CALL bmMoveObject(Object* object, float x, float y, float z);
EXPORT float CALL bmGetObjectPitch(const Object* object);
EXPORT float CALL bmGetObjectYaw(const Object* object);
EXPORT float CALL bmGetObjectRoll(const Object* object);
EXPORT void CALL bmSetObjectRotation(Object* object, float pitch, float yaw, float roll);
EXPORT void CALL bmTurnObject(Object* object, float pitch, float yaw, float roll);
EXPORT void CALL bmObjectLookAt(Object* object, float x, float y, float z);
EXPORT float CALL bmGetObjectScaleX(const Object* object);
EXPORT float CALL bmGetObjectScaleY(const Object* object);
EXPORT float CALL bmGetObjectScaleZ(const Object* object);
EXPORT float CALL bmGetObjectWidth(const Object* object);
EXPORT float CALL bmGetObjectHeight(const Object* object);
EXPORT float CALL bmGetObjectDepth(const Object* object);
EXPORT float CALL bmGetObjectMinX(const Object* object);
EXPORT float CALL bmGetObjectMinY(const Object* object);
EXPORT float CALL bmGetObjectMinZ(const Object* object);
EXPORT float CALL bmGetObjectMaxX(const Object* object);
EXPORT float CALL bmGetObjectMaxY(const Object* object);
EXPORT float CALL bmGetObjectMaxZ(const Object* object);
EXPORT void CALL bmSetObjectScale(Object* object, float sx, float sy, float sz);
EXPORT int CALL bmGetObjectCollision(const Object* object);
EXPORT void CALL bmSetObjectCollision(Object* object, int mode);
EXPORT float CALL bmGetObjectRadius(const Object* object);
EXPORT void CALL bmSetObjectRadius(Object* object, float radius);
EXPORT bool_t CALL bmObjectCollidesBoxes(Object* object);
EXPORT bool_t CALL bmObjectCollidesObject(Object* object, Object* object2);
EXPORT int CALL bmGetObjectAnimMode(const Object* object);
EXPORT void CALL bmSetObjectAnimMode(Object* object, int mode);
EXPORT float CALL bmGetObjectAnimSpeed(const Object* object);
EXPORT void CALL bmSetObjectAnimSpeed(Object* object, float speed);
EXPORT int CALL bmGetObjectFrame(const Object* object);
EXPORT void CALL bmSetObjectFrame(Object* object, int frame);
EXPORT int CALL bmGetObjectMinFrame(const Object* object);
EXPORT int CALL bmGetObjectMaxFrame(const Object* object);
EXPORT void CALL bmSetObjectAnimRange(Object* object, int min, int max);
EXPORT int CALL bmGetObjectNumFrames(const Object* object);
EXPORT int CALL bmAddSurface(Object* object);
EXPORT int CALL bmGetNumSurfaces(Object* object);
EXPORT int CALL bmAddVertex(Object* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
EXPORT int CALL bmAddTriangle(Object* object, int buffer, int v0, int v1, int v2);
EXPORT void CALL bmRebuildObjectMesh(Object* object);
EXPORT Material* CALL bmGetObjectMaterial(Object* object, int index);
EXPORT void CALL bmDrawObject(Object* object);

EXPORT float CALL bmGetDefaultAnimFPS();
EXPORT void CALL bmSetDefaultAnimFPS(float fps);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* OBJECT_H_INCLUDED */
