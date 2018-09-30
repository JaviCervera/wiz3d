#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SWIG
struct material_t;
struct mesh_t;

struct mesh_t* mesh_new();
bool_t mesh_load(const char* filename, struct mesh_t* mesh);
void mesh_retain(struct mesh_t* mesh);
void mesh_release(struct mesh_t* mesh);
int mesh_addbuffer(struct mesh_t* mesh);
int mesh_numbuffers(struct mesh_t* mesh);
int mesh_addvertex(struct mesh_t* mesh, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
int mesh_addtriangle(struct mesh_t* mesh, int buffer, int v0, int v1, int v2);
void mesh_rebuild(struct mesh_t* mesh);
struct material_t* mesh_material(struct mesh_t* mesh, int buffer);
float mesh_width(const struct mesh_t* mesh);
float mesh_height(const struct mesh_t* mesh);
float mesh_depth(const struct mesh_t* mesh);
float mesh_boxminx(const struct mesh_t* mesh);
float mesh_boxminy(const struct mesh_t* mesh);
float mesh_boxminz(const struct mesh_t* mesh);
float mesh_boxmaxx(const struct mesh_t* mesh);
float mesh_boxmaxy(const struct mesh_t* mesh);
float mesh_boxmaxz(const struct mesh_t* mesh);
int _mesh_lastframe(const struct mesh_t* mesh);
void _mesh_animate(struct mesh_t* mesh, float frame);
void _mesh_draw(const struct mesh_t* mesh, const struct material_t* materials);
struct mesh_t* _mesh_newskybox();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MESH_H_INCLUDED */
