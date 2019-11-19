Model = {}

function Model.Load(name)
AddModelPaths("../../content/Textures/models/"..name..".mod")
end

function Model.LoadTexture(name,texture)
    LoadTexture("../../content/Textures/models/"..name.."/"..name.."_"..texture..".png")
end

