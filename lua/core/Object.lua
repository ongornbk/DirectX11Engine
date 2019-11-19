Object = {}

Object.lastCreatedObject = 0
Object.pickedObject = 0

function Object.Delete()
    DeleteObject(Object.pickedObject)
end

function Object.Pick(object)
    Object.pickedObject = object
end

function  Object.SetRenderingFlag(bool)
    SetRenderingFlag(Object.pickedObject,bool)
end

function Object.SetSelectableFlag(bool)
    SetSelectableFlag(Object.pickedObject,bool)
end

function Object.SetPushableFlag(bool)
    SetPushableFlag(Object.pickedObject,bool)
end

function Object.SetShadowFlag(bool)
    SetShadowFlag(Object.pickedObject,bool)
end

function Object.SetCollisionPriority(priority)
    SetCollisionPriority(Object.pickedObject,priority)
end