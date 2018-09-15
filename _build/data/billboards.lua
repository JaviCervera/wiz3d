NUM_CUBES = 64
ROTATION_SPEED = 32

-- make screen resizable
screen.set(800, 600, false, true)

-- create and position viewer
local view = viewer.new()
view.clearcolor = _COLOR_WHITE
viewer.turn(view, 45, -45, 0)

-- load texture
local tex = texture.load("smile.png")

-- create billboards
local billboards = {}
local x = -8
local z = -8
for i = 1, NUM_CUBES do
  local bb = object.newquad()
  bb.billboard = _BILLBOARD_FACE
  bb.x = x
  bb.z = z
  object.material(bb, 0).texture = tex
  object.material(bb, 0).diffuse = color.rgb(math.random(0, 255), math.random(0, 255), math.random(0, 255))
  object.material(bb, 0).blend = _BLEND_ALPHA
  table.insert(billboards, bb)
  x = x + 2
  if x >= 8 then x = -8; z = z + 2; end
end

while screen.opened() and not input.keydown(_KEY_ESC) do
  -- update viewer
  viewer.turn(view, 0, ROTATION_SPEED * screen.delta(), 0)
  view.x = 0
  view.y = 0
  view.z = 0
  viewer.move(view, 0, 0, -8)

  -- draw scene
  viewer.prepare(view)
  for _, bb in ipairs(billboards) do
    object.draw(bb)
  end

  -- draw ui
  screen.setup2d()
  screen.drawtext(math.floor(screen.fps()) .. " FPS", 4, 4)
  screen.refresh()
end
