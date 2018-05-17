GetHero()
SetWalkingStance(1)
SetUnitSpeed(250)
InitializeUnit("../../content/Textures/models/barbarian.mod",100,20,0,0,0,false)
LockCameraOnUnit()
for i=200,1,-1 do
CreateUnit()
SetWalkingStance(1)
SetUnitSpeed(160)
InitializeUnit("../../content/Textures/models/barbarian.mod",100,20,0,0,0,true)
end
for i=200,1,-1 do
CreateUnit()
SetWalkingStance(1)
SetUnitSpeed(110)
InitializeUnit("../../content/Textures/models/enemy.mod",100,20,0,0,0,true)
end
for i=200,1,-1 do
CreateUnit()
SetWalkingStance(0)
SetUnitSpeed(120)
InitializeUnit("../../content/Textures/models/reaper.mod",111,20,0,0,0,true)
end
for i=200,1,-1 do
CreateUnit()
SetWalkingStance(0)
SetUnitSpeed(160)
InitializeUnit("../../content/Textures/models/paladin.mod",111,20,0,0,0,true)
end

