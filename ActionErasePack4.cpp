#include "ActionErasePack4.h"
#include "Global.h"

ActionErasePack4::ActionErasePack4(struct modern_pack4* const refpack) : m_pack(*refpack)
{

}

ActionErasePack4::~ActionErasePack4()
{
}

void ActionErasePack4::execute()
{
   // Global::GetInstance()->m_bmap4.erase(m_pack);
}

const ActionBehavior ActionErasePack4::execute_in_array()
{
    this->execute();
    return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
