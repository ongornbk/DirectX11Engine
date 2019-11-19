require "core/Object"

Unit = {}

Unit.lastCreatedUnit = 0
Unit.pickedUnit = 0

function Unit.new ()
Unit.lastCreatedUnit = CreateUnit()
Object.lastCreatedObject = Unit.lastCreatedUnit
return Unit.lastCreatedUnit
end

function Unit.Pick(object)
Unit.pickedUnit = object
Object.Pick(object)
end

function Unit.SetWalkingStance (stance)
SetWalkingStance(Unit.pickedUnit,stance)
end

function Unit.SetSpeed (speed)
SetUnitSpeed(Unit.pickedUnit,speed)
end

function Unit.Initialize (model,size,collision,x,y,z,wandering)
InitializeUnit(Unit.pickedUnit,tostring(model) .. ".mod",size,collision,x,y,z,wandering)
end

function Unit.GetPosition ()
return GetUnitPosition(Unit.pickedUnit)
end

function Unit.Goto (x,y)
SetTaskGotoPoint(Unit.pickedUnit,x,y)
end

function Unit.Attack (target)
return SetTaskAttack(Unit.pickedUnit,target)
end

function Unit.SetPosition (x,y)
SetUnitPosition(Unit.pickedUnit,x,y)
end

function Unit.CleanTasks ()
CleanTasks(Unit.pickedUnit)
end

function Unit.ToggleRunning()
ChangeWalkingStance(Unit.pickedUnit)
end

function Unit.ApplyColorFilter(red,green,blue,alpha)
    ApplyColorFilter(Unit.pickedUnit,red,green,blue,alpha)
    end


