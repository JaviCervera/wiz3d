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
    int     colmode;
    float radius;
    int     animmode;
    float animspeed;
    float animframe;
    int     animmin;
    int     animmax;
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

EXPORT Object* CALL wzCreateObject(const Memblock* memblock) {
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
    wzRebuildObjectMesh(object);
    _SetObjectMaterials(object);
    return object;
}

EXPORT Object* CALL wzCreateCube() {
    Object* object;
    Mesh* mesh;
    int buffer;

    object = wzCreateObject(NULL);
    mesh = object->_mesh;
    buffer = AddMeshBuffer(mesh);

    /* add front face */
    AddMeshVertex(mesh, buffer, -0.5f,    0.5f, -0.5f, 0, 0, -1, 0, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f,    0.5f, -0.5f, 0, 0, -1, 1, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, -0.5f, -0.5f, 0, 0, -1, 1, 1, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, -1, 0, 1, COLOR_WHITE);
    AddMeshTriangle(mesh, buffer, 0, 1, 2);
    AddMeshTriangle(mesh, buffer, 0, 2, 3);

    /* add right face */
    AddMeshVertex(mesh, buffer,    0.5f,    0.5f, -0.5f, 1, 0, 0, 0, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f,    0.5f,    0.5f, 1, 0, 0, 1, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, -0.5f,    0.5f, 1, 0, 0, 1, 1, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, -0.5f, -0.5f, 1, 0, 0, 0, 1, COLOR_WHITE);
    AddMeshTriangle(mesh, buffer, 4, 5, 6);
    AddMeshTriangle(mesh, buffer, 4, 6, 7);

    /* add back face */
    AddMeshVertex(mesh, buffer,    0.5f,    0.5f, 0.5f, 0, 0, 1, 0, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f,    0.5f, 0.5f, 0, 0, 1, 1, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f, -0.5f, 0.5f, 0, 0, 1, 1, 1, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, -0.5f, 0.5f, 0, 0, 1, 0, 1, COLOR_WHITE);
    AddMeshTriangle(mesh, buffer, 8, 9, 10);
    AddMeshTriangle(mesh, buffer, 8, 10, 11);

    /* add left face */
    AddMeshVertex(mesh, buffer, -0.5f,    0.5f,    0.5f, -1, 0, 0, 0, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f,    0.5f, -0.5f, -1, 0, 0, 1, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f, -0.5f, -0.5f, -1, 0, 0, 1, 1, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f, -0.5f,    0.5f, -1, 0, 0, 0, 1, COLOR_WHITE);
    AddMeshTriangle(mesh, buffer, 12, 13, 14);
    AddMeshTriangle(mesh, buffer, 12, 14, 15);

    /* add top face */
    AddMeshVertex(mesh, buffer, -0.5f, 0.5f,    0.5f, 0, 1, 0, 0, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, 0.5f,    0.5f, 0, 1, 0, 1, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, 0.5f, -0.5f, 0, 1, 0, 1, 1, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f, 0.5f, -0.5f, 0, 1, 0, 0, 1, COLOR_WHITE);
    AddMeshTriangle(mesh, buffer, 16, 17, 18);
    AddMeshTriangle(mesh, buffer, 16, 18, 19);

    /* add bottom face */
    AddMeshVertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, -1, 0, 0, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, -0.5f, -0.5f, 0, -1, 0, 1, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, -0.5f,    0.5f, 0, -1, 0, 1, 1, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f, -0.5f,    0.5f, 0, -1, 0, 0, 1, COLOR_WHITE);
    AddMeshTriangle(mesh, buffer, 20, 21, 22);
    AddMeshTriangle(mesh, buffer, 20, 22, 23);

    wzRebuildObjectMesh(object);
    _SetObjectMaterials(object);
    return object;
}

