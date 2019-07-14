import "../compsystem", "../entity", "../math3d"
import component, math, transform, typetraits

type
  Camera* = object of Component
    viewport*: Vec4i
    clearMode*: CameraClearMode
    clearColor*: uint
    isOrtho*: bool
    fov: float32
    distance: Vec2
    isFogEnabled: bool
    fogColor: uint
    fogDistance: Vec2
    projection: Mat4
    view: Mat4
  CameraPtr* = ptr Camera
  CameraClearMode* = enum
    cmNone, cmColor, cmSkybox

# Create system for this component type

proc initCamera(c: ComponentPtr) =
  let cam = cast[CameraPtr](c)
  cam.projection = idMat4()
  cam.view = idMat4()

proc runCamera(c: ComponentPtr) =
  let cam = cast[CameraPtr](c)

  # Set viewport
  # ...

  # Prepare projection matrix
  let ratio = if cam.viewport.w != 0: cam.viewport.z / cam.viewport.w else: 1'f32
  if (cam.isOrtho):
    let height: float32 = cam.distance[0] * tan(rad(cam.fov)) * 2
    let width: float32 = height * ratio
    cam.projection = orthoLh(-width, width, -height, height, cam.distance[0], cam.distance[1])
  else:
    cam.projection = perspectiveLh(rad(cam.fov), ratio, cam.distance[0], cam.distance[1])
  
  # Prepare view matrix
  let transform = cam.getOwner().getTransform()
  cam.view = idMat4().rotate(-transform.getQuaternion().rad, transform.getQuaternion().axis).translate(-transform.getPosition())

registerCompSystem[Camera](initCamera, runCamera)