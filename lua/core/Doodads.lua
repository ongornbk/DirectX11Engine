Doodads = {}



function Doodads.new ()
local tptrA,tptrB = CreateDoodads()
PickObject(tptrA,tptrB)
return {ptrA = tptrA,ptrB = tptrB}
end

function Doodads.Load(A,B)
return {ptrA = A,ptrB = B}
end

function Doodads.Initialize(texture,size,collision,x,y,z)
InitializeDoodads(texture,size,collision,x,y,z)
end




