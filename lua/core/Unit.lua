Unit = {}



function Unit.new ()
local tptrA,tptrB = CreateUnit()
PickUnit(tptrA,tptrB)
return {ptrA = tptrA,ptrB = tptrB}
end

function Unit.delete()
DeleteUnit()
end

function Unit.Pick(unit)
PickUnit(unit.ptrA,unit.ptrB)
end

function Unit.SetWalkingStance (stance)
SetWalkingStance(stance)
end

function Unit.SetSpeed (speed)
SetUnitSpeed(speed)
end

function Unit.Initialize (model,size,collision,x,y,z,wandering)
InitializeUnit(tostring(model) .. ".mod",size,collision,x,y,z,wandering)
end

function Unit.GetPosition ()
return GetUnitPosition()
end

function Unit.Register (name)
PushUnitVariable(name)
end

function Unit.Goto (x,y)
SetTaskGotoPoint(x,y)
end

function Unit.SetPosition (x,y)
SetUnitPosition(x,y,0)
end

function Unit.CleanTasks ()
CleanTasks()
end

function Unit.GetFlag(flag)
return GetRenderContainerFlag(flag)
end

