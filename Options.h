#pragma once
#include "modern/modern_class.h"
#include "modern/modern_handle.h"
#include "modern/modern_cstring.h"

#define OPTIONS_LENGTH 1

static constexpr char* m_optionsNames[OPTIONS_LENGTH] =
{
	"SHOW_FPS"
};

class Options : public modern_class

{
public:
	Options();
	~Options();

	static modern_handle const &GetInstance();

	const int64_t GetKey(const class modern_cstring& name) volatile;

	union
	{
		struct
		{
			modern_Boolean option_ShowFPS;
		};
		int64_t options[OPTIONS_LENGTH];
	};
};

