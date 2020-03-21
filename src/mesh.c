#define LITE_ASSBIN_USE_GFX /* add support for litegfx specific stuff in assbin loader */
#define LITE_MD2_USE_GFX /* add support for litegfx specific stuff in md2 loader */
#include "../lib/litelibs/liteassbin.h"
#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "../lib/litelibs/litemd2.h"
#include "../lib/stb/stretchy_buffer.h"
#include "color.h"
#include "light.h"
#include "material.h"
#include "material_internal.h"
#include "memblock.h"
#include "mesh.h"
#include "pixmap.h"
#include "screen.h"
#include "texture.h"
#include "util.h"
#include "viewer.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    int frame;
    lvec3_t* positions;
    lvec3_t* normals;
} Frame;

typedef struct {
    lvert_t* vertices;
    unsigned short* indices;
    Frame* frames;
} Buffer;

typedef struct SMesh {
    size_t refcount;
    Buffer* buffers;
    Material* materials;
    lvec3_t boxmin;
    lvec3_t boxmax;
} Mesh;

bool_t _InitAssimpMesh(const Memblock* memblock, Mesh* mesh);
bool_t _InitMD2Mesh(const Memblock* memblock, Mesh* mesh);


Mesh* CreateMesh(const Memblock* memblock) {
    Mesh* mesh;
    bool_t init_ok;

    mesh = _Alloc(Mesh);
    mesh->refcount = 1;
    mesh->buffers = NULL;
    mesh->materials = NULL;
    
    if (memblock) {
        init_ok = FALSE;
        if (bmGetMemblockInt(memblock, 0) == 844121161) {
            init_ok = _InitMD2Mesh(memblock, mesh);
        } else {
            init_ok = _InitAssimpMesh(memblock, mesh);
        }

        if (!init_ok) {
            ReleaseMesh(mesh);
            mesh = NULL;
        }
    }
    
    return mesh;
}

void RetainMesh(Mesh* mesh) {
    ++mesh->refcount;
}

void ReleaseMesh(Mesh* mesh) {
    int i;

    if (--mesh->refcount == 0) {
        /* free buffer data */
        for (i = 0; i < sb_count(mesh->buffers); ++i) {
            int j;
            for (j = 0; j < sb_count(mesh->buffers[i].frames); ++j) {
                sb_free(mesh->buffers[i].frames[j].positions);
                sb_free(mesh->buffers[i].frames[j].normals);
            }
            sb_free(mesh->buffers[i].vertices);
            sb_free(mesh->buffers[i].indices);
            sb_free(mesh->buffers[i].frames);
            _FinishMaterial(&mesh->materials[i]);
        }

        sb_free(mesh->materials);
        sb_free(mesh->buffers);
        free(mesh);
    }
}

int AddMeshBuffer(Mesh* mesh) {
    Buffer* buffer;
    Material* material;

    buffer = sb_add(mesh->buffers, 1);
    _InitMaterial(sb_add(mesh->materials, 1));
    buffer->vertices = NULL;
    buffer->indices = NULL;
    buffer->frames = NULL;

    return sb_count(mesh->buffers) - 1;
}

int AddMeshVertex(Mesh* mesh, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color) {
    sb_push(
        mesh->buffers[buffer].vertices,
        lvert(
            x, y, z,
            nx, ny, nz,
            u, v,
            bmGetRed(color) / 255.0f,
            bmGetGreen(color) / 255.0f,
            bmGetBlue(color) / 255.0f,
            bmGetAlpha(color) / 255.0f));
    return sb_count(mesh->buffers[buffer].vertices) - 1;
}

int AddMeshTriangle(Mesh* mesh, int buffer, int v0, int v1, int v2) {
    unsigned short* index;

    index = sb_add(mesh->buffers[buffer].indices, 3);
    index[0] = v0;
    index[1] = v1;
    index[2] = v2;
    return (sb_count(mesh->buffers[buffer].indices) - 3) / 3;
}

