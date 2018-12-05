-- make screen resizable
screen.set(800, 600, false, true)

-- create draw functions
local draw_funcs = {
  function(self)
    screen.setdrawcolor(self.color)
    screen.drawpoint(self.x, self.y)
  end,
  function(self)
    screen.setdrawcolor(self.color)
    screen.drawline(self.x, self.y, self.w, self.z)
  end,
  function(self)
    screen.setdrawcolor(self.color)
    screen.drawrect(self.x, self.y, self.w, self.z)
  end,
  function(self)
    screen.setdrawcolor(self.color)
    screen.drawellipse(self.x, self.y, self.w, self.z)
  end
}

-- create primitives table
local primitives = {}

-- main loop
while screen.opened() and not input.keydown(_KEY_ESC) do
  -- add a primitive up to a max of 1000
  if #primitives < 1000 then
    table.insert(primitives, {
      x = math.random(0, screen.width()),
      y = math.random(0, screen.height()),
      z = math.random(0, screen.width()),
      w = math.random(0, screen.height()),
      color = color.rgb(math.random(0, 255), math.random(0, 255), math.random(0, 255)),
      draw = draw_funcs[math.random(#draw_funcs)]
    })
  end

  -- draw primitives
  screen.setup2d()
  screen.clear(_COLOR_BLACK)
  for _, prim in ipairs(primitives) do
    prim:draw()
  end
  screen.refresh()
end
