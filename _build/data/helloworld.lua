TEXT = "Hello, world!"

while screen.opened() and not input.keydown(_KEY_ESC) do
  screen.setup2d()
  screen.clear(color.multiply(_COLOR_BLUE, 0.5))
  screen.setdrawcolor(_COLOR_YELLOW)
  screen.drawtext(TEXT, (screen.width() - screen.textwidth(TEXT)) / 2, (screen.height() - screen.textheight(TEXT)) / 2)
  screen.refresh()
end
