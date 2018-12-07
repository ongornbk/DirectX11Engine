require "core/Unit"
require "core/Game"
require "core/Music"
require "core/Camera"

Game.Start()
Music.Play("lakeland")
Camera.Up(0.0,1.0,0.0,0.0)
Camera.LookAt(0.0,0.0,1.0,0.0)
hero = Unit.new()
SetFlags("10100100")
Unit.SetWalkingStance(1)
Unit.SetSpeed(320)
Unit.Initialize("barbarian",100,20,0,0,0,false)