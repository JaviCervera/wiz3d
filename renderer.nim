import math3d
import opengl

# Internal vars
var screenSize: Vec2i

# Forward declarations
proc rSetScreenSize*(size:Vec2i)
proc rSetup3D*(viewport:Vec4i)

proc rInit*(size:Vec2i): bool =
  # Init OpenGL
  loadExtensions()
  rSetScreenSize(size)
  rSetup3D((0, 0, size.x, size.y))
  result = true

proc rSetScreenSize*(size:Vec2i) =
  screenSize = size

proc rSetup3D*(viewport:Vec4i) =
  # Setup 3D
  glEnable(GL_BLEND)
  glEnable(GL_DEPTH_TEST)
  glEnable(GL_SCISSOR_TEST)
  glDepthFunc(GL_LEQUAL)
  glFrontFace(GL_CW)
  #rSetBlendMode(bmSolid)
  #rSetCulling(true)
  #rSetDepthWrite(true)
  #rSetTextures(0, 0, 0, 0, 0)
