require "core/Unit"
require "core/Doodads"
require "core/Camera"
require "core/Game"
require "core/Chat"
require "core/Pointer"

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
SetFlags("11100100")
Unit.SetWalkingStance(1)
Unit.SetSpeed(135)
Unit.Initialize("enemy",100,20,x,y,0,true)
end

if IsKeyPressed(21) == true
then
local niu = Pointer.load(GetLastSelectedUnit())
if Pointer.exist(niu)
then
Pointer.swap(niu,hero)
end
end

if IsKeyHit(22) == true
then
local x,y = GetMousePosition()
Doodads.new()
SetFlags("10000000")
Doodads.Initialize("well0",125,50,x,y,0)
Chat.Print("well0 Has Been Created!")
end
if IsKeyPressed(23) == true
then
local x,y = GetMousePosition()
Doodads.new()
SetFlags("11000000")
Doodads.Initialize("barell0",105,18,x,y,0)
Chat.Print("barell0 Has Been Created!")
end
if IsKeyPressed(24) == true
then
local x,y = GetMousePosition()
CreateAnimatedDoodads()
SetFlags("10000000")
InitializeAnimatedDoodads("fire0",120,24,x,y,0)
SetNumberOfFrames(25)
Chat.Print("fire0 Has Been Created!")
end
if IsKeyHit(26) == true
then
local x,y = GetMousePosition()
Doodads.new()
SetFlags("10000000")
Doodads.Initialize("cow_corpse0",120,20,x,y,-1)
Chat.Print("cow_corpse0 Has Been Created!")
--SetZ(1)
end
if IsKeyHit(27) == true
then
local x,y = GetMousePosition()
CreateTree()
SetFlags("10000010")
InitializeTree("tree0",400,20,x,y,0)
Chat.Print("tree0 Has Been Created!")
end
if IsKeyHit(28) == true
then
local x,y = GetMousePosition()
CreateTree()
SetFlags("10000010")
InitializeTree("fountain0",250,70,x,y,0)
Chat.Print("fountain0 Has Been Created!")
end

