require "core/Unit"
require "core/Chat"

Unit.Pick(hero)
local hero_position_x,hero_position_y = Unit.GetPosition()

Camera.SetPosition(hero_position_x,hero_position_y)

GetUnitsInRange(hero,300.0)
local unit = PopGroup()
while(unit > 0)
do
Unit.Pick(unit)
if Unit.Attack(hero) == false
then
    AttackSound()
end
AddUnitToGroup(pullgroup,unit)
unit = PopGroup()
end

