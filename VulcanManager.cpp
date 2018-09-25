#include "VulcanManager.h"
#include "IPP.h"
#include <vector>

VulcanManager::VulcanManager()
{
}


VulcanManager::~VulcanManager()
{
}

bool VulcanManager::Initialize(int screenWidth, int screenHeight, bool fullscreen, HWND hwnd, bool vsync)
{
	VkApplicationInfo applicationInfo{};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.apiVersion = VK_API_VERSION_1_0;
	applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	applicationInfo.pApplicationName = "RPG Engine";
	
	VkInstanceCreateInfo instanceCreateInfo {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	auto ret = vkCreateInstance(&instanceCreateInfo, nullptr,&m_instance);
	if (ret != VK_SUCCESS)
	{
		ipp::Console::SetTextColor(ipp::TextColors::RED);
		ipp::Console::Println("CRTITICAL_ERROR vkInstanceCreateInfo");
		ipp::System::Exit(-1);
	}

	{
		uint32_t gpu_count = 0u;
		vkEnumeratePhysicalDevices(m_instance, &gpu_count, nullptr);
		std::vector<VkPhysicalDevice> gpu_list(gpu_count);
		vkEnumeratePhysicalDevices(m_instance, &gpu_count, gpu_list.data());
		m_gpu = gpu_list[0];
	}
	{
		uint32_t family_count = 0u;
		vkGetPhysicalDeviceQueueFamilyProperties(m_gpu, &family_count, nullptr);
		std::vector<VkQueueFamilyProperties> family_property_list(family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(m_gpu, &family_count, family_property_list.data());

		VkBool32 found = VK_FALSE;
		for (uint32_t i = 0u; i < family_count;++i)
		{
			if (family_property_list[i].queueFlags&VK_QUEUE_GRAPHICS_BIT)
			{
				found = VK_TRUE;
				m_graphicsFamilyIndex = i;
			}
		}
		if (found == VK_FALSE)
		{
			ipp::Console::SetTextColor(ipp::TextColors::RED);
			ipp::Console::Println("CRITICAL_ERROR VK_QUEUE_GRAPHICS_BIT not found");
			ipp::System::Exit(-1);
		}

	}
	float queue_priorities[]{ 1.0f };

	VkDeviceQueueCreateInfo device_queue_device_info{};
	device_queue_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	device_queue_device_info.queueFamilyIndex =
	device_queue_device_info.queueCount = 1;
	device_queue_device_info.pQueuePriorities = queue_priorities;

	VkDeviceCreateInfo device_create_info{};
	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.queueCreateInfoCount = 1;
	device_create_info.pQueueCreateInfos = &device_queue_device_info;
	VkResult err = vkCreateDevice(m_gpu,&device_create_info, nullptr, &m_device);
	if (VK_SUCCESS != err)
	{
		ipp::Console::SetTextColor(ipp::TextColors::RED);
		ipp::Console::Println("CRITICAL_ERROR vkCreateDevice");
		ipp::System::Exit(-1);
	}
	return true;
}

void VulcanManager::Release()
{
	vkDestroyInstance(m_instance, nullptr);
	m_instance = nullptr;
	vkDestroyDevice(m_device, nullptr);
	m_device = nullptr;
}
