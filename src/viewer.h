#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include "types.h"

#define CLEAR_NONE   0
#define CLEAR_COLOR  1
#define CLEAR_SKYBOX 2

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

EXPORT struct viewer_t* CALL viewer_new();
EXPORT void CALL viewer_delete(struct viewer_t* viewer);
EXPORT void CALL viewer_move(struct viewer_t* viewer, float x, float y, float z);
EXPORT void CALL viewer_turn(struct viewer_t* viewer, float pitch, float yaw, float roll);
EXPORT void CALL viewer_prepare(const struct viewer_t* viewer);

#ifndef SWIG
const struct viewer_t* _viewer_active();
const void* _viewer_activematrix();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VIEWER_H_INCLUDED */
