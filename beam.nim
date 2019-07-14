# In order to build, you need to install dependencies with nimble:
# nimble install opengl
# nimble install nimrod-glfw
import comp/camera
import comp/transform

import entity, prefab, renderer, world

import glfw3 as glfw

# Create window
if glfw.Init() == 0:
  raise newException(Exception, "Failed to initialize GLFW")
glfw.WindowHint(glfw.SAMPLES, 4)
var win = glfw.CreateWindow(800, 600, "Nim Beam example", nil, nil)
glfw.MakeContextCurrent(win)

# Init renderer
if not rInit((800, 600)):
  raise newException(Exception, "Failed to initialize renderer")

# Create world and entities
let wld = createWorld()
let empty = wld.addEntity("Empty")
let cam = wld.addCamera("MainCamera")

# Main loop
while glfw.WindowShouldClose(win) == 0:
  wld.update()
  wld.draw()
  glfw.PollEvents()
  glfw.SwapBuffers(win)

wld.destroy()