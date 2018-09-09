ROTATION_SPEED = 90

-- create and position viewer
local view = viewer.new()
viewer.move(view, 0, 2, -2)
viewer.turn(view, 45, 0, 0)

-- setup lighting
local dir_light = light.new(_LIGHT_DIRECTIONAL)
light.turn(dir_light, 45, 45)

-- create a cube
local cube = object.newcube()
object.material(cube, 0).texture = texture.load("box-texture.png")

while screen.opened() and not input.keydown(_KEY_ESC) do
  object.turn(cube, 0, ROTATION_SPEED * screen.delta(), 0)

  -- draw scene
  viewer.prepare(view)
  object.draw(cube)

  -- draw ui
  screen.setup2d()
  screen.drawtext(math.floor(screen.fps()) .. " FPS", 4, 4)
  screen.refresh()
end
