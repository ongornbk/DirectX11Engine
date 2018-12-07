Pointer = {}

function Pointer.swap(A,B)
local tempA = A.ptrA
local tempB = B.ptrB
A.ptrA = B.ptrA
A.ptrB = B.ptrB
B.ptrA = tempA
B.ptrB = tempB
end

function Pointer.exist(A)
    if A.ptrA > 0 or A.ptrB > 0
    then
    return true
    else
    return false
    end
end

function Pointer.load(A,B)
    return {ptrA = A,ptrB = B}
    end