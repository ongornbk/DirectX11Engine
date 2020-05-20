require "core/Camera"
require "core/Model"

io.write(string.format("Hello from %s\n", _VERSION))
--StartServer(1234)
SetTilesMultiplier(123)
LoadTexture("../../content/Textures/system/sys.png")


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


math.randomseed(1234)

LoadTexture("../../content/Textures/gui/ui_cursor.png")
LoadTexture("../../content/Textures/gui/ui_game.png")
LoadTexture("../../content/Textures/gui/ui_gameMenu.png")

LoadTexture("../../content/Textures/tiles/dirt0.png")
LoadTexture("../../content/Textures/tiles/dirt1.png")
LoadTexture("../../content/Textures/tiles/dirt2.png")

LoadTexture("../../content/Textures/tiles/grass0.png")
LoadTexture("../../content/Textures/tiles/grass1.png")
LoadTexture("../../content/Textures/tiles/grass2.png")
LoadTexture("../../content/Textures/tiles/grass3.png")

LoadTexture("../../content/Textures/tiles/rock.png")
LoadTexture("../../content/Textures/tiles/leaves.png")
LoadTexture("../../content/Textures/tiles/paving.png")
LoadTexture("../../content/Textures/tiles/paving2.png")
LoadTexture("../../content/Textures/tiles/dust.png")
LoadTexture("../../content/Textures/tiles/water.png")
LoadTexture("../../content/Textures/tiles/sand0.png")
LoadTexture("../../content/Textures/font/ExocetLight.png")

LoadTexture("../../content/Textures/doodads/well0.png")
LoadTexture("../../content/Textures/doodads/barell0.png")
LoadTexture("../../content/Textures/doodads/fire0.png")
LoadTexture("../../content/Textures/doodads/cow_corpse0.png")
LoadTexture("../../content/Textures/doodads/tree0.png")
LoadTexture("../../content/Textures/doodads/tree1.png")
LoadTexture("../../content/Textures/doodads/tree2.png")
LoadTexture("../../content/Textures/doodads/fountain0.png")

LoadSound("../../content/Music/lakeland.ogg")
LoadSound("../../content/SFX/place.ogg")
LoadSound("../../content/SFX/footsteps.ogg")
LoadSound("../../content/SFX/teleport.ogg")
LoadSound("../../content/SFX/attack1.ogg")
LoadSound("../../content/SFX/attack2.ogg")
LoadSound("../../content/SFX/attack3.ogg")

InitializeProjectionMatrix(4,10,1000)
InitializeOrthoMatrix(10,1000)
Camera.SetPosition(0,0)
AddMusic("lakeland",30,true)
AddInterfaceSound("place",50)
AddInterfaceSound("footsteps",50)
AddInterfaceSound("teleport",60)
AddInterfaceSound("attack1",60)
AddInterfaceSound("attack2",60)
AddInterfaceSound("attack3",60)


LoadFont("../../content/Textures/font/ExocetLight.co",432,131)