void RebuildMesh(Mesh* mesh) {
    int b, v;

    /* calculate mesh bounds */
    if (sb_count(mesh->buffers) > 0 && sb_count(mesh->buffers[0].vertices) > 0) {
        mesh->boxmin = lvec3(mesh->buffers[0].vertices[0].pos[0], mesh->buffers[0].vertices[0].pos[1], mesh->buffers[0].vertices[0].pos[2]);
        mesh->boxmax = mesh->boxmin;
    } else {
        mesh->boxmin = lvec3(0, 0, 0);
        mesh->boxmax = lvec3(0, 0, 0);
    }
    for (b = 0; b < sb_count(mesh->buffers); ++b) {
        for (v = 0; v < sb_count(mesh->buffers[b].vertices); ++v) {
            float vx, vy, vz;
            vx = mesh->buffers[b].vertices[v].pos[0];
            vy = mesh->buffers[b].vertices[v].pos[1];
            vz = mesh->buffers[b].vertices[v].pos[2];
            if (vx < mesh->boxmin.x) mesh->boxmin.x = vx;
            if (vy < mesh->boxmin.y) mesh->boxmin.y = vy;
            if (vz < mesh->boxmin.z) mesh->boxmin.z = vz;
            if (vx > mesh->boxmax.x) mesh->boxmax.x = vx;
            if (vy > mesh->boxmax.y) mesh->boxmax.y = vy;
            if (vz > mesh->boxmax.z) mesh->boxmax.z = vz;
        }
    }
}

int GetNumMeshBuffers(Mesh* mesh) {
    return sb_count(mesh->buffers);
}

Material* GetMeshMaterial(Mesh* mesh, int buffer) {
    return &mesh->materials[buffer];
}

float GetMeshWidth(const Mesh* mesh) {
    return mesh->boxmax.x - mesh->boxmin.x;
}

float GetMeshHeight(const Mesh* mesh) {
    return mesh->boxmax.y - mesh->boxmin.y;
}

float GetMeshDepth(const Mesh* mesh) {
    return mesh->boxmax.z - mesh->boxmin.z;
}

float GetMeshBoxMinX(const Mesh* mesh) {
    return mesh->boxmin.x;
}

float GetMeshBoxMinY(const Mesh* mesh) {
    return mesh->boxmin.y;
}

float GetMeshBoxMinZ(const Mesh* mesh) {
    return mesh->boxmin.z;
}

float GetMeshBoxMaxX(const Mesh* mesh) {
    return mesh->boxmax.x;
}

float GetMeshBoxMaxY(const Mesh* mesh) {
    return mesh->boxmax.y;
}

float GetMeshBoxMaxZ(const Mesh* mesh) {
    return mesh->boxmax.z;
}

int _GetMeshLastFrame(const Mesh* mesh) {
    return (sb_count(mesh->buffers[0].frames) > 0) ? sb_last(mesh->buffers[0].frames).frame : 0;
}

