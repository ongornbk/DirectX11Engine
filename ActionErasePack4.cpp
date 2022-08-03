#include "ActionErasePack4.h"
#include "Global.h"

ActionErasePack4::ActionErasePack4(struct modern_pack4* const refpack)
{
    m_pack = refpack;
}

ActionErasePack4::~ActionErasePack4()
{
    if (m_pack)
    {
        delete m_pack;
        m_pack = nullptr;
    }
}

void ActionErasePack4::execute()
{
    //auto& mpb = *&Global::GetInstance()->m_bmap4;
    //mpb[*m_pack]--;
   // if (mpb[*m_pack]==0ll)
   // {
   //     mpb.erase(*m_pack);
   // }
}

const ActionBehavior ActionErasePack4::execute_in_array()
{
    this->execute();
    return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
