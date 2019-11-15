#pragma once
#include <Windows.h>

//#include <vulkan/vulkan.h>

//#pragma comment(lib,"vulkan-1.lib")

class VulcanManager
{
public:
	VulcanManager(void);
	~VulcanManager(void);

	bool Initialize(int screenWidth, int screenHeight, bool fullscreen, HWND hwnd, bool vsync);
	void Release();

private:

	//VkInstance        m_instance            = nullptr;
	//VkDevice          m_device              = nullptr;
	//VkPhysicalDevice  m_gpu                 = nullptr;

//	uint32_t          m_graphicsFamilyIndex = 0u;
};

