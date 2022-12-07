#include "IAction.h"
#include "Interface.h"
#include "IInterfaceBehavior.h"

class ActionSetInterfaceBehavior :
    public IAction
{
    IInterfaceBehavior* m_behavior;
    modern_handle m_interface;

    ActionSetInterfaceBehavior() = delete;

public:

    ActionSetInterfaceBehavior(modern_handle& inter, class IInterfaceBehavior* const behavior);
    ~ActionSetInterfaceBehavior();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};