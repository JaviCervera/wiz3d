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
#include "mesh.h"
#include "pixmap.h"
#include "screen.h"
#include "texture.h"
#include "util.h"
#include "viewer.h"
#include <stdio.h>
#include <string.h>

struct frame_t
{
  int                frame;
  lvec3_t*           positions;
  lvec3_t*           normals;
};

struct buffer_t
{
  lvert_t*           vertices;
  unsigned short*    indices;
  struct frame_t*    frames;
};

struct mesh_t
{
  size_t             refcount;
  struct buffer_t*   buffers;
  struct material_t* materials;
  lvec3_t            boxmin;
  lvec3_t            boxmax;
};

#pragma pack(push, 1)
struct mshmaterial_t
{
  int color;
  int specular;
  int emissive;
  int ambient;
  unsigned char blendmode;
  unsigned char flags;
  float specpower;
  float cubealpha;
  float refrcoef;
  unsigned char usedtexs;
};
#pragma pack(pop)

bool_t _mesh_load_assimp(const char* filename, struct mesh_t* mesh);
bool_t _mesh_load_md2(const char* filename, struct mesh_t* mesh);


struct mesh_t* mesh_new()
{
  struct mesh_t* mesh;
  mesh = _alloc(struct mesh_t);
  mesh->refcount = 1;
  mesh->buffers = NULL;
  mesh->materials = NULL;
  return mesh;
}

bool_t mesh_load(const char* filename, struct mesh_t* mesh)
{
  char ext[STRING_SIZE];
  ext_extract(filename, ext, sizeof(ext));
  if (str_casecmp(ext, "assbin") == 0)
  {
    return _mesh_load_assimp(filename, mesh);
  }
  else if (str_casecmp(ext, "md2") == 0)
  {
    return _mesh_load_md2(filename, mesh);
  }
  else
  {
    return FALSE;
  }
}

void mesh_retain(struct mesh_t* mesh)
{
  ++mesh->refcount;
}

void mesh_release(struct mesh_t* mesh)
{
  int i;

  if (--mesh->refcount == 0)
  {
    /* free buffer data */
    for (i = 0; i < sb_count(mesh->buffers); ++i)
    {
      int j;
      for (j = 0; j < sb_count(mesh->buffers[i].frames); ++j)
      {
        sb_free(mesh->buffers[i].frames[j].positions);
        sb_free(mesh->buffers[i].frames[j].normals);
      }
      sb_free(mesh->buffers[i].vertices);
      sb_free(mesh->buffers[i].indices);
      sb_free(mesh->buffers[i].frames);
      material_deinit(&mesh->materials[i]);
    }

    sb_free(mesh->materials);
    sb_free(mesh->buffers);
    free(mesh);
  }
}

int mesh_addbuffer(struct mesh_t* mesh)
{
  struct buffer_t* buffer;
  struct material_t* material;

  buffer = sb_add(mesh->buffers, 1);
  material_init(sb_add(mesh->materials, 1));
  buffer->vertices = NULL;
  buffer->indices = NULL;
  buffer->frames = NULL;

  return sb_count(mesh->buffers) - 1;
}

int mesh_addvertex(struct mesh_t* mesh, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v, int color)
{
  sb_push(
    mesh->buffers[buffer].vertices,
    lvert(
      x, y, z,
      nx, ny, nz,
      u, v,
      color_red(color) / 255.0f,
      color_green(color) / 255.0f,
      color_blue(color) / 255.0f,
      color_alpha(color) / 255.0f));
  return sb_count(mesh->buffers[buffer].vertices) - 1;
}

int mesh_addtriangle(struct mesh_t* mesh, int buffer, int v0, int v1, int v2)
{
  unsigned short* index;

  index = sb_add(mesh->buffers[buffer].indices, 3);
  index[0] = v0;
  index[1] = v1;
  index[2] = v2;
  return (sb_count(mesh->buffers[buffer].indices) - 3) / 3;
}

