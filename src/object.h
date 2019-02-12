#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "types.h"

#define _ANIM_STOP 0
#define _ANIM_PLAY 1
#define _ANIM_LOOP 2

#define _BILLBOARD_NONE 0
#define _BILLBOARD_FACE 1
#define _BILLBOARD_UPRIGHT 2

#define _COL_NONE 0
#define _COL_SPHERE 1
#define _COL_BOX 2

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

struct object_t* object_new();
struct object_t* object_newcube();
struct object_t* object_newquad();
struct object_t* object_newtriangle();
struct object_t* object_load(const char* filename);
struct object_t* object_clone(const struct object_t* object);
void object_delete(struct object_t* object);
int object_addbuffer(struct object_t* object);
int object_numbuffers(struct object_t* object);
int object_addvertex(struct object_t* object, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
int object_addtriangle(struct object_t* object, int buffer, int v0, int v1, int v2);
void object_rebuildmesh(struct object_t* object);
struct material_t* object_material(struct object_t* object, int index);
float object_width(const struct object_t* object);
float object_height(const struct object_t* object);
float object_depth(const struct object_t* object);
float object_minx(const struct object_t* object);
float object_miny(const struct object_t* object);
float object_minz(const struct object_t* object);
float object_maxx(const struct object_t* object);
float object_maxy(const struct object_t* object);
float object_maxz(const struct object_t* object);
bool_t object_move(struct object_t* object, float x, float y, float z);
void object_turn(struct object_t* object, float pitch, float yaw, float roll);
bool_t object_collidesboxes(struct object_t* object);
bool_t object_collidesobject(struct object_t* object, struct object_t* object2);
void object_draw(struct object_t* object);
int object_numframes(const struct object_t* object);
void object_setanimfps(float fps);
float object_animfps();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* OBJECT_H_INCLUDED */
