LoadInstance("../saves/map.save")
tileSelected = 0
SetInterface(1)
ResumeGame()

CreateUnit()
PickLastCreatedUnit()
PushUnitVariable("hero")
SetWalkingStance(1)
SetUnitSpeed(250)
InitializeUnit("barbarian.mod",100,20,100,100,0,false)
--LockCameraOnUnit()