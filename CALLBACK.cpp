#include "ResourceManager.h"
#include "LUAManager.h"

#ifdef __cplusplus
extern "C"
#endif // __cplusplus
{




namespace lua_callback
{
#pragma region
	using std::string;
	using std::wstring;
#pragma endregion
	static void SetResourceManager(ResourceManager* manager);

	namespace
	{

		static ResourceManager* m_resources;

	}

	static void SetResourceManager(ResourceManager* manager)
	{
		m_resources = manager;
	}

	static int LoadTexture(lua_State* state)
	{
#pragma warning(disable : 4996)
			string str = lua_tostring(state,1);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string,ws.c_str());
			m_resources->LoadTextureResource(wide_string);
			delete wide_string;
		return 1;
	}

	static int LoadSound(lua_State* state)
	{
#pragma warning(disable : 4996)
		string str = lua_tostring(state, 1);
		wchar_t* wide_string = new wchar_t[str.length() + 1];
		wstring ws = std::wstring(str.begin(), str.end()).c_str();
		wcscpy(wide_string, ws.c_str());
		m_resources->LoadSoundResource(wide_string);
		delete wide_string;
		return 1;
	}

	static void RegisterFunctions()
	{
		lua_State* m_lua = lua::GetInstance();
		lua_register(m_lua, "LoadTexture", LoadTexture);
		lua_register(m_lua, "LoadSound", LoadSound);
	}

}

}
