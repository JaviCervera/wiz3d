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
struct mesh_t* mesh_load(const char* filename);
void mesh_retain(struct mesh_t* mesh);
void mesh_release(struct mesh_t* mesh);
int mesh_addbuffer(struct mesh_t* mesh);
int mesh_numbuffers(struct mesh_t* mesh);
int mesh_addvertex(struct mesh_t* mesh, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v);
int mesh_addtriangle(struct mesh_t* mesh, int buffer, int v0, int v1, int v2);
struct material_t* mesh_material(struct mesh_t* mesh, int buffer);

int _mesh_lastframe(struct mesh_t* mesh);
void _mesh_animate(struct mesh_t* mesh, float frame);
void _mesh_draw(struct mesh_t* mesh, struct material_t* materials);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MESH_H_INCLUDED */
