require "core/Object"

Destructible = {}

Destructible.lastCreatedDestructible = 0
Destructible.pickedDestructible = 0

function Destructible.new ()
    Destructible.lastCreatedDestructible = CreateDestructible()
Object.lastCreatedObject =Destructible.lastCreatedDestructible
return Destructible.lastCreatedDestructible
    end

    function Destructible.Pick(object)
        Destructible.pickedDestructible = object
        Object.Pick(object)
        end

        function Destructible.Initialize (model,size,collision,x,y,z)
            InitializeDestructible(Destructible.pickedDestructible,tostring(model),size,collision,x,y,z)
            end



