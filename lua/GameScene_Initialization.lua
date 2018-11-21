require "core/Unit"

LoadInstance("../saves/map.save")
tileSelected = 0
SetInterface(1)
ResumeGame()
hero = Unit.new()
Unit.Pick(hero)
Unit.Register("hero")
Unit.SetWalkingStance(1)
Unit.SetSpeed(250)
Unit.Initialize("barbarian",100,20,100,100,0,false)