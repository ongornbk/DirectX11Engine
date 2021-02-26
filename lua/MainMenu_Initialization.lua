require "core/Camera"
require "core/Model"

io.write(string.format("Hello from %s\n", _VERSION))
--StartServer(1234)
SetTilesMultiplier(100)
LoadTexture("x64/Release/content/Textures/system/sys.png")


Model.Load("barbarian")
Model.LoadTexture("barbarian","attack1")
Model.LoadTexture("barbarian","gethit")
Model.LoadTexture("barbarian","run")
Model.LoadTexture("barbarian","townneutral")
Model.LoadTexture("barbarian","townwalk")
Model.LoadTexture("barbarian","specialcast")

Model.Load("enemy")
Model.LoadTexture("enemy","walk")
Model.LoadTexture("enemy","townneutral")

Model.Load("amazon")
Model.LoadTexture("amazon","run")
Model.LoadTexture("amazon","townneutral")

Model.Load("amazon_light")
Model.LoadTexture("amazon_light","run")
Model.LoadTexture("amazon_light","townneutral")
Model.LoadTexture("amazon_light","walk")

Model.Load("reaper")
Model.LoadTexture("reaper","townwalk")

Model.Load("hell_bovine")
Model.LoadTexture("hell_bovine","dead")
Model.LoadTexture("hell_bovine","walk")
Model.LoadTexture("hell_bovine","death")
Model.LoadTexture("hell_bovine","attack2")
Model.LoadTexture("hell_bovine","attack1")
Model.LoadTexture("hell_bovine","gethit")
Model.LoadTexture("hell_bovine","neutral")

Model.Load("irrlicht")
Model.LoadTexture("irrlicht","walk")
Model.LoadTexture("irrlicht","death")

Model.Load("griswold")
Model.LoadTexture("griswold","walk")
Model.LoadTexture("griswold","dead")
Model.LoadTexture("griswold","death")

Model.Load("baboon")
Model.LoadTexture("baboon","walk")
Model.LoadTexture("baboon","dead")
Model.LoadTexture("baboon","death")

Model.Load("fallen_shaman")
Model.LoadTexture("fallen_shaman","walk")
Model.LoadTexture("fallen_shaman","dead")
Model.LoadTexture("fallen_shaman","death")


math.randomseed(1234)

LoadTexture("x64/Release/content/Textures/gui/ui_cursor.png")
LoadTexture("x64/Release/content/Textures/gui/ui_game.png")
LoadTexture("x64/Release/content/Textures/gui/ui_gameMenu.png")

LoadTexture("x64/Release/content/Textures/tiles/dirt.png")
--LoadTexture("../../content/Textures/tiles/dirt1.png")
--LoadTexture("../../content/Textures/tiles/dirt2.png")

LoadTexture("x64/Release/content/Textures/tiles/grass.png")
--LoadTexture("../../content/Textures/tiles/grass0.png")
--LoadTexture("../../content/Textures/tiles/grass1.png")
--LoadTexture("../../content/Textures/tiles/grass2.png")
--LoadTexture("../../content/Textures/tiles/grass3.png")

LoadTexture("x64/Release/content/Textures/tiles/rock.png")
LoadTexture("x64/Release/content/Textures/tiles/leaves.png")
LoadTexture("x64/Release/content/Textures/tiles/paving.png")
LoadTexture("x64/Release/content/Textures/tiles/paving2.png")
LoadTexture("x64/Release/content/Textures/tiles/dust.png")
LoadTexture("x64/Release/content/Textures/tiles/water.png")
LoadTexture("x64/Release/content/Textures/tiles/sand0.png")
LoadTexture("x64/Release/content/Textures/font/ExocetLight.png")

LoadTexture("x64/Release/content/Textures/doodads/well0.png")
LoadTexture("x64/Release/content/Textures/doodads/barell0.png")
LoadTexture("x64/Release/content/Textures/doodads/fire0.png")
LoadTexture("x64/Release/content/Textures/doodads/cow_corpse0.png")
LoadTexture("x64/Release/content/Textures/doodads/tree0.png")
LoadTexture("x64/Release/content/Textures/doodads/tree1.png")
LoadTexture("x64/Release/content/Textures/doodads/tree2.png")
LoadTexture("x64/Release/content/Textures/doodads/fountain0.png")
LoadTexture("x64/Release/content/Textures/doodads/town_wall.png")

LoadSound("x64/Release/content/Music/lakeland.ogg")
LoadSound("x64/Release/content/SFX/place.ogg")
LoadSound("x64/Release/content/SFX/footsteps.ogg")
LoadSound("x64/Release/content/SFX/teleport.ogg")
LoadSound("x64/Release/content/SFX/attack1.ogg")
LoadSound("x64/Release/content/SFX/attack2.ogg")
LoadSound("x64/Release/content/SFX/attack3.ogg")

InitializeProjectionMatrix(4,10,1000)
InitializeOrthoMatrix(10,1000)
Camera.SetPosition(0,0)
AddMusic("lakeland",50,true)
AddInterfaceSound("place",50)
AddInterfaceSound("footsteps",50)
AddInterfaceSound("teleport",60)
AddInterfaceSound("attack1",60)
AddInterfaceSound("attack2",60)
AddInterfaceSound("attack3",60)


LoadFont("x64/Release/content/Textures/font/ExocetLight.co",432,131)