void _AnimateMesh(Mesh* mesh, float frame) {
    int b;

    /* animate all buffers */
    for (b = 0; b < sb_count(mesh->buffers); ++b) {
        Buffer* buffer;
        Frame*    frames;
        int f;
        bool_t finished;

        buffer = &mesh->buffers[b];
        frames = mesh->buffers[b].frames;

        /* make sure that there are frames to animate */
        if (!frames) continue;

        /* if outside bounds, copy first or last frames */
        if (frame < 0) {
            int v;
            for (v = 0; v < sb_count(buffer->vertices); ++v) {
                buffer->vertices[v].pos[0] = frames[0].positions[v].x;
                buffer->vertices[v].pos[1] = frames[0].positions[v].y;
                buffer->vertices[v].pos[2] = frames[0].positions[v].z;
                buffer->vertices[v].nor[0] = frames[0].normals[v].x;
                buffer->vertices[v].nor[1] = frames[0].normals[v].y;
                buffer->vertices[v].nor[2] = frames[0].normals[v].z;
            }
            continue; /* continue to next buffer */
        } else if (frame > sb_last(frames).frame) {
            int v;
            for (v = 0; v < sb_count(buffer->vertices); ++v) {
                buffer->vertices[v].pos[0] = sb_last(frames).positions[v].x;
                buffer->vertices[v].pos[1] = sb_last(frames).positions[v].y;
                buffer->vertices[v].pos[2] = sb_last(frames).positions[v].z;
                buffer->vertices[v].nor[0] = sb_last(frames).normals[v].x;
                buffer->vertices[v].nor[1] = sb_last(frames).normals[v].y;
                buffer->vertices[v].nor[2] = sb_last(frames).normals[v].z;
            }
            continue; /* continue to next buffer */
        }

        /* if within bounds, copy correct frame (interpolating when needed) */
        finished = FALSE;
        for (f = 0; f < sb_count(frames); ++f) {
            /* if we finished in the last iteration, continue to next buffer */
            if (finished) continue;

            /* found frame, so copy vertices and normals */
            if (frames[f].frame == frame) {
                int j;
                for (j = 0; j < sb_count(buffer->vertices); ++j) {
                    buffer->vertices[j].pos[0] = frames[f].positions[j].x;
                    buffer->vertices[j].pos[1] = frames[f].positions[j].y;
                    buffer->vertices[j].pos[2] = frames[f].positions[j].z;
                    buffer->vertices[j].nor[0] = frames[f].normals[j].x;
                    buffer->vertices[j].nor[1] = frames[f].normals[j].y;
                    buffer->vertices[j].nor[2] = frames[f].normals[j].z;
                }
                finished = TRUE;
            }

            /* found next frame, so interpolate */
            if (frames[f].frame > frame) {
                int v;
                float alpha = (frame - frames[f-1].frame) / (frames[f].frame - frames[f-1].frame);
                for (v = 0; v < sb_count(buffer->vertices); ++v) {
                    lvec3_t pos, nor;
                    pos = lvec3_mix(frames[f-1].positions[v], frames[f].positions[v], alpha);
                    nor = lvec3_mix(frames[f-1].normals[v], frames[f].normals[v], alpha);
                    buffer->vertices[v].pos[0] = pos.x;
                    buffer->vertices[v].pos[1] = pos.y;
                    buffer->vertices[v].pos[2] = pos.z;
                    buffer->vertices[v].nor[0] = nor.x;
                    buffer->vertices[v].nor[1] = nor.y;
                    buffer->vertices[v].nor[2] = nor.z;
                }
                finished = TRUE;
            }
        }
    }
}

