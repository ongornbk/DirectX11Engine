require "core/Unit"
require "core/Chat"

Unit.Pick(hero)
local hero_position_x,hero_position_y = Unit.GetPosition()

Camera.SetPosition(hero_position_x,hero_position_y)

--GetUnitsInRange(300)
--local unit = PopGroup()
--while(unit)
--do
--Unit.Pick(unit)
--Unit.Goto(hero_position_x,hero_position_y)
--unit = PopGroup()
--end