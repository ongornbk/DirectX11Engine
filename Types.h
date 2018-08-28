#pragma once
#include <atomic>

using std::atomic;

typedef unsigned short  INDEX;
typedef atomic<INDEX>   AINDEX;
typedef          short  SINDEX;
typedef atomic<SINDEX>  ASINDEX;

extern "C"
{

	struct INDEX2
	{
		INDEX2() noexcept
		{
			this->i = 0;
			this->j = 0;
		}
		INDEX2(INDEX I, INDEX J) noexcept
		{
			this->i = I;
			this->j = J;
		}
		INDEX i;
		INDEX j;
	};

	struct SINDEX2
	{
		SINDEX2() noexcept
		{
			this->i = 0;
			this->j = 0;
		}
		SINDEX2(SINDEX I, SINDEX J) noexcept
		{
			this->i = I;
			this->j = J;
		}
		SINDEX i;
		SINDEX j;
	};

	struct ASINDEX2
	{
		ASINDEX2() noexcept
		{
			this->i = 0;
			this->j = 0;
		}
		ASINDEX2(SINDEX I, SINDEX J) noexcept
		{
			this->i = I;
			this->j = J;
		}
		ASINDEX i;
		ASINDEX j;
	};


}