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

EXPORT Object* CALL spCreateObject(const Memblock* memblock);
EXPORT Object* CALL spCreateCube();
EXPORT Object* CALL spCreateQuad();
EXPORT Object* CALL spCreateTriangle();
EXPORT Object* CALL spLoadObject(const char* filename);
EXPORT Object* CALL spCloneObject(const Object* object);
EXPORT void CALL spDeleteObject(Object* object);
EXPORT float CALL spGetObjectX(const Object* object);
EXPORT float CALL spGetObjectY(const Object* object);
EXPORT float CALL spGetObjectZ(const Object* object);
EXPORT void CALL spSetObjectPosition(Object* object, float x, float y, float z);
EXPORT bool_t CALL spMoveObject(Object* object, float x, float y, float z);
EXPORT float CALL spGetObjectPitch(const Object* object);
EXPORT float CALL spGetObjectYaw(const Object* object);
EXPORT float CALL spGetObjectRoll(const Object* object);
EXPORT void CALL spSetObjectRotation(Object* object, float pitch, float yaw, float roll);
EXPORT void CALL spTurnObject(Object* object, float pitch, float yaw, float roll);
EXPORT void CALL spObjectLookAt(Object* object, float x, float y, float z);
EXPORT float CALL spGetObjectScaleX(const Object* object);
EXPORT float CALL spGetObjectScaleY(const Object* object);
EXPORT float CALL spGetObjectScaleZ(const Object* object);
EXPORT float CALL spGetObjectWidth(const Object* object);
EXPORT float CALL spGetObjectHeight(const Object* object);
EXPORT float CALL spGetObjectDepth(const Object* object);
EXPORT float CALL spGetObjectMinX(const Object* object);
EXPORT float CALL spGetObjectMinY(const Object* object);
EXPORT float CALL spGetObjectMinZ(const Object* object);
EXPORT float CALL spGetObjectMaxX(const Object* object);
EXPORT float CALL spGetObjectMaxY(const Object* object);
EXPORT float CALL spGetObjectMaxZ(const Object* object);
EXPORT void CALL spSetObjectScale(Object* object, float sx, float sy, float sz);
EXPORT int CALL spGetObjectCollision(const Object* object);
EXPORT void CALL spSetObjectCollision(Object* object, int mode);
EXPORT float CALL spGetObjectRadius(const Object* object);
EXPORT void CALL spSetObjectRadius(Object* object, float radius);
EXPORT bool_t CALL spObjectCollidesBoxes(Object* object);
EXPORT bool_t CALL spObjectCollidesObject(Object* object, Object* object2);
EXPORT int CALL spGetObjectAnimMode(const Object* object);
EXPORT void CALL spSetObjectAnimMode(Object* object, int mode);
EXPORT float CALL spGetObjectAnimSpeed(const Object* object);
EXPORT void CALL spSetObjectAnimSpeed(Object* object, float speed);
EXPORT int CALL spGetObjectFrame(const Object* object);
EXPORT void CALL spSetObjectFrame(Object* object, int frame);
EXPORT int CALL spGetObjectMinFrame(const Object* object);
EXPORT int CALL spGetObjectMaxFrame(const Object* object);
EXPORT void CALL spSetObjectAnimRange(Object* object, int min, int max);
EXPORT int CALL spGetObjectNumFrames(const Object* object);
EXPORT int CALL spAddSurface(Object* object);
EXPORT int CALL spGetNumSurfaces(Object* object);
EXPORT int CALL spAddVertex(Object* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
EXPORT int CALL spAddTriangle(Object* object, int buffer, int v0, int v1, int v2);
EXPORT void CALL spRebuildObjectMesh(Object* object);
EXPORT Material* CALL spGetObjectMaterial(Object* object, int index);
EXPORT void CALL spDrawObject(Object* object);

EXPORT float CALL spGetDefaultAnimFPS();
EXPORT void CALL spSetDefaultAnimFPS(float fps);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* OBJECT_H_INCLUDED */
