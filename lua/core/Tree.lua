require "core/Object"

Tree = {}

Tree.lastCreatedTree = 0
Tree.pickedTree = 0

function Tree.new ()
    Tree.lastCreatedTree = CreateTree()
Object.lastCreatedObject = Tree.lastCreatedTree
return Tree.lastCreatedTree
    end

    function Tree.Pick(object)
        Tree.pickedTree = object
        Object.Pick(object)
        end

        function Tree.Initialize (model,size,collision,x,y,z)
            InitializeTree(Tree.pickedTree,tostring(model),size,collision,x,y,z)
            end