import math

type
  Vec2T*[T] = tuple[x: T, y:T]
  Vec3T*[T] = tuple[x: T, y:T, z:T]
  Vec4T*[T] = tuple[x: T, y:T, z:T, w:T]
  QuatT*[T] = tuple[w: T, x: T, y:T, z:T]
  Mat4T*[T] = array[0..15, T]
  Vec2* = Vec2T[float32]
  Vec2i* = Vec2T[int]
  Vec3* = Vec3T[float32]
  Vec3i* = Vec3T[int]
  Vec4* = Vec4T[float32]
  Vec4i* = Vec4T[int]
  Quat* = QuatT[float32]
  Mat4* = Mat4T[float32]

# Common procedures

proc deg*[T](r:T): T = r * T(57.2957795)
proc rad*[T](d:T): T = d * T(0.0174532925)

# Vec2 procedures

proc `-`*[T](a: Vec2T[T]): Vec2T[T] = (-a.x, -a.y)
proc `+`*[T](a, b: Vec2T[T]): Vec2T[T] = (a.x + b.x, a.y + b.y)
proc `-`*[T](a, b: Vec2T[T]): Vec2T[T] = (a.x - b.x, a.y - b.y)
proc `*`*[T](a, b: Vec2T[T]): Vec2T[T] = (a.x * b.x, a.y * b.y)
proc `/`*[T](a, b: Vec2T[T]): Vec2T[T] = (a.x / b.x, a.y / b.y)
proc `+`*[T](a: Vec2T[T], b: T): Vec2T[T] = (a.x + b, a.y + b)
proc `-`*[T](a: Vec2T[T], b: T): Vec2T[T] = (a.x - b, a.y - b)
proc `*`*[T](a: Vec2T[T], b: T): Vec2T[T] = (a.x * b, a.y * b)
proc `/`*[T](a: Vec2T[T], b: T): Vec2T[T] = (a.x / b, a.y / b)
proc dot*[T](a, b: Vec2T[T]): T = (a.x * b.x + a.y * b.y)
proc sqlen*[T](a: Vec2T[T]): T = a.dot(a)
proc len*[T](a: Vec2T[T]): T = a.sqlen.sqrt
proc norm*[T](a: Vec2T[T]): Vec2T[T] = (let ln = a.len; let iln = if ln > T(0): T(1) / ln else: T(0); a * iln)
proc mix*[T](a, b: Vec2T[T], t: T): Vec2T[T] = a + (b - a) * t
proc deg*[T](a: Vec2T[T]): Vec2T[T] = (a.x.deg, a.y.deg)
proc rad*[T](a: Vec2T[T]): Vec2T[T] = (a.x.rad, a.y.rad)

# Vec3 procedures

proc `-`*[T](a: Vec3T[T]): Vec3T[T] = (-a.x, -a.y, -a.z)
proc `+`*[T](a, b: Vec3T[T]): Vec3T[T] = (a.x + b.x, a.y + b.y, a.z + b.z)
proc `-`*[T](a, b: Vec3T[T]): Vec3T[T] = (a.x - b.x, a.y - b.y, a.z - b.z)
proc `*`*[T](a, b: Vec3T[T]): Vec3T[T] = (a.x * b.x, a.y * b.y, a.z * b.z)
proc `/`*[T](a, b: Vec3T[T]): Vec3T[T] = (a.x / b.x, a.y / b.y, a.z / b.z)
proc `+`*[T](a: Vec3T[T], b: T): Vec3T[T] = (a.x + b, a.y + b, a.z + b)
proc `-`*[T](a: Vec3T[T], b: T): Vec3T[T] = (a.x - b, a.y - b, a.z - b)
proc `*`*[T](a: Vec3T[T], b: T): Vec3T[T] = (a.x * b, a.y * b, a.z * b)
proc `/`*[T](a: Vec3T[T], b: T): Vec3T[T] = (a.x / b, a.y / b, a.z / b)
proc dot*[T](a, b: Vec3T[T]): T = (a.x * b.x + a.y * b.y + a.z * b.z)
proc cross*[T](a, b: Vec3T[T]): Vec3T[T] = (a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x)
proc sqlen*[T](a: Vec3T[T]): T = a.dot(a)
proc len*[T](a: Vec3T[T]): T = a.sqlen.sqrt
proc norm*[T](a: Vec3T[T]): Vec3T[T] = (let ln = a.len; let iln = if ln > T(0): T(1) / ln else: T(0); a * iln)
proc mix*[T](a, b: Vec3T[T], t: T): Vec3T[T] = a + (b - a) * t
proc deg*[T](a: Vec3T[T]): Vec3T[T] = (a.x.deg, a.y.deg, a.z.deg)
proc rad*[T](a: Vec3T[T]): Vec3T[T] = (a.x.rad, a.y.rad, a.z.rad)

