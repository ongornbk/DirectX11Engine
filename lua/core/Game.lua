Game = {}

function Game.Start ()
LoadInstance("maps/map.save")
tileSelected = 0
SetInterface(1)
ResumeGame()
end

function Game.Resume ()
ResumeGame()
end

function Game.Exit ()
PostQuitMessage(1)
end

function Game.Save()
SaveInstance("maps/map.save")
end



