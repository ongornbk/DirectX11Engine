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
#include "IPP.h"
#pragma endregion

void c_script_donothing(void)
{
}

void c_script_tree_fade_enter(void)
{
	//ipp::Console::GetInput();
	if (Global::GetInstance()->m_enteringObject.get() == RendererManager::GetInstance()->GetFocusAgentHandle().get())
	{
		class Tree* const tree = (class Tree* const)((class RegionC* const)Global::GetInstance()->m_triggeringRegion.get())->GetParent().get();
	
	
	
		//if (tree->GetStance())
		//{
		//	return;
		//}
		tree->SetColorFilter(1.f, 1.f, 1.f, 0.15f);
		//tree->CastShadow(false);
		//tree->SetStance(1);
	}
	//else if(Global::GetInstance()->m_enteringObject.get() == Global::GetInstance()->m_lastSelectedUnit.get())
	//{
	//	class Tree* const tree = (class Tree* const)((class RegionC* const)Global::GetInstance()->m_triggeringRegion.get())->GetParent().get();
	//	class EObject* const object = (class EObject* const)Global::GetInstance()->m_enteringObject.get();
	//
	//	class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
	//	action->push(new ActionWaitUntil(ConditionFactory::CreateOrCondition(
	//		ConditionFactory::CreateBooleanCondition(new BooleanVariableObjectIntersectsWithRegion(
	//			Global::GetInstance()->m_enteringObject, Global::GetInstance()->m_triggeringRegion),
	//			new ConstBooleanVariable(false), BooleanOperatorType::BOOLEAN_OPERATOR_TYPE_EQUALS
	//		),
	//		ConditionFactory::CreateBooleanCondition(new BooleanVariableObjectIsSelected(
	//			object),
	//			new ConstBooleanVariable(false), BooleanOperatorType::BOOLEAN_OPERATOR_TYPE_EQUALS
	//		))));
	//	action->push(new ActionWaitUntil(nullptr));
	//	action->push(new ActionSetShadowCast(tree, true));
	//	action->push(new ActionApplyColorFilter(tree, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f)));
	//	action->push(new ActionTreeSetStance(tree, 0));
	//	Timer::CreateInstantTimer(action);
	//}
}

void c_script_tree_fade_leave(void)
{
	if (Global::GetInstance()->m_leavingObject.get() == RendererManager::GetInstance()->GetFocusAgentHandle().get())
	{
		class Tree* const tree = (class Tree* const)((class RegionC* const)Global::GetInstance()->m_triggeringRegion.get())->GetParent().get();
	
		//tree->SetStance(0);
		tree->SetColorFilter(1.f, 1.f, 1.f, 1.f);
		//tree->CastShadow();
	}
}
