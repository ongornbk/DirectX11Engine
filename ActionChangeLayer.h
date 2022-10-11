#pragma once
#include "IAction.h"
#include "RenderLayerType.h"
#include "GameObject.h"
#include "RendererManager.h"

class ActionChangeLayer :
	public IAction
{
	class modern_handle m_object;
	enum class RenderLayerType m_layer;

	ActionChangeLayer() = delete;

public:

	ActionChangeLayer(class GameObject* const object,const enum class RenderLayerType layer);
	~ActionChangeLayer();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