# Vec4 procedures

proc `-`*[T](a: Vec4T[T]): Vec4T[T] = (-a.x, -a.y, -a.z, -a.w)
proc `+`*[T](a, b: Vec4T[T]): Vec4T[T] = (a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w)
proc `-`*[T](a, b: Vec4T[T]): Vec4T[T] = (a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w)
proc `*`*[T](a, b: Vec4T[T]): Vec4T[T] = (a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w)
proc `/`*[T](a, b: Vec4T[T]): Vec4T[T] = (a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w)
proc `+`*[T](a: Vec4T[T], b: T): Vec4T[T] = (a.x + b, a.y + b, a.z + b, a.w + b)
proc `-`*[T](a: Vec4T[T], b: T): Vec4T[T] = (a.x - b, a.y - b, a.z - b, a.w - b)
proc `*`*[T](a: Vec4T[T], b: T): Vec4T[T] = (a.x * b, a.y * b, a.z * b, a.w * b)
proc `/`*[T](a: Vec4T[T], b: T): Vec4T[T] = (a.x / b, a.y / b, a.z / b, a.w / b)
proc dot*[T](a, b: Vec4T[T]): T = (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w)
proc sqlen*[T](a: Vec4T[T]): T = a.dot(a)
proc len*[T](a: Vec4T[T]): T = a.sqlen.sqrt
proc norm*[T](a: Vec4T[T]): Vec4T[T] = (let ln = a.len; let iln = if ln > T(0): T(1) / ln else: T(0); a * iln)
proc mix*[T](a, b: Vec4T[T], t: T): Vec4T[T] = a + (b - a) * t
proc deg*[T](a: Vec4T[T]): Vec4T[T] = (a.x.deg, a.y.deg, a.z.deg, a.w.deg)
proc rad*[T](a: Vec4T[T]): Vec4T[T] = (a.x.rad, a.y.rad, a.z.rad, a.w.rad)

# Quat procedures

proc `+`[T](a, b: QuatT[T]): QuatT[T] = (a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z)

proc `*`[T](a: QuatT[T], b:T): QuatT[T] = (a.w * b, a.x * b, a.y * b, a.z * b)

proc conj*[T](a: QuatT[T]): QuatT[T] = (a.w, -a.x, -a.y, -a.z)

proc `*`*[T](a, b: QuatT[T]): QuatT[T] =
  (
    a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z,
    a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
    a.w*b.y + a.y*b.w + a.z*b.x - a.x*b.z,
    a.w*b.z + a.z*b.w + a.x*b.y - a.y*b.x
  )

proc `*`*[T](a: QuatT[T], v:Vec3T[T]): Vec3T[T] =
  let a = a * (T(0), v.x, v.y, v.z) * a.conj
  (a.x, a.y, a.z)

proc dot*[T](a, b: QuatT[T]): T = a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z

proc norm*[T](a:QuatT[T]): QuatT[T] =
  let sqm = a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w
  if sqm > T(0.00001) and (sqm - T(1)) > T(0.00001):
    a * (T(1) / T(sqm.sqrt))
  else:
    a

proc lerp*[T](a, b: QuatT[T], t: T): QuatT[T] = (a*(1-t) + b*t).norm

proc slerp*[T](a, b: QuatT[T], t: T): QuatT[T] =
  var d = dot(a, b)
  let q = if d < T(0): (d *= -T(1); b * -1) else: b
  if d < T(0.95):
    let ac = T(arccos(d))
    a * T(sin(ac*(T(1) - t))) + q * (T(sin(ac*t)) / T(sin(ac)))
  else:
    lerp(a, q, t)

proc rad*[T](a: QuatT[T]): T = arccos(a.w) * 2

proc deg*[T](a: QuatT[T]): T = deg(rad(a))

proc axis*[T](a: QuatT[T]): Vec3T[T] =
  let sc = T(sqrt(a.x*a.x + a.y*a.y + a.z*a.z))
  let isc = if sc > 0: T(1)/sc else: T(0)
  (a.x*isc, a.y*isc, a.z*isc)

