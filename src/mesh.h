#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SWIG

Mesh* CreateMesh(const Memblock* memblock);
void RetainMesh(Mesh* mesh);
void ReleaseMesh(Mesh* mesh);
int AddMeshBuffer(Mesh* mesh);
int GetNumMeshBuffers(Mesh* mesh);
int AddMeshVertex(Mesh* mesh, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color);
int AddMeshTriangle(Mesh* mesh, int buffer, int v0, int v1, int v2);
void RebuildMesh(Mesh* mesh);
Material* GetMeshMaterial(Mesh* mesh, int buffer);
float GetMeshWidth(const Mesh* mesh);
float GetMeshHeight(const Mesh* mesh);
float GetMeshDepth(const Mesh* mesh);
float GetMeshBoxMinX(const Mesh* mesh);
float GetMeshBoxMinY(const Mesh* mesh);
float GetMeshBoxMinZ(const Mesh* mesh);
float GetMeshBoxMaxX(const Mesh* mesh);
float GetMeshBoxMaxY(const Mesh* mesh);
float GetMeshBoxMaxZ(const Mesh* mesh);
int _GetMeshLastFrame(const Mesh* mesh);
void _AnimateMesh(Mesh* mesh, float frame);
void _DrawMesh(const Mesh* mesh, const Material* materials);
Mesh* _CreateSkyboxMesh();

#endif /* SWIG */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MESH_H_INCLUDED */
