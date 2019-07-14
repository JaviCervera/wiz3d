import "../compsystem", "../math3d", component, typetraits

type
  Transform* = object of Component
    position: Vec3
    quaternion: Quat
    euler: Vec3
    scale: Vec3
    matrix: Mat4
    isDirty: bool
    parent: TransformPtr
    children: seq[TransformPtr]
  TransformPtr* = ptr Transform

proc getPosition*(t: TransformPtr): Vec3 = t.position
proc setPosition*(t: TransformPtr, v: Vec3) = (t.position = v; t.isDirty = true)
proc getQuaternion*(t: TransformPtr): Quat = t.quaternion
proc setQuaternion*(t: TransformPtr, q: Quat) = (t.quaternion = q; t.euler = q.toEuler.deg; t.isDirty = true)
proc getEuler*(t: TransformPtr): Vec3 = t.euler
proc setEuler*(t: TransformPtr, v: Vec3) = (t.euler = v; t.quaternion = fromEuler(v.rad); t.isDirty = true)
proc getScale*(t: TransformPtr): Vec3 = t.scale
proc setScale*(t: TransformPtr, v: Vec3) = (t.scale = v; t.isDirty = true)

proc getMatrix*(t: TransformPtr): ptr Mat4 =
  if t.isDirty:
    # TODO Calculate matrix
    t.isDirty = false
  addr t.matrix

proc getParent*(t: TransformPtr): TransformPtr = t.parent

proc hasChild(t: TransformPtr, c: TransformPtr): bool =
  for ch in t.children:
    if ch == c:
      result = true
      break

proc removeChild*(t: TransformPtr, c: TransformPtr) =
  for i, ch in t.children:
    if ch == c:
      t.children.delete(i)
      c.parent = nil
      break

proc addChild*(t: TransformPtr, c: TransformPtr) =
  if not t.hasChild(c):
    t.children.add(c)
    if c.parent != nil:
      c.parent.removeChild(c)
    c.parent = t

# Create system for this component type

proc initTransform(c: ComponentPtr) =
  let t = cast[TransformPtr](c)
  t.quaternion = (1'f32, 0'f32, 0'f32, 0'f32)
  t.matrix = idMat4()

registerCompSystem[Transform](initTransform)