void mesh_rebuild(struct mesh_t* mesh)
{
  int b, v;

  /* calculate mesh bounds */
  if (sb_count(mesh->buffers) > 0 && sb_count(mesh->buffers[0].vertices) > 0)
  {
    mesh->boxmin = lvec3(mesh->buffers[0].vertices[0].pos[0], mesh->buffers[0].vertices[0].pos[1], mesh->buffers[0].vertices[0].pos[2]);
    mesh->boxmax = mesh->boxmin;
  }
  else
  {
    mesh->boxmin = lvec3(0, 0, 0);
    mesh->boxmax = lvec3(0, 0, 0);
  }
  for (b = 0; b < sb_count(mesh->buffers); ++b)
  {
    for (v = 0; v < sb_count(mesh->buffers[b].vertices); ++v)
    {
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

int mesh_numbuffers(struct mesh_t* mesh)
{
  return sb_count(mesh->buffers);
}

struct material_t* mesh_material(struct mesh_t* mesh, int buffer)
{
  return &mesh->materials[buffer];
}

float mesh_width(const struct mesh_t* mesh)
{
  return mesh->boxmax.x - mesh->boxmin.x;
}

float mesh_height(const struct mesh_t* mesh)
{
  return mesh->boxmax.y - mesh->boxmin.y;
}

float mesh_depth(const struct mesh_t* mesh)
{
  return mesh->boxmax.z - mesh->boxmin.z;
}

float mesh_boxminx(const struct mesh_t* mesh)
{
  return mesh->boxmin.x;
}

float mesh_boxminy(const struct mesh_t* mesh)
{
  return mesh->boxmin.y;
}

float mesh_boxminz(const struct mesh_t* mesh)
{
  return mesh->boxmin.z;
}

float mesh_boxmaxx(const struct mesh_t* mesh)
{
  return mesh->boxmax.x;
}

float mesh_boxmaxy(const struct mesh_t* mesh)
{
  return mesh->boxmax.y;
}

float mesh_boxmaxz(const struct mesh_t* mesh)
{
  return mesh->boxmax.z;
}

int _mesh_lastframe(const struct mesh_t* mesh)
{
  return (sb_count(mesh->buffers[0].frames) > 0) ? sb_last(mesh->buffers[0].frames).frame : 0;
}

void _mesh_animate(struct mesh_t* mesh, float frame)
{
  int b;

  /* animate all buffers */
  for (b = 0; b < sb_count(mesh->buffers); ++b)
  {
    struct buffer_t* buffer;
    struct frame_t*  frames;
    int f;
    bool_t finished;

    buffer = &mesh->buffers[b];
    frames = mesh->buffers[b].frames;

    /* make sure that there are frames to animate */
    if (!frames) continue;

    /* if outside bounds, copy first or last frames */
    if (frame < 0)
    {
      int v;
      for (v = 0; v < sb_count(buffer->vertices); ++v)
      {
        buffer->vertices[v].pos[0] = frames[0].positions[v].x;
        buffer->vertices[v].pos[1] = frames[0].positions[v].y;
        buffer->vertices[v].pos[2] = frames[0].positions[v].z;
        buffer->vertices[v].nor[0] = frames[0].normals[v].x;
        buffer->vertices[v].nor[1] = frames[0].normals[v].y;
        buffer->vertices[v].nor[2] = frames[0].normals[v].z;
      }
      continue; /* continue to next buffer */
    }
    else if (frame > sb_last(frames).frame)
    {
      int v;
      for (v = 0; v < sb_count(buffer->vertices); ++v)
      {
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
    for (f = 0; f < sb_count(frames); ++f)
    {
      /* if we finished in the last iteration, continue to next buffer */
      if (finished) continue;

      /* found frame, so copy vertices and normals */
      if (frames[f].frame == frame)
      {
        int j;
        for (j = 0; j < sb_count(buffer->vertices); ++j)
        {
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
      if (frames[f].frame > frame)
      {
        int v;
        float alpha = (frame - frames[f-1].frame) / (frames[f].frame - frames[f-1].frame);
        for (v = 0; v < sb_count(buffer->vertices); ++v)
        {
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

void _mesh_draw(const struct mesh_t* mesh, const struct material_t* materials)
{
  int i;

  /* if no material array is specified, take it from the mesh */
  if (!materials) materials = mesh->materials;

  /* draw all buffers */
  for (i = 0; i < sb_count(mesh->buffers); ++i)
  {
    const struct material_t* material;
    int specular;

    material = &materials[i];

    /* set material settings */
    specular = color_multiply(material->specular, material->shininess);
    lgfx_setblend(material->blend);
    ltex_bindcolor((const ltex_t*)_texture_ptr(material->texture));
    lgfx_setcolor(
      color_red(material->diffuse) / 255.0f,
      color_green(material->diffuse) / 255.0f,
      color_blue(material->diffuse) / 255.0f,
      color_alpha(material->diffuse) / 255.0f);
    lgfx_setemissive(
      color_red(material->emissive) / 255.0f,
      color_green(material->emissive) / 255.0f,
      color_blue(material->emissive) / 255.0f);
    lgfx_setspecular(
      color_red(specular) / 255.0f,
      color_green(specular) / 255.0f,
      color_blue(specular) / 255.0f);
    lgfx_setshininess(_clamp(material->shininess * material->shininesspower > -1 ? material->shininesspower : material_shininesspower(), 0, 128));
    lgfx_setculling((material->flags & _FLAG_CULL) == _FLAG_CULL);
    lgfx_setdepthwrite((material->flags & _FLAG_DEPTHWRITE) == _FLAG_DEPTHWRITE);

    /* setup lighting */
    if ((material->flags & _FLAG_LIGHTING) == _FLAG_LIGHTING)
    {
      int numlights = _light_numlights();
      lgfx_setlighting(numlights);
    }
    else
    {
      lgfx_setlighting(0);
    }

    /* setup fog */
    if ((material->flags & _FLAG_FOG) == _FLAG_FOG)
    {
      lgfx_setfog(
        _viewer_active()->fogenabled,
        color_red(_viewer_active()->fogcolor) / 255.0f,
        color_green(_viewer_active()->fogcolor) / 255.0f,
        color_blue(_viewer_active()->fogcolor) / 255.0f,
        _viewer_active()->fogmin,
        _viewer_active()->fogmax
      );
    }
    else
    {
      lgfx_setfog(FALSE, 0, 0, 0, 0, 0);
    }

    /* draw */
    if (sb_count(mesh->buffers[i].indices) > 0)
    {
      lvert_drawindexed(
        mesh->buffers[i].vertices,
        mesh->buffers[i].indices,
        sb_count(mesh->buffers[i].indices),
        MODE_TRIANGLES
      );
    }
    else
    {
      lvert_draw(
        mesh->buffers[i].vertices,
        sb_count(mesh->buffers[i].vertices),
        MODE_TRIANGLES);
    }
  }
}

struct mesh_t* _mesh_newskybox()
{
  struct mesh_t* mesh;
  int buffer;
  int ldb, ldf, lub, luf, rdb, rdf, rub, ruf, ldb1, lub1;
  int ulb, ulf, urb, urf;
  int dlb, dlf, drb, drf;

  mesh = mesh_new();
  buffer = mesh_addbuffer(mesh);

  /* add vertices */
  ldb = mesh_addvertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, 0, 0, 1, _COLOR_WHITE);
  ldf = mesh_addvertex(mesh, buffer, -0.5f, -0.5f,  0.5f, 0, 0, 0, 0.16666667f, 1, _COLOR_WHITE);
  lub = mesh_addvertex(mesh, buffer, -0.5f,  0.5f, -0.5f, 0, 0, 0, 0, 0, _COLOR_WHITE);
  luf = mesh_addvertex(mesh, buffer, -0.5f,  0.5f,  0.5f, 0, 0, 0, 0.16666667f, 0, _COLOR_WHITE);
  rdb = mesh_addvertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 0, 0, 0, 0.5f, 1, _COLOR_WHITE);
  rdf = mesh_addvertex(mesh, buffer,  0.5f, -0.5f,  0.5f, 0, 0, 0, 0.33333333f, 1, _COLOR_WHITE);
  rub = mesh_addvertex(mesh, buffer,  0.5f,  0.5f, -0.5f, 0, 0, 0, 0.5f, 0, _COLOR_WHITE);
  ruf = mesh_addvertex(mesh, buffer,  0.5f,  0.5f,  0.5f, 0, 0, 0, 0.33333333f, 0, _COLOR_WHITE);
  ldb1 = mesh_addvertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, 0, 0.66555555f, 1, _COLOR_WHITE);
  lub1 = mesh_addvertex(mesh, buffer, -0.5f,  0.5f, -0.5f, 0, 0, 0, 0.66555555f, 0, _COLOR_WHITE);
  ulb =  mesh_addvertex(mesh, buffer, -0.5f,  0.5f, -0.5f, 0, 0, 0, 0.66666667f, 0, _COLOR_WHITE);
  ulf =  mesh_addvertex(mesh, buffer, -0.5f,  0.5f,  0.5f, 0, 0, 0, 0.66666667f, 1, _COLOR_WHITE);
  urb =  mesh_addvertex(mesh, buffer,  0.5f,  0.5f, -0.5f, 0, 0, 0, 0.83333335f, 0, _COLOR_WHITE);
  urf =  mesh_addvertex(mesh, buffer,  0.5f,  0.5f,  0.5f, 0, 0, 0, 0.83333335f, 1, _COLOR_WHITE);
  dlb =  mesh_addvertex(mesh, buffer, -0.5f, -0.5f, -0.5f, 0, 0, 0, 0.83333335f, 0, _COLOR_WHITE);
  dlf =  mesh_addvertex(mesh, buffer, -0.5f, -0.5f,  0.5f, 0, 0, 0, 0.83333335f, 1, _COLOR_WHITE);
  drb =  mesh_addvertex(mesh, buffer,  0.5f, -0.5f, -0.5f, 0, 0, 0, 1, 0, _COLOR_WHITE);
  drf =  mesh_addvertex(mesh, buffer,  0.5f, -0.5f,  0.5f, 0, 0, 0, 1, 1, _COLOR_WHITE);

  /* add indices */
  mesh_addtriangle(mesh, buffer, lub, luf, ldf); /* left face */
  mesh_addtriangle(mesh, buffer, lub, ldf, ldb);
  mesh_addtriangle(mesh, buffer, luf, ruf, rdf); /* front face */
  mesh_addtriangle(mesh, buffer, luf, rdf, ldf);
  mesh_addtriangle(mesh, buffer, ruf, rub, rdb); /* right face */
  mesh_addtriangle(mesh, buffer, ruf, rdb, rdf);
  mesh_addtriangle(mesh, buffer, rub, lub1, ldb1); /* back face */
  mesh_addtriangle(mesh, buffer, rub, ldb1, rdb);
  mesh_addtriangle(mesh, buffer, ulb, urb, ulf); /* up face */
  mesh_addtriangle(mesh, buffer, urb, urf, ulf);
  mesh_addtriangle(mesh, buffer, dlb, dlf, drb); /* down face */
  mesh_addtriangle(mesh, buffer, drb, dlf, drf);

  /* setup material */
  mesh->materials[0].flags = _FLAG_CULL;

  return mesh;
}

bool_t _mesh_load_assimp(const char* filename, struct mesh_t* mesh)
{
  lassbin_scene_t* scene;
  int m, t;

  scene = lassbin_load(filename);
  if (!scene) return FALSE;

  /* make sure that meshes use 16 bits indices */
  for (m = 0; m < scene->num_meshes; ++m)
  {
    if (scene->meshes[m].num_vertices > 65536)
    {
      lassbin_free(scene);
      return FALSE;
    }
  }

  /* add buffers */
  for (m = 0; m < scene->num_meshes; ++m)
  {
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

    buffer = mesh_addbuffer(mesh);

    /* add vertices */
    verts = lassbin_getvertices(&scene->meshes[m]);
    sb_add(mesh->buffers[buffer].vertices, scene->meshes[m].num_vertices);
    memcpy(mesh->buffers[buffer].vertices, verts, scene->meshes[m].num_vertices * sizeof(lvert_t));
    free(verts);

    /* add indices */
    indices = lassbin_getindices(&scene->meshes[m], &num_indices);
    if (indices)
    {
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
    if (tex_name)
    {
      struct texture_t* texture = NULL;

      /* create embedded texture */
      if (tex_name[0] == '*')
      {
        int tex_index;
        struct pixmap_t* pixmap;
        tex_index = tex_name[1] - 48; /* convert ascii code tu number */
        pixmap = _pixmap_newfromdata(scene->textures[tex_index].data, lassbin_texturesize(&scene->textures[tex_index]));
        if (pixmap) {
          texture = texture_newfrompixmap(pixmap);
          pixmap_delete(pixmap);
        }
      }
      /* load texture */
      else
      {
        texture = texture_load(tex_name);
      }
      if (texture) texture_retain(texture); /* automatically loaded textures are reference counted */
      mesh->materials[buffer].texture = texture;
    }

    /* apply diffuse */
    if (diffuse)
    {
      mesh->materials[buffer].diffuse = color_rgba(
        (int)diffuse[0] * 255,
        (int)diffuse[1] * 255,
        (int)diffuse[2] * 255,
        (int)opacity * 255
      );
    }
    else
    {
      mesh->materials[buffer].diffuse = color_rgba(1, 1, 1, (int)opacity * 255);
    }

    /* apply emissive */
    if (emissive)
    {
      mesh->materials[buffer].emissive = color_rgba(
        (int)emissive[0] * 255,
        (int)emissive[1] * 255,
        (int)emissive[2] * 255,
        255
      );
    }

    /* apply specular */
    if (specular)
    {
      mesh->materials[buffer].specular = color_rgba(
        (int)specular[0] * 255,
        (int)specular[1] * 255,
        (int)specular[2] * 255,
        255
      );
    }

    /* apply shininess */
    mesh->materials[buffer].shininess = shininess;
  }

  lassbin_free(scene);

  return TRUE;
}

bool_t _mesh_load_md2(const char* filename, struct mesh_t* mesh)
{
  lmd2_model_t*  mdl;
  struct frame_t* frame;
  int buffer;
  int i;

  /* load md2 */
  mdl = lmd2_load(filename);
  if (!mdl) return FALSE;

  /* create mesh */
  buffer = mesh_addbuffer(mesh);

  /* load texture */
  if (mdl->header.num_skins > 0)
  {
    struct texture_t* texture = texture_load(mdl->skins[0].name);
    if (texture) texture_retain(texture); /* automatically loaded textures are reference counted */
    mesh_material(mesh, buffer)->texture = texture;
  }

  /* create vertices */
  lvert_t* verts = lmd2_getvertices(mdl, 0);
  sb_add(
    mesh->buffers[buffer].vertices,
    mdl->header.num_tris * 3 - sb_count(mesh->buffers[buffer].vertices));
  memcpy(mesh->buffers[buffer].vertices, verts, sizeof(lvert_t) * sb_count(mesh->buffers[buffer].vertices));
  free(verts);

  /* create frames */
  for (i = 0; i < mdl->header.num_frames; ++i )
  {
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
    for (v = 0; v < numverts; ++v)
    {
      frame->positions[v] = lvec3(verts[v].pos[0], verts[v].pos[1], verts[v].pos[2]);
      frame->normals[v] = lvec3(verts[v].nor[0], verts[v].nor[1], verts[v].nor[2]);
    }
    free(verts);
  }

  lmd2_free(mdl);

  return TRUE;
}