proc toEuler*[T](a:QuatT[T]): Vec3T[T] =
  (
    T(arctan2(2 * (a.y*a.z + a.w*a.x), a.w*a.w - a.x*a.x - a.y*a.y + a.z*a.z)),
    T(arcsin(-2 * (a.x*a.z - a.w*a.y))),
    T(arctan2(2 * (a.x*a.y + a.w*a.z), a.w*a.w + a.x*a.x - a.y*a.y - a.z*a.z))
  )

proc fromAxis*[T](rad: T, axis:Vec3T[T]): QuatT[T] =
  let hr = rad / 2
  let v = axis.norm * hr.sin
  (T(hr.cos), v.x, v.y, v.z)

proc fromEuler*[T](rad: Vec3T[T]): QuatT[T] =
  let hx = rad.x / 2
  let hy = rad.y / 2
  let hz = rad.z / 2
  let sx = T(hx.sin)
  let sy = T(hy.sin)
  let sz = T(hz.sin)
  let cx = T(hx.cos)
  let cy = T(hy.cos)
  let cz = T(hz.cos)
  let w = cx * cy * cz + sx * sy * sz
  let x = sx * cy * cz - cx * sy * sz
  let y = cx * sy * cz + sx * cy * sz
  let z = cx * cy * sz - sx * sy * cz
  result = (w, x, y, z)

# Mat4 procedures

proc idMat4T*[T](): Mat4T[T] =
  [
    T(1), T(0), T(0), T(0),
    T(0), T(1), T(0), T(0),
    T(0), T(0), T(1), T(0),
    T(0), T(0), T(0), T(1)
  ]

proc idMat4*() : Mat4 = idMat4T[float32]()

proc `*`*[T](a, b: Mat4T[T]): Mat4T[T] =
  for i in 0..<4:
    let a0 = a[i]
    let a1 = a[1+4]
    let a2 = a[1+8]
    let a3 = a[1+12]
    result[i] = a0*b[0] + a1*b[1] + a2*b[2] + a3*b[3]
    result[i+4] = a0*b[4] + a1*b[5] + a2*b[6] + a3*b[7]
    result[i+8] = a0*b[8] + a1*b[9] + a2*b[10] + a3*b[11]
    result[i+12] = a0*b[12] + a1*b[13] + a2*b[14] + a3*b[15]

proc `*`*[T](a: Mat4T[T], v: Vec4T[T]): Vec4T[T] =
  var mat = idMat4T[T]()
  mat[12] = v.x
  mat[13] = v.y
  mat[14] = v.z
  mat[15] = v.w
  mat = a * mat
  (mat[12], mat[13], mat[14], mat[15])

proc translate*[T](a: Mat4T[T], v: Vec3T[T]): Mat4T[T] =
  result = idMat4T[T]()
  result[12] = v.x
  result[13] = v.y
  result[14] = v.z
  result = a * result

proc rotate*[T](a: Mat4T[T], rad: float, axis: Vec3T[T]): Mat4T[T] =
  let c = T(cos(rad))
  let s = T(sin(rad))
  let xx = axis.x * axis.x
  let xy = axis.x * axis.y
  let xz = axis.x * axis.z
  let yy = axis.y * axis.y
  let yz = axis.y * axis.z
  let zz = axis.z * axis.z
  result = idMat4T[T]()
  result[0] = xx * (1 - c) + c
  result[1] = xy * (1 - c) + axis.z * s
  result[2] = xz * (1 - c) - axis.y * s
  result[4] = xy * (1 - c) - axis.z * s
  result[5] = yy * (1 - c) + c
  result[6] = yz * (1 - c) + axis.x * s
  result[8] = xz * (1 - c) + axis.y * s
  result[9] = yz * (1 - c) - axis.x * s
  result[10] = zz * (1 - c) + c
  result = a * result

proc rotate*[T](a: Mat4T[T], q:QuatT[T]): Mat4T[T] = rotate(a, rad(q), axis(q))

proc scale*[T](a: Mat4T[T], v: Vec3T[T]): Mat4T[T] =
  result = idMat4T[T]()
  result[0] = v.x
  result[5] = v.y
  result[10] = v.z
  result = a * result

proc transpose*[T](a: Mat4T[T]): Mat4T[T] =
  for r in 0..<4:
    for c in 0..<4:
      result[c*4 + r] = a[r*4 + c]