void _DrawMesh(const Mesh* mesh, const Material* materials) {
    int i;

    /* if no material array is specified, take it from the mesh */
    if (!materials) materials = mesh->materials;

    /* draw all buffers */
    for (i = 0; i < sb_count(mesh->buffers); ++i) {
        const Material* material;
        const Viewer* viewer;
        int specular;
        bool_t use_lighting;

        material = &materials[i];

        /* get lighting settings */
        if ((bmGetMaterialFlags(material) & FLAG_LIGHTING) == FLAG_LIGHTING) {
            use_lighting = _GetNumLights() > 0;
        } else {
            use_lighting = FALSE;
        }

        /* set material settings */
        specular = bmMultiplyColor(bmGetMaterialSpecular(material), bmGetMaterialShininess(material));
        lgfx_setblend(bmGetMaterialBlend(material));
        ltex_bind(
            (const ltex_t*)_GetTexturePtr(bmGetMaterialTexture(material)),
            (const ltex_t*)_GetTexturePtr(bmGetMaterialLightmap(material)),
            use_lighting);
        lgfx_setcolor(
            bmGetRed(bmGetMaterialDiffuse(material)) / 255.0f,
            bmGetGreen(bmGetMaterialDiffuse(material)) / 255.0f,
            bmGetBlue(bmGetMaterialDiffuse(material)) / 255.0f,
            bmGetAlpha(bmGetMaterialDiffuse(material)) / 255.0f);
        lgfx_setemissive(
            bmGetRed(bmGetMaterialEmissive(material)) / 255.0f,
            bmGetGreen(bmGetMaterialEmissive(material)) / 255.0f,
            bmGetBlue(bmGetMaterialEmissive(material)) / 255.0f);
        lgfx_setspecular(
            bmGetRed(specular) / 255.0f,
            bmGetGreen(specular) / 255.0f,
            bmGetBlue(specular) / 255.0f);
        lgfx_setshininess(_Clamp(bmGetMaterialShininess(material) * bmGetMaterialShininessPower(material) > -1 ? bmGetMaterialShininessPower(material) : bmGetDefaultShininessPower(), 0, 128));
        lgfx_setculling((bmGetMaterialFlags(material) & FLAG_CULL) == FLAG_CULL);
        lgfx_setdepthwrite((bmGetMaterialFlags(material) & FLAG_DEPTHWRITE) == FLAG_DEPTHWRITE);

        /* setup lighting */
        lgfx_setlighting(use_lighting ? _GetNumLights() : 0);

        /* setup fog */
        viewer = _GetActiveViewer();
        if ((bmGetMaterialFlags(material) & FLAG_FOG) == FLAG_FOG) {
            lgfx_setfog(
                bmIsViewerFogEnabled(viewer),
                bmGetRed(bmGetViewerFogColor(viewer)) / 255.0f,
                bmGetGreen(bmGetViewerFogColor(viewer)) / 255.0f,
                bmGetBlue(bmGetViewerFogColor(viewer)) / 255.0f,
                bmGetViewerFogDistanceMin(viewer),
                bmGetViewerFogDistanceMax(viewer)
            );
        } else {
            lgfx_setfog(FALSE, 0, 0, 0, 0, 0);
        }

        /* draw */
        if (sb_count(mesh->buffers[i].indices) > 0) {
            lvert_drawindexed(
                mesh->buffers[i].vertices,
                mesh->buffers[i].indices,
                sb_count(mesh->buffers[i].indices),
                R_TRIANGLES
            );
        } else {
            lvert_draw(
                mesh->buffers[i].vertices,
                sb_count(mesh->buffers[i].vertices),
                R_TRIANGLES);
        }
    }
}

Mesh* _CreateSkyboxMesh() {
    Mesh* mesh;
    int buffer;
    int ldb, ldf, lub, luf, rdb, rdf, rub, ruf, ldb1, lub1;
    int ulb, ulf, urb, urf;
    int dlb, dlf, drb, drf;

    mesh = CreateMesh(NULL);
    buffer = AddMeshBuffer(mesh);

    /* add vertices */
    ldb = AddMeshVertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, 0, 0, 1, COLOR_WHITE);
    ldf = AddMeshVertex(mesh, buffer, -0.5f, -0.5f,    0.5f, 0, 0, 0, 0.16666667f, 1, COLOR_WHITE);
    lub = AddMeshVertex(mesh, buffer, -0.5f,    0.5f, -0.5f, 0, 0, 0, 0, 0, COLOR_WHITE);
    luf = AddMeshVertex(mesh, buffer, -0.5f,    0.5f,    0.5f, 0, 0, 0, 0.16666667f, 0, COLOR_WHITE);
    rdb = AddMeshVertex(mesh, buffer,    0.5f, -0.5f, -0.5f, 0, 0, 0, 0.5f, 1, COLOR_WHITE);
    rdf = AddMeshVertex(mesh, buffer,    0.5f, -0.5f,    0.5f, 0, 0, 0, 0.33333333f, 1, COLOR_WHITE);
    rub = AddMeshVertex(mesh, buffer,    0.5f,    0.5f, -0.5f, 0, 0, 0, 0.5f, 0, COLOR_WHITE);
    ruf = AddMeshVertex(mesh, buffer,    0.5f,    0.5f,    0.5f, 0, 0, 0, 0.33333333f, 0, COLOR_WHITE);
    ldb1 = AddMeshVertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, 0, 0.66555555f, 1, COLOR_WHITE);
    lub1 = AddMeshVertex(mesh, buffer, -0.5f,    0.5f, -0.5f, 0, 0, 0, 0.66555555f, 0, COLOR_WHITE);
    ulb =    AddMeshVertex(mesh, buffer, -0.5f,    0.5f, -0.5f, 0, 0, 0, 0.66666667f, 0, COLOR_WHITE);
    ulf =    AddMeshVertex(mesh, buffer, -0.5f,    0.5f,    0.5f, 0, 0, 0, 0.66666667f, 1, COLOR_WHITE);
    urb =    AddMeshVertex(mesh, buffer,    0.5f,    0.5f, -0.5f, 0, 0, 0, 0.83333335f, 0, COLOR_WHITE);
    urf =    AddMeshVertex(mesh, buffer,    0.5f,    0.5f,    0.5f, 0, 0, 0, 0.83333335f, 1, COLOR_WHITE);
    dlb =    AddMeshVertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, 0, 0.83333335f, 0, COLOR_WHITE);
    dlf =    AddMeshVertex(mesh, buffer, -0.5f, -0.5f,    0.5f, 0, 0, 0, 0.83333335f, 1, COLOR_WHITE);
    drb =    AddMeshVertex(mesh, buffer,    0.5f, -0.5f, -0.5f, 0, 0, 0, 1, 0, COLOR_WHITE);
    drf =    AddMeshVertex(mesh, buffer,    0.5f, -0.5f,    0.5f, 0, 0, 0, 1, 1, COLOR_WHITE);

    /* add indices */
    AddMeshTriangle(mesh, buffer, lub, luf, ldf); /* left face */
    AddMeshTriangle(mesh, buffer, lub, ldf, ldb);
    AddMeshTriangle(mesh, buffer, luf, ruf, rdf); /* front face */
    AddMeshTriangle(mesh, buffer, luf, rdf, ldf);
    AddMeshTriangle(mesh, buffer, ruf, rub, rdb); /* right face */
    AddMeshTriangle(mesh, buffer, ruf, rdb, rdf);
    AddMeshTriangle(mesh, buffer, rub, lub1, ldb1); /* back face */
    AddMeshTriangle(mesh, buffer, rub, ldb1, rdb);
    AddMeshTriangle(mesh, buffer, ulb, urb, ulf); /* up face */
    AddMeshTriangle(mesh, buffer, urb, urf, ulf);
    AddMeshTriangle(mesh, buffer, dlb, dlf, drb); /* down face */
    AddMeshTriangle(mesh, buffer, drb, dlf, drf);

    /* setup material */
    bmSetMaterialFlags(&mesh->materials[0], FLAG_CULL);

    return mesh;
}

