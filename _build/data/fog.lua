NUM_CUBES = 16 * 50
ROTATION_SPEED = 32

-- make screen resizable
screen.set(800, 600, false, true)

-- setup lighting
local dir_light = light.new(_LIGHT_DIRECTIONAL)
light.turn(dir_light, 45, 45)

-- create and position viewer
local view = viewer.new()
view.color = _COLOR_DARKGRAY
viewer.move(view, 0, 0, -7)
view.max = 5000
view.fogenabled = true
view.fogmax = 20

-- create rows of cubes
local cubes = {}
local x = -7
local z = NUM_CUBES / 16 * 2 - 2
for i = 1, NUM_CUBES, 2 do
  local cube
  if i == 1 then
    cube = object.newcube()
    object.material(cube, 0).diffuse = _COLOR_BROWN
  else
    cube = object.clone(cubes[1])
  end
  cube.x = x
  cube.y = -1.5
  cube.z = z
  table.insert(cubes, cube)
  cube = object.clone(cubes[1])
  cube.x = x
  cube.y = 1.5
  cube.z = z
  table.insert(cubes, cube)
  x = x + 2
  if x > 7 then x = -7; z = z - 2; end
end

while screen.opened() and not input.keydown(_KEY_ESC) do
  -- turn objects
  for _, cube in ipairs(cubes) do
    object.turn(cube, 0, ROTATION_SPEED * screen.delta(), 0)
  end

  -- draw scene
  viewer.prepare(view)
  for _, cube in ipairs(cubes) do
    object.draw(cube)
  end

  -- draw ui
  screen.setup2d()
  screen.drawtext(math.floor(screen.fps()) .. " FPS", 4, 4)
  screen.refresh()
end
