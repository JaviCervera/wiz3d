#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SWIG
struct SMaterial;
struct SMemblock;
struct SMesh;

struct SMesh* CreateMesh(const struct SMemblock* memblock);
void RetainMesh(struct SMesh* mesh);
void ReleaseMesh(struct SMesh* mesh);
int AddMeshBuffer(struct SMesh* mesh);
int GetNumMeshBuffers(struct SMesh* mesh);
int AddMeshVertex(struct SMesh* mesh, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
int AddMeshTriangle(struct SMesh* mesh, int buffer, int v0, int v1, int v2);
void RebuildMesh(struct SMesh* mesh);
struct SMaterial* GetMeshMaterial(struct SMesh* mesh, int buffer);
float GetMeshWidth(const struct SMesh* mesh);
float GetMeshHeight(const struct SMesh* mesh);
float GetMeshDepth(const struct SMesh* mesh);
float GetMeshBoxMinX(const struct SMesh* mesh);
float GetMeshBoxMinY(const struct SMesh* mesh);
float GetMeshBoxMinZ(const struct SMesh* mesh);
float GetMeshBoxMaxX(const struct SMesh* mesh);
float GetMeshBoxMaxY(const struct SMesh* mesh);
float GetMeshBoxMaxZ(const struct SMesh* mesh);
int _GetMeshLastFrame(const struct SMesh* mesh);
void _AnimateMesh(struct SMesh* mesh, float frame);
void _DrawMesh(const struct SMesh* mesh, const Material* materials);
struct SMesh* _CreateSkyboxMesh();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MESH_H_INCLUDED */
