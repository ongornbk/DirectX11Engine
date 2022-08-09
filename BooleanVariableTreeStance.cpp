#include "BooleanVariableTreeStance.h"

BooleanVariableTreeStance::BooleanVariableTreeStance(class Tree* const __tree)
{
    tree.make_handle(__tree->GetHandle());
}

BooleanVariableTreeStance::BooleanVariableTreeStance(const modern_handle& __tree)
{
    tree.make_handle(__tree);
}

const bool BooleanVariableTreeStance::get()
{
    class Tree* const A = (class Tree* const )tree.get();
    if (A)
    {
        return (bool)A->GetStance();
    }
    return false;
}
