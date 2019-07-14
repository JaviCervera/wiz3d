type
    Component* = object {.inheritable.}
        typeName*: string
        owner*: pointer # It's an EntityPtr, but it is not defined here yet
    ComponentPtr* = ptr Component