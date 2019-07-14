import entity, comp/transform, compsystem

type
  World* = object
    entities: seq[EntityPtr]
  WorldPtr* = ptr World

# Forward declarations
proc removeEntities*(world: WorldPtr)
proc findEntity*(world: WorldPtr, name: string): EntityPtr

proc createWorld*(): WorldPtr =
  result = create(World)

proc destroy*(world: WorldPtr) =
  world.removeEntities()
  dealloc(world)

proc addEntity*(world: WorldPtr, name: string): EntityPtr =
  if world.findEntity(name) == nil:
    result = create(Entity)
    result.name = name
    discard addComponent[Transform](result)
    world.entities.add(result)

proc removeEntity*(world: WorldPtr, entity: EntityPtr) =
  for i, e in world.entities:
    if e == entity:
      entity.removeComponents()
      dealloc(entity)
      world.entities.delete(i)
      break

proc removeEntities*(world: WorldPtr) =
  for e in world.entities:
    e.removeComponents()
    dealloc(e)
  world.entities.setLen(0)

proc getNumEntities*(world: WorldPtr): int =
  world.entities.len

proc getEntity*(world: WorldPtr, index: int): EntityPtr =
  world.entities[index]

proc findEntity*(world: WorldPtr, name: string): EntityPtr =
  for e in world.entities:
    if e.name == name:
      result = e
      break

proc update*(world: WorldPtr) =
  runCompSystems()

proc draw*(world: WorldPtr) =
  discard