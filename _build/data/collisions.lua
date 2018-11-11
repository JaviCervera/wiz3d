-- make screen resizable and set drawing color
screen.set(800, 600, false, true)
screen.setdrawcolor(color.rgb(240, 240, 240))

-- create floor
local floor = object.newcube()
object.move(floor, 0, -0.5, 4)
floor.colmode = _COL_BOX
floor.sx = 20
floor.sz = 20
object.material(floor, 0).diffuse = _COLOR_BLUE

-- load ball
local ball = object.load("sphere.assbin")
object.move(ball, 0, 0.5, -4)
ball.colmode = _COL_SPHERE
ball.radius = 0.5
object.material(ball, 0).diffuse = _COLOR_RED

-- create block
local block = object.newcube()
object.move(block, 0, 2, 0)
block.colmode = _COL_BOX
block.sx = 4
block.sy = 4
object.material(block, 0).diffuse = _COLOR_LIGHTGRAY

-- create ball shadow
local ball_shadow = object.newquad()
ball_shadow.pitch = 90
object.material(ball_shadow, 0).texture = texture.load("circle_shadow.png")
object.material(ball_shadow, 0).diffuse = _COLOR_BLACK
object.material(ball_shadow, 0).blend = _BLEND_ALPHA

-- create block shadow
local block_shadow = object.newquad()
block_shadow.pitch = 90
block_shadow.sx = 4
object.material(block_shadow, 0).diffuse = _COLOR_LIGHTGRAY
object.material(block_shadow, 0).blend = _BLEND_MUL

-- create and position viewer
local view = viewer.new()
viewer.move(view, 0, 7, -8)
viewer.turn(view, 45, 0, 0)

-- setup lighting
light.setambient(_COLOR_LIGHTGRAY)
local dir_light = light.new(_LIGHT_DIRECTIONAL)
dir_light.pitch = 15
dir_light.yaw = 60

local direction = 1
while screen.opened() and not input.keydown(_KEY_ESC) do
  -- move ball
  if input.keydown(_KEY_UP) then object.move(ball, 0, 0, 2 * screen.delta()) end
  if input.keydown(_KEY_DOWN) then object.move(ball, 0, 0, -2 * screen.delta()) end
  if input.keydown(_KEY_LEFT) then object.move(ball, -2 * screen.delta(), 0, 0) end
  if input.keydown(_KEY_RIGHT) then object.move(ball, 2 * screen.delta(), 0, 0) end

  -- move block
  object.move(block, 0, 2 * direction * screen.delta(), 0)
  if block.y >= 4 then
    block.y = 4
    direction = -1
  end
  if object.collidesobject(block, floor) or object.collidesobject(block, ball) then
    direction = 1
  end

  -- update shadows
  ball_shadow.x = ball.x
  ball_shadow.z = ball.z
  block_shadow.x = block.x
  block_shadow.z = block.z

  -- draw scene
  viewer.prepare(view)
  object.draw(floor)
  object.draw(ball)
  object.draw(block)
  object.draw(block_shadow)
  object.draw(ball_shadow)
  
  -- draw ui
  screen.refresh()
end
