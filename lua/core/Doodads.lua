require "core/Object"

Doodads = {}

Doodads.lastCreatedDoodads = 0
Doodads.pickedDoodads = 0

function Doodads.new ()
    Doodads.lastCreatedDoodads = CreateDoodads()
Object.lastCreatedObject = Doodads.lastCreatedDoodads
return Doodads.lastCreatedDoodads
    end

    function Doodads.Pick(object)
        Doodads.pickedDoodads = object
        Object.Pick(object)
        end

        function Doodads.Initialize (model,size,collision,x,y,z)
            InitializeDoodads(Doodads.pickedDoodads,tostring(model),size,collision,x,y,z)
            end



