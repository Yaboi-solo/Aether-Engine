#include "atpch.h"
#include "VulkanContext.h"

#include "Core/Application.h"

namespace Aether {

	static bool s_Validation = true;

	bool isVulkanSupported();

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
		switch (flags)
		{
		case VK_DEBUG_REPORT_ERROR_BIT_EXT: AT_ERROR("Vulkan Debug Callback:\n	Object Type: {0}\n	Message: {1}", (int)objectType, pMessage); break;
		case VK_DEBUG_REPORT_WARNING_BIT_EXT: AT_WARN("Vulkan Debug Callback:\n	Object Type: {0}\n	Message: {1}", (int)objectType, pMessage); break;
		case VK_DEBUG_REPORT_INFORMATION_BIT_EXT: AT_INFO("Vulkan Debug Callback:\n	Object Type: {0}\n	Message: {1}", (int)objectType, pMessage); break;
		default: AT_TRACE("Vulkan Debug Callback:\n	Object Type: {0}\n	Message: {1}", (int)objectType, pMessage); break;
		}
		return VK_FALSE;
	}

	VulkanContext::VulkanContext(void* window, uint32_t width, uint32_t height)
	{
		m_Window = window;
		m_WindowWidth = width;
		m_WindowHeight = height;
	}

	VulkanContext::~VulkanContext()
	{
		vkDestroyCommandPool(m_Device->GetVulkanDevice(), m_TransferCommandPool, nullptr);
		
		m_Swapchain.Destroy();

		m_Swapchain.DestroySurface();
		
		m_Device->Destroy();

		if (s_Validation)
		{
			auto vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(s_VulkanInstance, "vkDestroyDebugReportCallbackEXT");
			AT_ASSERT(vkDestroyDebugReportCallbackEXT != NULL, "");
			vkDestroyDebugReportCallbackEXT(s_VulkanInstance, m_DebugReportCallback, nullptr);
		}
		
		vkDestroyInstance(s_VulkanInstance, nullptr);
		s_VulkanInstance = nullptr;
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
		// Instance Creation
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
		
		AT_TRACE("Created Vulkan surface.");

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Device Creation
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		m_PhysicalDevice = VulkanPhysicalDevice::Select();

		VkPhysicalDeviceFeatures features = {};
		features.samplerAnisotropy = true;
		//features.wideLines = true;
		//features.fillModeNonSolid = true;
		//features.independentBlend = true;
		//features.pipelineStatisticsQuery = true;
		m_Device = CreateRef<VulkanDevice>(m_PhysicalDevice, features);

		m_Swapchain.Init(s_VulkanInstance, m_Device);

		m_Swapchain.CreateSurface(m_Window);
		AT_TRACE("Created surface.");
		
		m_Swapchain.Create(m_WindowWidth, m_WindowHeight);
		AT_TRACE("Created swapchain.");

		QueueFamilyIndices indices = GetQueueFamilyIndices(m_PhysicalDevice->GetVulkanPhysicalDevice());
			
		VkCommandPoolCreateInfo commandPoolInfo = {};
		commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolInfo.queueFamilyIndex = indices.Transfer;
		commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
		VK_CHECK_RESULT(vkCreateCommandPool(m_Device->GetVulkanDevice(), &commandPoolInfo, nullptr, &m_TransferCommandPool));
	}

	void VulkanContext::Resize(uint32_t width, uint32_t height)
	{
		m_Swapchain.Resize(width, height);
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
}