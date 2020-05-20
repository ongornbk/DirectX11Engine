require "core/Unit"
require "core/Game"
require "core/Music"
require "core/Camera"
require "core/Chat"
require "core/Tree"

--SetTileMapRendering(false)

Game.Start()
Music.Play("lakeland")
Camera.Up(0.0,1.0,0.0,0.0)
Camera.LookAt(0.0,0.0,1.0,0.0)
hero = Unit.new()
Unit.Pick(hero)
Unit.SetWalkingStance(1)
Unit.SetSpeed(300)
Object.SetRenderingFlag(true)
Object.SetSelectableFlag(false)
Object.SetPushableFlag(true)
Object.SetShadowFlag(true)
Object.SetCollisionPriority(2)
Unit.Initialize("barbarian",100,25,0,0,0,false)
--PushSPointerParameter("pickedObject")
--CreatePeriodicTimer("MessageFront",0,1)

pullgroup = CreateUnitGroup()




