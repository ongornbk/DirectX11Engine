GetUnitVariable("hero")
local x,y = GetUnitPosition()
GetUnitsInRange(200)
while(PopGroup())
do

SetTaskGotoPoint(x,y)
end
