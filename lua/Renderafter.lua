require "core/Unit"

Unit.Pick(hero)
local position = Unit.GetPosition()
GetUnitsInRange(200)
while(PopGroup())
do
Unit.Goto(position)
end
