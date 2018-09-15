ROTATION_SPEED = 32
TEXT = "Hover Bike by Ptis is licensed under CC Attribution-NonCommercial"

-- make screen resizable
screen.set(800, 600, false, true)

-- create and position viewer
local view = viewer.new()
view.color = _COLOR_DARKGRAY
viewer.move(view, 0, 4, -8)
viewer.turn(view, 20, 0, 0)

-- setup lighting
material.setshininesspower(2)
local dir_light = light.new(_LIGHT_DIRECTIONAL)
light.turn(dir_light, 45, -45)

-- load hoverbike
local hoverbike = object.load("hoverbike.assbin")
local mat0 = object.material(hoverbike, 0)
local mat1 = object.material(hoverbike, 1)
mat0.texture = texture.load("bike.png")
mat0.diffuse = _COLOR_WHITE
mat0.specular = _COLOR_WHITE
mat1.texture = texture.load("glass.png")
mat1.diffuse = _COLOR_WHITE
mat1.specular = _COLOR_WHITE
mat1.blend = _BLEND_ALPHA
hoverbike.sx = 0.025
hoverbike.sy = 0.025
hoverbike.sz = 0.025

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
