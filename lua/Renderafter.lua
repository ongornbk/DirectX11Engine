require "core/Unit"
require "core/Chat"

Unit.Pick(hero)

local x,y = GetMousePosition()
if GetMouseState(0) == true
then
Unit.Goto(x,y)
else
Unit.CleanTasks()
end
if GetMousePressed(1) == true
then
Unit.SetPosition(x,y)
Unit.CleanTasks()
end

local hero_position_x,hero_position_y = Unit.GetPosition()

Camera.SetPosition(hero_position_x,hero_position_y)

GetUnitsInRange(500)
while(PopGroup())
do
Unit.Goto(hero_position_x,hero_position_y)
end