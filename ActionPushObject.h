#include "IAction.h"
#include "RenderLayerType.h"
#include "GameObject.h"
#include "RendererManager.h"

class ActionPushObject :
	public IAction
{
	class modern_handle m_object;
	enum class RenderLayerType m_layer;

	ActionPushObject() = delete;

public:

	ActionPushObject(class GameObject* const object, const enum class RenderLayerType layer);
	~ActionPushObject();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