bool_t _InitAssimpMesh(const Memblock* memblock, Mesh* mesh) {
    lassbin_scene_t* scene;
    int m, t;

    scene = lassbin_loadmem((const char*)memblock);
    if (!scene) return FALSE;

    /* make sure that meshes use 16 bits indices */
    for (m = 0; m < scene->num_meshes; ++m) {
        if (scene->meshes[m].num_vertices > 65536) {
            lassbin_free(scene);
            return FALSE;
        }
    }

    /* add buffers */
    for (m = 0; m < scene->num_meshes; ++m) {
        int buffer;
        lvert_t* verts;
        unsigned short* indices;
        int num_indices;
        const lassbin_material_t* material;
        const char* tex_name;
        float opacity;
        const float* diffuse;
        const float* emissive;
        const float* specular;
        float shininess;
        /*float shinpercent;*/

        buffer = AddMeshBuffer(mesh);

        /* add vertices */
        verts = lassbin_getvertices(&scene->meshes[m]);
        sb_add(mesh->buffers[buffer].vertices, scene->meshes[m].num_vertices);
        memcpy(mesh->buffers[buffer].vertices, verts, scene->meshes[m].num_vertices * sizeof(lvert_t));
        free(verts);

        /* add indices */
        indices = lassbin_getindices(&scene->meshes[m], &num_indices);
        if (indices) {
            sb_add(mesh->buffers[buffer].indices, num_indices);
            memcpy(mesh->buffers[buffer].indices, indices, num_indices * sizeof(unsigned short));
            free(indices);
        }

        /* parse material */
        material = &scene->materials[scene->meshes[m].material_index];
        tex_name = lassbin_mattexturename(material, LASSBIN_TEXTURE_DIFFUSE, 0);
        opacity = lassbin_matopacity(material);
        diffuse = lassbin_matdiffuse(material);
        emissive = lassbin_matemissive(material);
        specular = lassbin_matspecular(material);
        shininess = lassbin_matshininess(material);
        /*shinpercent = lassbin_matshinpercent(material);*/

        /* apply texture */
        if (tex_name) {
            Texture* texture = NULL;

            if (tex_name[0] == '*') {
                /* create embedded texture */
                int tex_index;
                Pixmap* pixmap;
                tex_index = tex_name[1] - 48; /* convert ascii code tu number */
                pixmap = _CreateEmptyPixmapFromData(scene->textures[tex_index].data, lassbin_texturesize(&scene->textures[tex_index]));
                if (pixmap) {
                    texture = bmCreateTexture(pixmap);
                    bmDeletePixmap(pixmap);
                }
            } else {
                /* load texture */
                texture = bmLoadTexture(tex_name);
            }
            if (texture) RetainTexture(texture); /* automatically loaded textures are reference counted */
            bmSetMaterialTexture(&mesh->materials[buffer], texture);
        }

        /* apply diffuse */
        if (diffuse) {
            bmSetMaterialDiffuse(&mesh->materials[buffer], bmGetRGBA(
                (int)diffuse[0] * 255,
                (int)diffuse[1] * 255,
                (int)diffuse[2] * 255,
                (int)opacity * 255
            ));
        } else {
            bmSetMaterialDiffuse(&mesh->materials[buffer], bmGetRGBA(1, 1, 1, (int)opacity * 255));
        }

        /* apply emissive */
        if (emissive) {
            bmSetMaterialEmissive(&mesh->materials[buffer], bmGetRGBA(
                (int)emissive[0] * 255,
                (int)emissive[1] * 255,
                (int)emissive[2] * 255,
                255
            ));
        }

        /* apply specular */
        if (specular) {
            bmSetMaterialSpecular(&mesh->materials[buffer], bmGetRGBA(
                (int)specular[0] * 255,
                (int)specular[1] * 255,
                (int)specular[2] * 255,
                255
            ));
        }

        /* apply shininess */
        bmSetMaterialShininess(&mesh->materials[buffer], shininess);
    }

    lassbin_free(scene);

    return TRUE;
}

