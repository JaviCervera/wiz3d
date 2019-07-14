import comp/component, typetraits

type
  CompSystem = object
    typeName: string
    components: seq[ComponentPtr]
    initProc: CompSystemProc
    runProc: CompSystemProc
    runCompsProc: CompSystemMultiProc
    deinitProc: CompSystemProc
  CompSystemPtr = ptr CompSystem
  CompSystemProc* = proc(comp:ComponentPtr)
  CompSystemMultiProc* = proc(comps:seq[ComponentPtr])

var registeredSystems: seq[CompSystem]

proc init(typeName: string, initProc: CompSystemProc, runProc: CompSystemProc, runCompsProc: CompSystemMultiProc, deinitProc: CompSystemProc) =
  var s:CompSystem
  s.typeName = typeName
  s.initProc = initProc
  s.runProc = runProc
  s.runCompsProc = runCompsProc
  s.deinitProc = deinitProc
  registeredSystems.add(s)

proc registerCompSystem*[T](initProc: CompSystemProc, runProc: CompSystemProc = nil, deinitProc: CompSystemProc = nil) =
  init(T.type.name, initProc, runProc, nil, deinitProc)

proc registerCompSystem*[T](initProc: CompSystemProc, runCompsProc: CompSystemMultiProc, deinitProc: CompSystemProc = nil) =
  init(T.type.name, initProc, nil, runCompsProc, deinitProc)

proc getComponentIndex(compSystem: CompSystem, c: ComponentPtr): int =
  result = -1
  for i, c2 in compSystem.components:
    if c == c2:
      result = i
      break

proc registerComponent*(c: ComponentPtr) =
  for i in 0..<registeredSystems.len:
    if registeredSystems[i].typeName == c.typeName and registeredSystems[i].getComponentIndex(c) == -1:
      registeredSystems[i].components.add(c)
      if registeredSystems[i].initProc != nil:
        registeredSystems[i].initProc(c)
      break

proc unregisterComponent*(c: ComponentPtr) =
  for i in 0..<registeredSystems.len:
    if registeredSystems[i].typeName == c.typeName:
      let ci = registeredSystems[i].getComponentIndex(c)
      if ci > -1:
        if registeredSystems[i].deinitProc != nil:
          registeredSystems[i].deinitProc(c)
        registeredSystems[i].components.delete(ci)
        break

# For every system that runs on each component,
# all the systems that run on all components are called
proc runCompSystems*() =
  var alreadyRan = false
  for s in registeredSystems:
    if s.runProc != nil:
      for c in s.components:
        s.runProc(c)
        alreadyRan = true
        for s in registeredSystems:
          if s.runCompsProc != nil and s.components.len > 0:
            s.runCompsProc(s.components)
  if not alreadyRan:
    for s in registeredSystems:
      if s.runCompsProc != nil and s.components.len > 0:
        s.runCompsProc(s.components)