require "core/Unit"
require "core/Game"
require "core/Music"

Game.Start()
Music.Play("lakeland")
hero = Unit.new()
Unit.Pick(hero)
Unit.SetWalkingStance(1)
Unit.SetSpeed(260)
Unit.Initialize("barbarian",100,21,0,0,0,false)