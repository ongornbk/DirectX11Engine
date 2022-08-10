#include "CScripts.h"
#include "RendererManager.h"
#include "ConditionFactory.h"
#include "Timer.h"
#pragma region Actions
#include "ActionExecuteActionArray.h"
#include "ActionWaitUntil.h"
#include "ActionSetShadowCast.h"
#include "ActionApplyColorFilter.h"
#include "ActionTreeSetStance.h"
#include "ActionIfThenElse.h"
#include "ActionSkipRemainingActions.h"
#include "ActionContinue.h"
#include "IPP.h"
#pragma endregion

void c_script_donothing(void)
{
}

void c_script_tree_fade_enter(void)
{
	if (Global::GetInstance()->m_enteringObject.get() == RendererManager::GetInstance()->GetFocusAgentHandle().get())
	{
		class Tree* const tree = (class Tree* const)((class RegionC* const)Global::GetInstance()->m_triggeringRegion.get())->GetParent().get();
	
	
	
		if (tree->GetStance())
		{
			return;
		}
		tree->SetColorFilter(1.f, 1.f, 1.f, 0.30f);
		tree->CastShadow(false);
		tree->SetStance(1);
	}
}

void c_script_tree_fade_leave(void)
{
	if (Global::GetInstance()->m_leavingObject.get() == RendererManager::GetInstance()->GetFocusAgentHandle().get())
	{
		class Tree* const tree = (class Tree* const)((class RegionC* const)Global::GetInstance()->m_triggeringRegion.get())->GetParent().get();
	
		tree->SetStance(0);
		tree->SetColorFilter(1.f, 1.f, 1.f, 1.f);
		tree->CastShadow();
	}
}
