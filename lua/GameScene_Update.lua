require "core/Unit"
require "core/Doodads"
require "core/Camera"
require "core/Game"
require "core/Chat"

if IsKeyHit(1) == true
then 
Game.Save()
Game.Exit()
end
if IsKeyHit(2) == true
then
tileSelected = 0
end
if IsKeyHit(3) == true
then
tileSelected = 1
end
if IsKeyHit(4) == true
then
tileSelected = 2
end
if IsKeyHit(5) == true
then
tileSelected = 3
end
if IsKeyHit(5) == true
then
tileSelected = 4
end
if IsKeyHit(6) == true
then
tileSelected = 5
end
if IsKeyHit(7) == true
then
tileSelected = 6
end
if IsKeyHit(8) == true
then
tileSelected = 7
end
if IsKeyHit(9) == true
then
tileSelected = 8
end
if IsKeyPressed(19) == true
then
GetMousePosition()
SetTile(tileSelected,2)
end
if IsKeyPressed(20) == true
then
local x,y = GetMousePosition()
Unit.new()
Unit.SetWalkingStance(1)
Unit.SetSpeed(100)
Unit.Initialize("enemy",100,18,x,y,0,false)
end

if IsKeyPressed(21) == true
then
niu = Unit.Load(GetLastSelectedUnit())
if Unit.exist(niu)
then
hero = niu
end

else

end

if IsKeyHit(22) == true
then
local x,y = GetMousePosition()
Doodads.new()
Doodads.Initialize("well0",125,50,x,y,0,false)
Chat.Print("well0 Has Been Created!")
end
if IsKeyPressed(23) == true
then
local x,y = GetMousePosition()
Doodads.new()
Doodads.Initialize("barell0",105,17,x,y,0,true)
Chat.Print("barell0 Has Been Created!")
end
if IsKeyPressed(24) == true
then
local x,y = GetMousePosition()
CreateAnimatedDoodads()
InitializeAnimatedDoodads("fire0",math.random(80,120),0,x,y,0,false)
SetNumberOfFrames(25)
Chat.Print("fire0 Has Been Created!")
end
if IsKeyHit(26) == true
then
local x,y = GetMousePosition()
Doodads.new()
Doodads.Initialize("cow_corpse0",120,0,x,y,-1,false)
Chat.Print("cow_corpse0 Has Been Created!")
--SetZ(1)
end
if IsKeyHit(27) == true
then
local x,y = GetMousePosition()
CreateTree()
InitializeTree("tree0",400,20,x,y,0,false)
Chat.Print("tree0 Has Been Created!")
end
if IsKeyHit(28) == true
then
local x,y = GetMousePosition()
CreateTree()
InitializeTree("fountain0",250,70,x,y,0,false)
Chat.Print("fountain0 Has Been Created!")
end
if GetMouseState(0) == true
then
Unit.Pick(hero)
local x,y = GetMousePosition()
Unit.Goto(x,y)
end
if GetMousePressed(1) == true
then
Unit.Pick(hero)
local x,y = GetMousePosition()
Unit.SetPosition(x,y)
Unit.CleanTasks()
end

Unit.Pick(hero)
Camera.SetPosition(Unit.GetPosition())