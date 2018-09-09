ROTATION_SPEED = 32
TEXT = "Hover Bike by Ptis is licensed under CC Attribution-NonCommercial"

-- make screen resizable
screen.set(800, 600, false, true)

-- create and position viewer
local view = viewer.new()
view.color = _COLOR_DARKGRAY
viewer.move(view, 0, 4, -8)
viewer.turn(view, 20, 0, 0)

-- create light
local dir_light = light.new(_LIGHT_DIRECTIONAL)
light.turn(dir_light, 45, 45)

-- load hoverbike
local hoverbike = object.load("hoverbike.msh")

while screen.opened() and not input.keydown(_KEY_ESC) do
  -- turn model
  object.turn(hoverbike, 0, ROTATION_SPEED * screen.delta(), 0)

  -- draw scene
  viewer.prepare(view)
  object.draw(hoverbike)

  -- draw ui
  screen.setup2d()
  screen.drawtext(TEXT, (screen.width() - screen.textwidth(TEXT)) / 2, 2)
  screen.refresh()
end
