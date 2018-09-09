#include "../lib/ode/ode.h"
#include "physics.h"

static dWorldID _physics_world;
static dSpaceID _physics_space;
static dJointGroupID _physics_jointgroup;

void _physics_callback(void *data, dGeomID o1, dGeomID o2)
{

}

void _physics_init()
{
  dInitODE();
  _physics_world = dWorldCreate();
  _physics_space = dSimpleSpaceCreate(0);
  _physics_jointgroup = dJointGroupCreate(0);
  /*dCreatePlane(_physics_space, 0, 1, 0, 0);
  dWorldSetGravity(_physics_world, 0, -1, 0);
  dWorldSetERP(_physics_world, 0.2f);
  dWorldSetCFM(_physics_world, 1e-5);
  dWorldSetContactMaxCorrectingVel(_physics_world, 0.9f);
  dWorldSetContactSurfaceLayer(_physics_world, 0.001f);
  dWorldSetAutoDisableFlag(_physics_world, TRUE);
  dContactSetMode(dContactBounce);
  dContactSetBounce(0.1f);
  dContactSetMu(48);*/
}

void _physics_update(float delta)
{
  dSpaceCollide(_physics_space, NULL, &_physics_callback);
  dWorldQuickStep(_physics_world, delta);
  dJointGroupEmpty(_physics_jointgroup);
}

void _physics_finish()
{
  dJointGroupDestroy(_physics_jointgroup);
  dSpaceDestroy(_physics_space);
  dWorldDestroy(_physics_world);
  dCloseODE();
}

void* _physics_createbox(float w, float h, float d)
{
  dGeomID shape;

  shape = dCreateBox(_physics_space, w, h, d);
  /*gGeomSetData(shape, void*);*/
  return shape;
}

void _physics_deleteshape(void* shape)
{

}
