Doodads = {}



function Doodads.new ()
local tptrA,tptrB = CreateDoodads()
return {ptrA = tptrA,ptrB = tptrB}
end

function Doodads.Load(A,B)
return {ptrA = A,ptrB = B}
end



function Doodads.exist(doodads)

if doodads.ptrA > 0 or doodads.ptrB > 0
then
return true
else
return false
end

end


