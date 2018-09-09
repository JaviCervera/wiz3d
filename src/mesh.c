#define LITE_MD2_USE_GFX /* add support for litegfx specific stuff in md2 laoder */
#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "../lib/litelibs/litemd2.h"
#include "../lib/stretchy_buffer.h"
#include "color.h"
#include "light.h"
#include "material.h"
#include "mesh.h"
#include "screen.h"
#include "texture.h"
#include "util.h"
#include "viewer.h"
#include <stdio.h>
#include <string.h>

#define MAX_SHININESS 8

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

static struct mesh_t* _mesh_load_md2(const char* filename);
static struct mesh_t* _mesh_load_msh(const char* filename);


struct mesh_t* mesh_new()
{
  struct mesh_t* mesh;
  mesh = _alloc(struct mesh_t);
  mesh->refcount = 1;
  mesh->buffers = NULL;
  mesh->materials = NULL;
  return mesh;
}

struct mesh_t* mesh_load(const char* filename)
{
  char ext[STRING_SIZE];
  ext_extract(filename, ext, sizeof(ext));
  if (str_casecmp(ext, "msh") == 0)
  {
    return _mesh_load_msh(filename);
  }
  else if (str_casecmp(ext, "md2") == 0)
  {
    return _mesh_load_md2(filename);
  }
  else
  {
    return NULL;
  }
}

void mesh_retain(struct mesh_t* mesh)
{
  ++mesh->refcount;
}

