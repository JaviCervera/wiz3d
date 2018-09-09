while screen.opened() and not input.keydown(_KEY_ESC) do
  screen.setup2d()
  screen.clear(_COLOR_BLACK)
  screen.drawtext("Hello, world!", 0, 0)
  screen.refresh()
end
