Camera = {}

function Camera.SetPosition (x,y)
SetCameraPosition(x,y)
end

function Camera.LockOnUnit ()
LockCameraOnUnit()
end

function Camera.Up (x,y,z,w)
SetCameraUp(x,y,z,w)
end

function Camera.LookAt (x,y,z,w)
SetCameraLookAt(x,y,z,w)
end