EXPORT Object* CALL wzCreateQuad() {
    Object* object;
    Mesh* mesh;
    int buffer;

    object = wzCreateObject(NULL);
    mesh = object->_mesh;
    buffer = AddMeshBuffer(mesh);

    AddMeshVertex(mesh, buffer, -0.5f,    0.5f, 0, 0, 0, -1, 0, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f,    0.5f, 0, 0, 0, -1, 1, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, -0.5f, 0, 0, 0, -1, 1, 1, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 1, COLOR_WHITE);
    AddMeshTriangle(mesh, buffer, 0, 1, 2);
    AddMeshTriangle(mesh, buffer, 0, 2, 3);

    /* set object materials */
    wzRebuildObjectMesh(object);
    _SetObjectMaterials(object);

    return object;
}

EXPORT Object* CALL wzCreateTriangle() {
    Object* object;
    Mesh* mesh;
    int buffer;

    object = wzCreateObject(NULL);
    mesh = object->_mesh;
    buffer = AddMeshBuffer(mesh);

    AddMeshVertex(mesh, buffer,         0,    0.5f, 0, 0, 0, -1, 0.5f, 1, COLOR_WHITE);
    AddMeshVertex(mesh, buffer,    0.5f, -0.5f, 0, 0, 0, -1, 1, 0, COLOR_WHITE);
    AddMeshVertex(mesh, buffer, -0.5f, -0.5f, 0, 0, 0, -1, 0, 0, COLOR_WHITE);
    AddMeshTriangle(mesh, buffer, 0, 1, 2);

    wzRebuildObjectMesh(object);
    _SetObjectMaterials(object);
    return object;
}

EXPORT Object* CALL wzLoadObject(const char* filename) {
    Memblock* memblock;
    Object* object = NULL;

    memblock = wzLoadMemblock(filename);
    if (memblock) {
        object = wzCreateObject(memblock);
        wzDeleteMemblock(memblock);
    }

    return object;
}

