#pragma once
namespace GlobalUtilities
{

	template <class returntype, class type> inline returntype memory_cast(type obj)
	{
		return *(returntype*)(obj);
	}


	template <class T> inline void Delete(T t)
	{

		if (t)
		{
			delete t;
			t = NULL;

		}
	}
	template <class T> inline void DeleteArray(T t)
	{

		if (t)
		{
			delete[] t;
			t = NULL;

		}
	}
	template <class T> inline void Unacquire(T t)
	{
		if (t)
		{
			(void)t->Unacquire();
			(void)t->Release();
			t = NULL;
		}
	}
	template <class T> inline void Translate(T t, float X, float Y,float Z, float M)
	{
		if (t)
		{
			t->SetPosition(X, Y,Z,M);
		}
	}
	template <class T> inline void Translate(T t, float X, float Y, float Z)
	{
		if (t)
		{
			t->SetPosition(X, Y,Z);
		}
	}
	template <class T> inline void Translate(T t, float X, float Y)
	{
		if (t)
		{
			t->SetPosition(X, Y);
		}
	}
	template <class T> inline T Interpolate(const T& a, const T& b, float l)
	{
		return a + (b - a) * l;
	}

	template <class T> inline T clamp(T value, T min, T max)
	{
		if (value <= min) return min;
		else if (value >= max) return max;
		else return value;
	}




		int            random(int min, int max);
		//float          random(float min, float max);

};

