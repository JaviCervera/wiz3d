-- make screen resizable
screen.set(800, 600, false, true)

-- create and position viewer
local view = viewer.new()
view.color = _COLOR_DARKGRAY
viewer.move(view, 0, 2, -4)
viewer.turn(view, 15, 0, 0)

-- load md2 object
local md2 = object.load("german.md2")
md2.animmode = _ANIM_LOOP
object.turn(md2, 0, 90, 0)

local walking = false
local space_down = false

while screen.opened() and not input.keydown(_KEY_ESC) do
  -- update animation
  if input.keydown(_KEY_SPACE)then 
    if not space_down then walking = not walking end
    space_down = true
  else
    space_down = false
  end
  if walking then
    md2.animmin = 31
    md2.animmax = 0 --51
  else
    md2.animmin = 0
    md2.animmax = 25
  end

  -- draw scene
  viewer.prepare(view)
  object.draw(md2)

  -- draw ui
  screen.setup2d()
  screen.drawtext(math.floor(screen.fps()) .. " FPS", 4, 4)
  screen.drawtext("Frame: " .. math.floor(md2.animframe), 4, 16)
  screen.refresh()
end