void mesh_release(struct mesh_t* mesh)
{
  int i;

  if (--mesh->refcount == 0) {
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

int mesh_addvertex(struct mesh_t* mesh, int buffer, float x, float y, float z, float nx, float ny, float nz, float u, float v)
{
  sb_push(mesh->buffers[buffer].vertices, lvert(x, y, z, nx, ny, nz, u, v, 1, 1, 1, 1));
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

int mesh_numbuffers(struct mesh_t* mesh)
{
  return sb_count(mesh->buffers);
}

struct material_t* mesh_material(struct mesh_t* mesh, int buffer)
{
  return &mesh->materials[buffer];
}

int _mesh_lastframe(struct mesh_t* mesh)
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

void _mesh_draw(struct mesh_t* mesh, struct material_t* materials)
{
  int i;

  /* if no material array is specified, take it from the mesh */
  if (!materials) materials = mesh->materials;

  /* draw all buffers */
  for ( i = 0; i < sb_count(mesh->buffers); ++i )
  {
    struct material_t* material;
    int specular;

    material = &materials[i];

    specular = color_multiply(material->specular, material->shininess);
    lgfx_setblend(material->blend);
    ltex_bindcolor((const ltex_t*)_texture_ptr(material->texture));
    lgfx_setcolor(
      color_red(material->color) / 255.0,
      color_green(material->color) / 255.0,
      color_blue(material->color) / 255.0,
      color_alpha(material->color) / 255.0);
    lgfx_setemissive(
      color_red(material->emissive) / 255.0,
      color_green(material->emissive) / 255.0,
      color_blue(material->emissive) / 255.0);
    lgfx_setspecular(
      color_red(specular) / 255.0,
      color_green(specular) / 255.0,
      color_blue(specular) / 255.0);
    lgfx_setshininess(material->shininess * MAX_SHININESS);
    lgfx_setculling((material->flags & _FLAG_CULL) == _FLAG_CULL);
    lgfx_setdepthwrite((material->flags & _FLAG_DEPTHWRITE) == _FLAG_DEPTHWRITE);
    if ((material->flags & _FLAG_LIGHTING) == _FLAG_LIGHTING)
    {
      int numlights = _light_numlights();
      lgfx_setlighting(numlights);
    }
    else lgfx_setlighting(0);
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

static struct mesh_t* _mesh_load_msh(const char* filename)
{
  FILE* f;
  size_t filenamelen;
  char* path;
  struct mesh_t* mesh;
  char id[5];
  unsigned short numsurfs;
  int i, j;
  int len;

  /* open file */
  f = fopen(filename, "rb");
  if ( !f ) return NULL;

  /* read id */
  id[4] = 0;
  fread(id, sizeof(char), 4, f);
  if ( strcmp(id, "ME01") != 0 ) return NULL;

  /* store path */
  filenamelen = strlen(filename);
  path = _allocnum(char, filenamelen+1);
  dir_extract(filename, path, filenamelen+1);
  filenamelen = strlen(path);

  /* create mesh */
  mesh = mesh_new();

  /* read surfaces */
  fread(&numsurfs, sizeof(numsurfs), 1, f);
  for ( i = 0; i < numsurfs; ++i )
  {
    struct mshmaterial_t mat;
    struct texture_t* texture = NULL;
    int flags = _FLAG_ALL;
    int numindices;
    unsigned short numvertices;
    unsigned char vertexflags;
    int buffer;

    /* read material */
    fread(&mat, sizeof(mat), 1, f);

    /* parse flags */
    if ( (mat.flags & _FLAG_CULL) == 0 ) flags -= _FLAG_CULL;
    if ( (mat.flags & _FLAG_DEPTHWRITE) == 0 ) flags -= _FLAG_DEPTHWRITE;

    /* read textures */
    if ( mat.usedtexs & 1 ) /* color texture */
    {
      char* str;

      fread(&len, sizeof(len), 1, f);
      str = _allocnum(char, filenamelen+len+1);
      str[filenamelen+len] = 0;
      strcpy(str, path);
      fread(str + filenamelen, sizeof(char), len, f);
      texture = texture_load(str);
      if (texture) texture_retain(texture); /* automatically loaded textures are reference counted */
      free(str);
    }
    if ( mat.usedtexs & 2 ) /* normal tex */
    {
      fread(&len, sizeof(len), 1, f);
      fseek(f, len, SEEK_CUR);
    }
    if ( mat.usedtexs & 4 ) /* specular tex */
    {
      fread(&len, sizeof(len), 1, f);
      fseek(f, len, SEEK_CUR);
    }
    if ( mat.usedtexs & 8 ) /* emissive tex */
    {
      fread(&len, sizeof(len), 1, f);
      fseek(f, len, SEEK_CUR);
    }
    if ( mat.usedtexs & 16 ) /* ambient tex */
    {
      fread(&len, sizeof(len), 1, f);
      fseek(f, len, SEEK_CUR);
    }
    if ( mat.usedtexs & 32 ) /* lightmap */
    {
      fread(&len, sizeof(len), 1, f);
      fseek(f, len, SEEK_CUR);
    }
    if ( mat.usedtexs & 64 ) /* cubemap */
    {
      fread(&len, sizeof(len), 1, f);
      fseek(f, len, SEEK_CUR);
    }

    /* read number of indices, number of vertices and vertex flags */
    fread(&numindices, sizeof(numindices), 1, f);
    fread(&numvertices, sizeof(numvertices), 1, f);
    fread(&vertexflags, sizeof(vertexflags), 1, f);

    /* create buffer */
    buffer = mesh_addbuffer(mesh);
    mesh_material(mesh, buffer)->texture = texture;
    mesh_material(mesh, buffer)->color = mat.color;
    mesh_material(mesh, buffer)->emissive = mat.emissive;
    mesh_material(mesh, buffer)->specular = mat.specular;
    mesh_material(mesh, buffer)->shininess = color_alpha(mat.specular) / 255.0f;
    mesh_material(mesh, buffer)->blend = mat.blendmode;
    mesh_material(mesh, buffer)->flags = flags;

    /* read indices */
    for ( j = 0; j < numindices; j += 3 )
    {
      unsigned short indices[3];
      fread(indices, sizeof(indices), 1, f);
      mesh_addtriangle(mesh, buffer, indices[0], indices[1], indices[2]);
    }

    /* read vertices */
    for ( j = 0; j < numvertices; ++j )
    {
      lvec3_t position;
      lvec3_t normal;
      lvec3_t tangent;
      int color = _COLOR_WHITE;
      float tex0[2] = { 0, 0 };
      float tex1[2];
      int bones[4];
      float weights[4];

      fread(&position, sizeof(position), 1, f);
      if ( vertexflags & 1 ) fread(&normal, sizeof(normal), 1, f);
      else normal = lvec3(0, 0, -1);
      if ( vertexflags & 2 ) fread(&tangent, sizeof(tangent), 1, f);
      if ( vertexflags & 4 ) fread(&color, sizeof(color), 1, f);
      else color = _COLOR_WHITE;
      if ( vertexflags & 8 ) fread(tex0, sizeof(tex0), 1, f);
      if ( vertexflags & 16) fread(tex1, sizeof(tex1), 1, f);
      if ( vertexflags & 32 )
      {
        fread(bones, sizeof(bones), 1, f);
        fread(weights, sizeof(weights), 1, f);
      }
      mesh_addvertex(mesh, buffer, position.x, position.y, position.z, normal.x, normal.y, normal.z, tex0[0], tex0[1]);
    }
  }

  /* free temp resources */
  free(path);
  fclose(f);

  return mesh;
}

static struct mesh_t* _mesh_load_md2(const char* filename)
{
  lmd2_model_t*  mdl;
  struct mesh_t* mesh;
  struct frame_t* frame;
  int buffer;
  int i;

  mdl = lmd2_load(filename);
  if (!mdl) return NULL;

  /* create mesh */
  mesh = mesh_new();
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

  return mesh;
}