proc inverse*[T](a: Mat4T[T]): Mat4T[T] =
  result[ 0] =  a[5] * a[10] * a[15] - a[5] * a[11] * a[14] - a[9] * a[6] * a[15] + a[9] * a[7] * a[14] + a[13] * a[6] * a[11] - a[13] * a[7] * a[10]
  result[ 4] = -a[4] * a[10] * a[15] + a[4] * a[11] * a[14] + a[8] * a[6] * a[15] - a[8] * a[7] * a[14] - a[12] * a[6] * a[11] + a[12] * a[7] * a[10]
  result[ 8] =  a[4] * a[ 9] * a[15] - a[4] * a[11] * a[13] - a[8] * a[5] * a[15] + a[8] * a[7] * a[13] + a[12] * a[5] * a[11] - a[12] * a[7] * a[ 9]
  result[12] = -a[4] * a[ 9] * a[14] + a[4] * a[10] * a[13] + a[8] * a[5] * a[14] - a[8] * a[6] * a[13] - a[12] * a[5] * a[10] + a[12] * a[6] * a[ 9]
  result[ 1] = -a[1] * a[10] * a[15] + a[1] * a[11] * a[14] + a[9] * a[2] * a[15] - a[9] * a[3] * a[14] - a[13] * a[2] * a[11] + a[13] * a[3] * a[10]
  result[ 5] =  a[0] * a[10] * a[15] - a[0] * a[11] * a[14] - a[8] * a[2] * a[15] + a[8] * a[3] * a[14] + a[12] * a[2] * a[11] - a[12] * a[3] * a[10]
  result[ 9] = -a[0] * a[ 9] * a[15] + a[0] * a[11] * a[13] + a[8] * a[1] * a[15] - a[8] * a[3] * a[13] - a[12] * a[1] * a[11] + a[12] * a[3] * a[ 9]
  result[13] =  a[0] * a[ 9] * a[14] - a[0] * a[10] * a[13] - a[8] * a[1] * a[14] + a[8] * a[2] * a[13] + a[12] * a[1] * a[10] - a[12] * a[2] * a[ 9]
  result[ 2] =  a[1] * a[ 6] * a[15] - a[1] * a[ 7] * a[14] - a[5] * a[2] * a[15] + a[5] * a[3] * a[14] + a[13] * a[2] * a[ 7] - a[13] * a[3] * a[ 6]
  result[ 6] = -a[0] * a[ 6] * a[15] + a[0] * a[ 7] * a[14] + a[4] * a[2] * a[15] - a[4] * a[3] * a[14] - a[12] * a[2] * a[ 7] + a[12] * a[3] * a[ 6]
  result[10] =  a[0] * a[ 5] * a[15] - a[0] * a[ 7] * a[13] - a[4] * a[1] * a[15] + a[4] * a[3] * a[13] + a[12] * a[1] * a[ 7] - a[12] * a[3] * a[ 5]
  result[14] = -a[0] * a[ 5] * a[14] + a[0] * a[ 6] * a[13] + a[4] * a[1] * a[14] - a[4] * a[2] * a[13] - a[12] * a[1] * a[ 6] + a[12] * a[2] * a[ 5]
  result[ 3] = -a[1] * a[ 6] * a[11] + a[1] * a[ 7] * a[10] + a[5] * a[2] * a[11] - a[5] * a[3] * a[10] - a[ 9] * a[2] * a[ 7] + a[ 9] * a[3] * a[ 6]
  result[ 7] =  a[0] * a[ 6] * a[11] - a[0] * a[ 7] * a[10] - a[4] * a[2] * a[11] + a[4] * a[3] * a[10] + a[ 8] * a[2] * a[ 7] - a[ 8] * a[3] * a[ 6]
  result[11] = -a[0] * a[ 5] * a[11] + a[0] * a[ 7] * a[ 9] + a[4] * a[1] * a[11] - a[4] * a[3] * a[ 9] - a[ 8] * a[1] * a[ 7] + a[ 8] * a[3] * a[ 5]
  result[15] =  a[0] * a[ 5] * a[10] - a[0] * a[ 6] * a[ 9] - a[4] * a[1] * a[10] + a[4] * a[2] * a[ 9] + a[ 8] * a[1] * a[ 6] - a[ 8] * a[2] * a[ 5]
  let d = a[0] * result[0] + a[1] * result[4] + a[2] * result[8] + a[3] * result[12]
  if abs(d) <= T(0.00001):
    result = a
  let id = T(1) / d
  for i in 0..<16:
    result[i] *= id

