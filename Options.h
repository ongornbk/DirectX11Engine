#pragma once

#include <modern__.h>

#define OPTIONS_LENGTH 3

static constexpr char* m_optionsNames[OPTIONS_LENGTH] =
{
	"NULL",
	"SHOW_FPS",
	"SOUND"
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
			modern_Boolean option_null;
			modern_Boolean option_ShowFPS;
			modern_Boolean option_Sound;
		};
		int64_t options[OPTIONS_LENGTH];
	};
};