EXPORT Object* CALL wzCloneObject(const Object* object) {
    Object* new_object = wzCreateObject(NULL);
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

EXPORT void CALL wzDeleteObject(Object* object) {
    ReleaseMesh(object->_mesh);
    free(object);
}

EXPORT float CALL wzGetObjectX(const Object* object) { return object->x; }

EXPORT float CALL wzGetObjectY(const Object* object) { return object->y; }

EXPORT float CALL wzGetObjectZ(const Object* object) { return object->z; }

EXPORT void CALL wzSetObjectPosition(Object* object, float x, float y, float z) {
    object->x = x;
    object->y = y;
    object->z = z;
}

EXPORT bool_t CALL wzMoveObject(Object* object, float x, float y, float z) {
    lvec3_t vec;
    bool_t collided = FALSE;

    /* transform movement by object's rotation */
    vec = lquat_mulvec3(lquat_fromeuler(lvec3_rad(lvec3(object->pitch, object->yaw, object->roll))), lvec3(x, y, z));

    /* move x and check collision boxes */
    object->x += vec.x;
    if (wzObjectCollidesBoxes(object)) {
        collided = TRUE;
        object->x -= vec.x;
    }

    /* move y and check collision boxes */
    object->y += vec.y;
    if (wzObjectCollidesBoxes(object)) {
        collided = TRUE;
        object->y -= vec.y;
    }

    /* move z and check collision boxes */
    object->z += vec.z;
    if (wzObjectCollidesBoxes(object)) {
        collided = TRUE;
        object->z -= vec.z;
    }

    return collided;
}

EXPORT float CALL wzGetObjectPitch(const Object* object) { return object->pitch; }

EXPORT float CALL wzGetObjectYaw(const Object* object) { return object->yaw; }

EXPORT float CALL wzGetObjectRoll(const Object* object) { return object->roll; }

EXPORT void CALL wzSetObjectRotation(Object* object, float pitch, float yaw, float roll) {
    object->pitch = pitch;
    object->yaw = yaw;
    object->roll = roll;
}

EXPORT void CALL wzTurnObject(Object* object, float pitch, float yaw, float roll) {
    lvec3_t vec;

    vec = lvec3_add(lvec3(object->pitch, object->yaw, object->roll), lvec3(pitch, yaw, roll));
    object->pitch = vec.x;
    object->yaw = vec.y;
    object->roll = vec.z;
}

EXPORT void CALL wzObjectLookAt(Object* object, float x, float y, float z) {
    lvec3_t dir;
    dir = lvec3_norm(lvec3_sub(lvec3(object->x, object->y, object->z), lvec3(x, y, z)));
    object->pitch = lm_rad2deg((float)asin(-dir.y));
    object->yaw = lm_rad2deg((float)atan2(dir.x, dir.z));
}

EXPORT float CALL wzGetObjectScaleX(const Object* object) { return object->sx; }

EXPORT float CALL wzGetObjectScaleY(const Object* object) { return object->sy; }

EXPORT float CALL wzGetObjectScaleZ(const Object* object) { return object->sz; }

EXPORT float CALL wzGetObjectWidth(const Object* object) { return GetMeshWidth(object->_mesh) * object->sx; }

EXPORT float CALL wzGetObjectHeight(const Object* object) { return GetMeshHeight(object->_mesh) * object->sy; }

EXPORT float CALL wzGetObjectDepth(const Object* object) { return GetMeshDepth(object->_mesh) * object->sz; }

EXPORT float CALL wzGetObjectMinX(const Object* object) { return object->x + GetMeshBoxMinX(object->_mesh) * object->sx; }

EXPORT float CALL wzGetObjectMinY(const Object* object) { return object->y + GetMeshBoxMinY(object->_mesh) * object->sy; }

EXPORT float CALL wzGetObjectMinZ(const Object* object) { return object->z + GetMeshBoxMinZ(object->_mesh) * object->sz; }

EXPORT float CALL wzGetObjectMaxX(const Object* object) { return object->x + GetMeshBoxMaxX(object->_mesh) * object->sx; }

EXPORT float CALL wzGetObjectMaxY(const Object* object) { return object->y + GetMeshBoxMaxY(object->_mesh) * object->sy; }

EXPORT float CALL wzGetObjectMaxZ(const Object* object) { return object->z + GetMeshBoxMaxZ(object->_mesh) * object->sz; }

EXPORT void CALL wzSetObjectScale(Object* object, float sx, float sy, float sz) {
    object->sx = sx;
    object->sy = sy;
    object->sz = sz;
}

EXPORT int CALL wzGetObjectCollision(const Object* object) { return object->colmode; }

EXPORT void CALL wzSetObjectCollision(Object* object, int mode) { object->colmode = _Clamp(mode, COL_NONE, COL_BOX); }

EXPORT float CALL wzGetObjectRadius(const Object* object) { return object->radius; }

EXPORT void CALL wzSetObjectRadius(Object* object, float radius) { object->radius = radius; }

EXPORT bool_t CALL wzObjectCollidesBoxes(Object* object) {
    if (object->colmode == COL_SPHERE) {
        return _CheckSphereCol(object->x, object->y, object->z, object->radius * object->radius);
    } else if (object->colmode == COL_BOX) {
        return _CheckBoxCol(
            wzGetObjectMinX(object), wzGetObjectMinY(object), wzGetObjectMinZ(object),
            wzGetObjectMaxX(object), wzGetObjectMaxY(object), wzGetObjectMaxZ(object)
        );
    } else {
        return FALSE;
    }
}

EXPORT bool_t CALL wzObjectCollidesObject(Object* object, Object* object2) {
    if (object != object2 && object->colmode != COL_NONE && object2->colmode != COL_NONE) {
        if (object->colmode == COL_SPHERE && object2->colmode == COL_SPHERE) {
            return lcol_spheresphere(
                object->x, object->y, object->z, object->radius * object->radius,
                object2->x, object2->y, object2->z, object2->radius * object2->radius
            ) == 1;
        } else if (object->colmode == COL_SPHERE && object2->colmode == COL_BOX) {
            return lcol_boxsphere(
                wzGetObjectMinX(object2), wzGetObjectMinY(object2), wzGetObjectMinZ(object2),
                wzGetObjectMaxX(object2), wzGetObjectMaxY(object2), wzGetObjectMaxZ(object2),
                object->x, object->y, object->z, object->radius * object->radius
            ) == 1;
        } else if (object->colmode == COL_BOX && object2->colmode == COL_SPHERE) {
            return lcol_boxsphere(
                wzGetObjectMinX(object), wzGetObjectMinY(object), wzGetObjectMinZ(object),
                wzGetObjectMaxX(object), wzGetObjectMaxY(object), wzGetObjectMaxZ(object),
                object2->x, object2->y, object2->z, object2->radius * object2->radius
            ) == 1;
        } else if (object->colmode == COL_BOX && object2->colmode == COL_BOX) {
            return lcol_boxbox(
                wzGetObjectMinX(object), wzGetObjectMinY(object), wzGetObjectMinZ(object),
                wzGetObjectMaxX(object), wzGetObjectMaxY(object), wzGetObjectMaxZ(object),
                wzGetObjectMinX(object2), wzGetObjectMinY(object2), wzGetObjectMinZ(object2),
                wzGetObjectMaxX(object2), wzGetObjectMaxY(object2), wzGetObjectMaxZ(object2)
            ) == 1;
        } else {
            return FALSE; /* should not get here */
        }
    } else {
        return FALSE;
    }
}

EXPORT int CALL wzGetObjectAnimMode(const Object* object) { return object->animmode; }

EXPORT void CALL wzSetObjectAnimMode(Object* object, int mode) { object->animmode = _Clamp(mode, ANIM_STOP, ANIM_LOOP); }

EXPORT float CALL wzGetObjectAnimSpeed(const Object* object) { return object->animspeed; }

EXPORT void CALL wzSetObjectAnimSpeed(Object* object, float speed) { object->animspeed = speed; }

EXPORT int CALL wzGetObjectFrame(const Object* object) { return object->animframe; }

EXPORT void CALL wzSetObjectFrame(Object* object, int frame) { object->animframe = frame; }

EXPORT int CALL wzGetObjectMinFrame(const Object* object) { return object->animmin; }

EXPORT int CALL wzGetObjectMaxFrame(const Object* object) { return object->animmax; }

EXPORT void CALL wzSetObjectAnimRange(Object* object, int min, int max) {
    object->animmin = min;
    object->animmax = max;
}

EXPORT int CALL wzGetObjectNumFrames(const Object* object) { return _GetMeshLastFrame(object->_mesh); }

EXPORT int CALL wzAddSurface(Object* object) {
    int buffer = AddMeshBuffer(object->_mesh);
    sb_add(object->_materials, 1);
    return buffer;
}

EXPORT int CALL wzGetNumSurfaces(Object* object) { return GetNumMeshBuffers(object->_mesh); }

EXPORT int CALL wzAddVertex(Object* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color) {
    return AddMeshVertex(object->_mesh, buffer, x, y, z, nx, ny, nz, u, v, color);
}

EXPORT int CALL wzAddTriangle(Object* object, int buffer, int v0, int v1, int v2) {
    return AddMeshTriangle(object->_mesh, buffer, v0, v1, v2);
}

EXPORT void CALL wzRebuildObjectMesh(Object* object) { RebuildMesh(object->_mesh); }

EXPORT Material* CALL wzGetObjectMaterial(Object* object, int index) { return &object->_materials[index]; }

EXPORT void CALL wzDrawObject(Object* object) {
    lmat4_t modelview;

    /* calculate animation */
    if (object->animmode != ANIM_STOP) {
        int lastframe = (object->animmax != 0) ? object->animmax : _GetMeshLastFrame(object->_mesh);
        object->animframe += object->animspeed * _object_animfps * wzGetDeltaTime();
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

EXPORT float CALL wzGetDefaultAnimFPS() { return _object_animfps; }

EXPORT void CALL wzSetDefaultAnimFPS(float fps) { _object_animfps = fps; }
