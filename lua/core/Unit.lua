Unit = {}

function Unit.new ()
local tptrA,tptrB = CreateUnit()
return {ptrA = tptrA,ptrB = tptrB}
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