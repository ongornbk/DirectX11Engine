#pragma once
#include "Texture.h"

class ResourceTexture
{
public:
	ResourceTexture(void);
	~ResourceTexture(void);

	const modern_Boolean Load(struct ID3D11Device* const device, const class modern_string& name);

	Texture* GetTexture();
	const class modern_string_view& GetName() const modern_except_state;
private:
	Texture* m_texture;
};

