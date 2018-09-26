LoadInstance("../saves/map.save")
tileSelected = 0
SetInterface(1)
ResumeGame()

CreateDoodads()
InitializeDoodads("well0",125,50,0,0,0,false)

CreateUnit()
PickLastCreatedUnit()
PushUnitVariable("hero")
SetWalkingStance(1)
SetUnitSpeed(250)
InitializeUnit("barbarian.mod",100,20,100,100,0,false)
for i=1,15,1
do
CreateUnit()
PickLastCreatedUnit()
SetWalkingStance(1)
SetUnitSpeed(100)
InitializeUnit("enemy.mod",100,18,250,350,0,true)
end
--LockCameraOnUnit()