bool_t _InitMD2Mesh(const Memblock* memblock, Mesh* mesh) {
    lmd2_model_t*    mdl;
    Frame* frame;
    int buffer;
    int i;

    /* load md2 */
    mdl = lmd2_loadmem((const char*)memblock);
    if (!mdl) return FALSE;

    /* create mesh */
    buffer = AddMeshBuffer(mesh);

    /* load texture */
    if (mdl->header.num_skins > 0) {
        Texture* texture = bmLoadTexture(mdl->skins[0].name);
        if (texture) RetainTexture(texture); /* automatically loaded textures are reference counted */
        bmSetMaterialTexture(GetMeshMaterial(mesh, buffer), texture);
    }

    /* create vertices */
    lvert_t* verts = lmd2_getvertices(mdl, 0);
    sb_add(
        mesh->buffers[buffer].vertices,
        mdl->header.num_tris * 3 - sb_count(mesh->buffers[buffer].vertices));
    memcpy(mesh->buffers[buffer].vertices, verts, sizeof(lvert_t) * sb_count(mesh->buffers[buffer].vertices));
    free(verts);

    /* create frames */
    for (i = 0; i < mdl->header.num_frames; ++i ) {
        int numverts;
        int v;

        numverts = sb_count(mesh->buffers[buffer].vertices);
        frame = sb_add(mesh->buffers[buffer].frames, 1);
        frame->frame = i;
        frame->positions = NULL;
        frame->normals = NULL;
        sb_add(frame->positions, numverts);
        sb_add(frame->normals, numverts);
        verts = lmd2_getvertices(mdl, i);
        for (v = 0; v < numverts; ++v) {
            frame->positions[v] = lvec3(verts[v].pos[0], verts[v].pos[1], verts[v].pos[2]);
            frame->normals[v] = lvec3(verts[v].nor[0], verts[v].nor[1], verts[v].nor[2]);
        }
        free(verts);
    }

    lmd2_free(mdl);

    return TRUE;
}
