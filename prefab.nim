import comp/camera, entity, world

proc addCamera*(world: WorldPtr, name: string): EntityPtr =
    result = world.addEntity(name)
    discard addComponent[Camera](result)

#proc addLight*(world: WorldPtr, name: string, lightType: int): EntityPtr
#proc addMesh*(world: WorldPtr, name: string, mesh: MeshPtr): EntityPtr
#proc addSprite*(world: WorldPtr, name: string, tex: TexturePtr): EntityPtr