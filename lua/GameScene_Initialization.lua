require "core/Unit"
require "core/Game"

Game.Start()

hero = Unit.new()
Unit.Pick(hero)
Unit.Register("hero")
Unit.SetWalkingStance(1)
Unit.SetSpeed(250)
Unit.Initialize("barbarian",100,20,100,100,0,false)