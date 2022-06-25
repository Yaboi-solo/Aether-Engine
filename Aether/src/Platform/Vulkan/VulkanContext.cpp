#include "atpch.h"
#include "VulkanContext.h"

#ifdef AT_PLATFORM_WINDOWS
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif

namespace Aether {

	static bool s_Validation = true;

	bool isVulkanSupported();
	VkResult CreateWindowSurface(VkInstance instance, void* windowHandle, VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT                  objectType,
		uint64_t                                    object,
		size_t                                      location,
		int32_t                                     messageCode,
		const char* pLayerPrefix,
		const char* pMessage,
		void* pUserData)
	{
		AT_WARN("Vulkan Debug Callback:\n	Object Type: {0}\n	Message: {1}", (int)objectType, pMessage);
		return VK_FALSE;
	}

	VulkanContext::VulkanContext(void* window)
	{
		m_Window = window;
	}

	VulkanContext::~VulkanContext()
	{
	}

	void VulkanContext::Init()
	{
		AT_ASSERT(isVulkanSupported(), "Vulkan is not supported!");

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Application Info
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pEngineName = "Aether";
		appInfo.pApplicationName = "Aether";
		appInfo.apiVersion = VK_API_VERSION_1_2;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Extensions and Validation
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<const char*> instanceExtensions = { VK_KHR_SURFACE_EXTENSION_NAME };
#ifdef AT_PLATFORM_WINDOWS
		instanceExtensions.push_back("VK_KHR_win32_surface");
#endif
		if (s_Validation)
		{
			instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		VkInstanceCreateInfo instanceCreateInfo = {};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &appInfo;
		instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
		instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

		if (s_Validation)
		{
			const char* validationLayerName = "VK_LAYER_KHRONOS_validation";

			uint32_t instanceLayerCount;
			vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
			std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerCount);
			vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data());
			bool validationLayerPresent = false;
			for (VkLayerProperties layer : instanceLayerProperties)
			{
				if (strcmp(layer.layerName, validationLayerName) == 0)
				{
					validationLayerPresent = true;
					break;
				}
			}

			if (validationLayerPresent)
			{
				instanceCreateInfo.enabledLayerCount = 1;
				instanceCreateInfo.ppEnabledLayerNames = &validationLayerName;
			}
			else
			{
				AT_ERROR("Validation layer VK_LAYER_KHRONOS_validation not present, validation disabled!");
				s_Validation = false;
			}

		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Instance and Surface Creation
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		VK_CHECK_RESULT(vkCreateInstance(&instanceCreateInfo, nullptr, &s_VulkanInstance));
		AT_TRACE("Created Vulkan instance.");

		if (s_Validation)
		{
			auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(s_VulkanInstance, "vkCreateDebugReportCallbackEXT");
			AT_ASSERT(vkCreateDebugReportCallbackEXT != NULL, "");
			VkDebugReportCallbackCreateInfoEXT debugReportInfo = {};
			debugReportInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
			debugReportInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
			debugReportInfo.pfnCallback = VulkanDebugCallback;
			VK_CHECK_RESULT(vkCreateDebugReportCallbackEXT(s_VulkanInstance, &debugReportInfo, nullptr, &m_DebugReportCallback));
		}

		CreateWindowSurface(s_VulkanInstance, m_Window, nullptr, &m_Surface);
		AT_TRACE("Created Vulkan surface.");

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Device Creation
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		m_PhysicalDevice = VulkanPhysicalDevice::Select(); 
		m_Device = CreateScope<VulkanDevice>();
		
	}

	void VulkanContext::SwapBuffers()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool isVulkanSupported()
	{
		uint32_t apiVersion;
		vkEnumerateInstanceVersion(&apiVersion);

		uint32_t major = VK_API_VERSION_MAJOR(apiVersion);
		uint32_t minor = VK_API_VERSION_MINOR(apiVersion);
		uint32_t patch = VK_API_VERSION_PATCH(apiVersion);

		if (major >= 1 && minor >= 2)
		{
			AT_TRACE("Vulkan Version: {0}.{1}.{2}", major, minor, patch);
			return true;
		}

		AT_FATAL("Required Vulkan version (1.2) not supported!");
		return false;
	}

	VkResult CreateWindowSurface(VkInstance instance, void* windowHandle, VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
	{
#ifdef AT_PLATFORM_WINDOWS
		HWND hWnd = (HWND)windowHandle;

		VkWin32SurfaceCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd = hWnd;
		createInfo.hinstance = GetModuleHandleA(0);

		VkResult result = vkCreateWin32SurfaceKHR(instance, &createInfo, allocator, surface);
		return result;
#endif
	}
}