proc orthoLh*[T](left, right, bottom, top, near, far: T): Mat4T[T] =
  let a = 2 / (right - left)
  let b = 2 / (top - bottom)
  let c = 2 / (far - near)
  let tx = -(right+left) / (right-left)
  let ty = -(top+bottom) / (top-bottom)
  let tz = -(far+near) / (far-near)
  result = idMat4T[T]()
  result[0] = a
  result[5] = b
  result[10] = c
  result[12] = tx
  result[13] = ty
  result[14] = tz

proc frustumLh*[T](left, right, bottom, top, near, far: T): Mat4T[T] =
  result = idMat4T[T]()
  result[0]  = 2 * near / (right - left)
  result[5]  = 2 * near / (top - bottom)
  result[8]  = -(right + left) / (right - left)
  result[9]  = -(top + bottom) / (top - bottom)
  result[10] = (far + near) / (far - near)
  result[11] = 1
  result[14] = -(2 * far * near) / (far - near)
  result[15] = 0

proc perspectiveLh*[T](fovy, aspect, near, far: T): Mat4T[T] =
  let tangent = T(tan(fovy/2))
  let height = near * tangent
  let width = height * aspect
  frustumLh(-width, width, -height, height, near, far)

proc lookAtLh*[T](center, eye, up: Vec3T[T]): Mat4T[T] =
  let z = norm(eye - center)
  let x = norm(cross(up, z))
  let y = norm(cross(z, x))
  result = idMat4T[T]()
  result[0] = x.x
  result[1] = y.x
  result[2] = z.x
  result[4] = x.y
  result[5] = y.y
  result[6] = z.y
  result[8] = x.z
  result[9] = y.z
  result[10] = z.z
  result = translate(result, center * -1)

proc orthoRh*[T](left, right, bottom, top, near, far: T): Mat4T[T] =
  let a = 2 / (right - left)
  let b = 2 / (top - bottom)
  let c = -2 / (far - near)
  let tx = -(right+left) / (right-left)
  let ty = -(top+bottom) / (top-bottom)
  let tz = -(far+near) / (far-near)
  result = idMat4T[T]()
  result[0] = a
  result[5] = b
  result[10] = c
  result[12] = tx
  result[13] = ty
  result[14] = tz

proc frustumRh*[T](left, right, bottom, top, near, far: T): Mat4T[T] =
  result = idMat4T[T]()
  result[0]  = 2 * near / (right - left)
  result[5]  = 2 * near / (top - bottom)
  result[8]  = (right + left) / (right - left)
  result[9]  = (top + bottom) / (top - bottom)
  result[10] = -(far + near) / (far - near)
  result[11] = -1
  result[14] = -(2 * far * near) / (far - near)
  result[15] = 0

proc perspectiveRh*[T](fovy, aspect, near, far: T): Mat4T[T] =
  let tangent = T(tan(fovy/2))
  let height = near * tangent
  let width = height * aspect
  frustumRh(-width, width, -height, height, near, far)

proc lookAtRh*[T](center, eye, up: Vec3T[T]): Mat4T[T] =
  let z = norm(center - eye)
  let x = norm(cross(up, z))
  let y = norm(cross(z, x))
  result = idMat4T[T]()
  result[0] = x.x
  result[1] = y.x
  result[2] = z.x
  result[4] = x.y
  result[5] = y.y
  result[6] = z.y
  result[8] = x.z
  result[9] = y.z
  result[10] = z.z
  result = translate(result, center * -1)

proc transformMat4T*[T](position: Vec3T[T], rotation: QuatT[T], scale: Vec3T[T]): Mat4T[T] =
  idMat4T[T]().translate(position).rotate(rad(rotation), axis(rotation)).scale(scale)

proc billboardMat4T*[T](view:Mat4T[T], pos: Vec3T[T], radSpin: T, size: Vec2, upfront: bool): Mat4T[T] =
  result = view.transpose
  result[3] = 0
  result[7] = 0
  result[11] = 0
  result[12] = pos.x
  result[13] = pos.y
  result[14] = pos.z
  result[15] = 1
  if upfront:
    result[4] = 0
    result[5] = 1
    result[6] = 0
  result = result.rotate(radSpin, (T(0), T(0), T(1))).scale((size.x, size.y, T(1)))