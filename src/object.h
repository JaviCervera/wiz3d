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
extern "C"
{
#endif

struct material_t;
struct mesh_t;

struct object_t
{
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
  struct mesh_t*     _mesh;
  struct material_t* _materials;
#endif
};

EXPORT struct object_t* CALL object_new();
EXPORT struct object_t* CALL object_newcube();
EXPORT struct object_t* CALL object_newquad();
EXPORT struct object_t* CALL object_newtriangle();
EXPORT struct object_t* CALL object_load(const char* filename);
EXPORT struct object_t* CALL object_clone(const struct object_t* object);
EXPORT void CALL object_delete(struct object_t* object);
EXPORT int CALL object_addbuffer(struct object_t* object);
EXPORT int CALL object_numbuffers(struct object_t* object);
EXPORT int CALL object_addvertex(struct object_t* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
EXPORT int CALL object_addtriangle(struct object_t* object, int buffer, int v0, int v1, int v2);
EXPORT void CALL object_rebuildmesh(struct object_t* object);
EXPORT struct material_t* CALL object_material(struct object_t* object, int index);
EXPORT float CALL object_width(const struct object_t* object);
EXPORT float CALL object_height(const struct object_t* object);
EXPORT float CALL object_depth(const struct object_t* object);
EXPORT float CALL object_minx(const struct object_t* object);
EXPORT float CALL object_miny(const struct object_t* object);
EXPORT float CALL object_minz(const struct object_t* object);
EXPORT float CALL object_maxx(const struct object_t* object);
EXPORT float CALL object_maxy(const struct object_t* object);
EXPORT float CALL object_maxz(const struct object_t* object);
EXPORT bool_t CALL object_move(struct object_t* object, float x, float y, float z);
EXPORT void CALL object_turn(struct object_t* object, float pitch, float yaw, float roll);
EXPORT bool_t CALL object_collidesboxes(struct object_t* object);
EXPORT bool_t CALL object_collidesobject(struct object_t* object, struct object_t* object2);
EXPORT void CALL object_draw(struct object_t* object);
EXPORT int CALL object_numframes(const struct object_t* object);
EXPORT void CALL object_setanimfps(float fps);
EXPORT float CALL object_animfps();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* OBJECT_H_INCLUDED */
