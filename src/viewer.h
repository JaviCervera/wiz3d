#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include "types.h"

#define _CLEAR_NONE   0
#define _CLEAR_COLOR  1
#define _CLEAR_SKYBOX 2

#ifdef __cplusplus
extern "C"
{
#endif

struct texture_t;

struct viewer_t
{
  float             x, y, z;
  float             pitch, yaw, roll;
  int               vx;
  int               vy;
  int               vw;
  int               vh;
  int               clearmode;
  int               clearcolor;
  struct texture_t* skybox;
  bool_t            ortho;
  float             fov;
  float             min;
  float             max;
  bool_t            fogenabled;
  int               fogcolor;
  float             fogmin;
  float             fogmax;
};

struct viewer_t* viewer_new();
void viewer_delete(struct viewer_t* viewer);
void viewer_move(struct viewer_t* viewer, float x, float y, float z);
void viewer_turn(struct viewer_t* viewer, float pitch, float yaw, float roll);
void viewer_prepare(const struct viewer_t* viewer);

#ifndef SWIG
const struct viewer_t* _viewer_active();
const void* _viewer_activematrix();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VIEWER_H_INCLUDED */
