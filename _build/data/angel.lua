ROTATION_SPEED = 32
TEXT = "Frank by misterdevious is licensed under CC Attribution-NonCommercial-ShareAlike"

-- make screen resizable and set drawing color
screen.set(800, 600, false, true)
screen.setdrawcolor(color.rgb(240, 240, 240))

-- create and position viewer
local view = viewer.new()
view.color = color.rgb(15, 15, 15)
viewer.move(view, 7, 7, -7)
viewer.turn(view, 37.5, -45, 0)

-- setup lighting
light.setambient(color.rgb(15, 15, 15))
local dir_light = light.new(_LIGHT_DIRECTIONAL)
dir_light.color = color.rgb(100, 100, 100)
local point_light1 = light.new(_LIGHT_POINT)
light.move(point_light1, 0, 0, -2)
point_light1.color = color.rgb(255, 100, 0)
local point_light2 = light.new(_LIGHT_POINT)
light.move(point_light2, 0, 8, 4)
point_light2.color = color.rgb(0, 100, 255)

-- load object (contains embedded texture)
local angel = object.load("angel.assbin")
object.turn(angel, 90, 0, 0)

local value = 0
while screen.opened() and not input.keydown(_KEY_ESC) do
  -- rotate statue
  object.turn(angel, 0, ROTATION_SPEED * screen.delta(), 0)

  -- update lighting
  value = value + screen.delta()
  local sin = 0.5 + math.abs(math.sin(value)) * 0.5
  local cos = 0.5 + math.abs(math.cos(value)) * 0.5
  point_light1.att = 2 * sin
  point_light2.att = 10 * cos

  -- draw scene
  viewer.prepare(view)
  object.draw(angel)
  
  -- draw ui
  screen.setup2d()
  screen.drawtext(TEXT, (screen.width() - screen.textwidth(TEXT)) / 2, 8)
  screen.refresh()
end
