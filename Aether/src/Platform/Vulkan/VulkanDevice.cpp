#include "atpch.h"
#include "VulkanDevice.h"

#include "VulkanContext.h"

namespace Aether {
	VulkanDevice::VulkanDevice()
	{
		
	}

	VulkanDevice::~VulkanDevice()
	{
	}

	VulkanPhysicalDevice::VulkanPhysicalDevice()
	{
		uint32_t gpuCount = 0;
		vkEnumeratePhysicalDevices(VulkanContext::GetInstance(), &gpuCount, nullptr);
		AT_ASSERT(gpuCount > 0, "No Vulkan supporting GPUs have been found!");
		std::vector<VkPhysicalDevice> physicalDevices(gpuCount);
		vkEnumeratePhysicalDevices(VulkanContext::GetInstance(), &gpuCount, physicalDevices.data());

		VkPhysicalDevice selectedDevice = nullptr;
		for (VkPhysicalDevice device : physicalDevices)
		{
			VkPhysicalDeviceProperties properties;
			VkPhysicalDeviceFeatures features;
			VkPhysicalDeviceMemoryProperties memoryProperties;

			vkGetPhysicalDeviceProperties(device, &properties);
			vkGetPhysicalDeviceFeatures(device, &features);
			vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);


			if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				selectedDevice = device;
				break;
			}

		}

		if (!selectedDevice)
		{
			AT_TRACE("Could not find discrete GPU. Selecting available GPU.");
			selectedDevice = physicalDevices.front();
		}

		AT_ASSERT(selectedDevice, "Could not find any physical devices!");



		m_PhysicalDevice = selectedDevice;
		vkGetPhysicalDeviceProperties(m_PhysicalDevice, &m_PhysicalDeviceProperties);
		vkGetPhysicalDeviceFeatures(m_PhysicalDevice, &m_PhysicalDeviceFeatures);
		vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &m_PhysicalDeviceMemoryProperties);


		uint32_t extCount = 0;
		vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &extCount, nullptr);
		if (extCount > 0)
		{
			std::vector<VkExtensionProperties> extensions(extCount);
			vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &extCount, extensions.data());

			AT_TRACE("Physical Device has {0} extensions available: ", extCount);
			for (auto& ext : extensions)
			{
				m_SupportedExtensions.push_back(ext.extensionName);
				AT_TRACE("		{0}", ext.extensionName);
			}
			
		}
		
		const float defaultQueuePriority(0.0f);

		m_QueueFamilyIndices = GetQueueFamilyIndices(m_PhysicalDevice);


		// Checking if queue families are valid only the first time and not every time
		// Because if they are valid the first time, it should work every time
		AT_ASSERT(m_QueueFamilyIndices.Graphics != (uint32_t)-1, "Failed to retrieve graphics queue family index!");
		AT_ASSERT(m_QueueFamilyIndices.Compute != (uint32_t)-1, "Failed to retrieve compute queue family index!");
		AT_ASSERT(m_QueueFamilyIndices.Transfer != (uint32_t)-1, "Failed to retrieve transfer queue family index!");

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;

		if (requestedQueueTypes & VK_QUEUE_GRAPHICS_BIT)
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = m_QueueFamilyIndices.Graphics;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			m_QueueCreateInfos.push_back(queueInfo);
		}
		
		if (requestedQueueTypes & VK_QUEUE_COMPUTE_BIT)
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = m_QueueFamilyIndices.Compute;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			m_QueueCreateInfos.push_back(queueInfo);
		}

		if (requestedQueueTypes & VK_QUEUE_TRANSFER_BIT)
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = m_QueueFamilyIndices.Transfer;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			m_QueueCreateInfos.push_back(queueInfo); 
		}

		AT_INFO("Selected Physical Device: {0}", m_PhysicalDeviceProperties.deviceName);
	}

	VulkanPhysicalDevice::~VulkanPhysicalDevice()
	{
	}

	QueueFamilyIndices GetQueueFamilyIndices(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices = QueueFamilyIndices();


		uint32_t queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		AT_ASSERT(queueFamilyCount > 0, "");
		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

		
		for (uint32_t i = 0; i < queueFamilyCount; i++)
		{
			// If queue family supports compute but not graphics
			if (queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT && ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0))
			{
				indices.Compute = i;
			}


			// If queue family supports transfer but not graphics and compute
			if (queueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT && ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) && ((queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0))
			{
				indices.Transfer = i;
			}

			// If queue family supports graphics
			if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.Graphics = i;
			}
		}

		return indices;
	}

	Scope<VulkanPhysicalDevice> VulkanPhysicalDevice::Select()
	{
		return CreateScope<VulkanPhysicalDevice>();
	}
}