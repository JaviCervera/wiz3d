import comp/component, comp/transform, compsystem, typetraits

type
  Entity* = object
    name*: string
    components: seq[ComponentPtr]
    transform: TransformPtr
  EntityPtr* = ptr Entity

proc hasComponent*[T](entity: EntityPtr): bool =
  for c in entity.components:
    if c.typeName == T.type.name:
      result = true
      break

proc addComponent*[T](entity: EntityPtr): ptr T =
  if not hasComponent[T](entity):
    result = create(T)
    result.typeName = T.type.name
    result.owner = entity
    entity.components.add(result)
    registerComponent(result)

proc removeComponent*[T](entity: EntityPtr) =
  if T isnot Transform:
    for i, c in entity.components:
      if c.typeName == T.type.name:
        unregisterComponent(c)
        entity.components.delete(i)
        dealloc(c)
        break

proc removeComponents*(entity: EntityPtr) =
  for c in entity.components:
    unregisterComponent(c)
    dealloc(c)
  entity.components.setLen(0)

proc getComponent*[T](entity: EntityPtr): ptr T =
  for c in entity.components:
    if c.typeName == T.type.name:
      result = cast[ptr T](c)
      break

proc getTransform*(entity: EntityPtr): TransformPtr =
  if entity.transform == nil:
    entity.transform = getComponent[Transform](entity)
  result = entity.transform

proc getOwner*(c: ComponentPtr): EntityPtr =
  cast[EntityPtr](c.owner)