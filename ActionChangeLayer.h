#pragma once
#include "IAction.h"
#include "RenderLayerType.h"
#include "RenderContainer.h"
#include "RendererManager.h"

class ActionChangeLayer :
	public IAction
{
	class EObject* m_object;
	enum class RenderLayerType m_layer;

	ActionChangeLayer() = delete;

public:

	ActionChangeLayer(class EObject* const object,const enum class RenderLayerType layer);
	~ActionChangeLayer();

	void execute() override;
};

