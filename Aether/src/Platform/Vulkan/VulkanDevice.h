#pragma once

#include "Vulkan.h"

namespace Aether {

	struct QueueFamilyIndices
	{
		uint32_t Graphics;
		uint32_t Compute;
		uint32_t Transfer;

		QueueFamilyIndices()
		{
			Graphics = -1;
			Compute = -1;
			Transfer = -1;
		}
	};

	QueueFamilyIndices GetQueueFamilyIndices(VkPhysicalDevice device);

	class VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice();
		~VulkanPhysicalDevice();

		static Scope<VulkanPhysicalDevice> Select();
	private:
		VkPhysicalDevice m_PhysicalDevice = nullptr;
		VkPhysicalDeviceProperties m_PhysicalDeviceProperties;
		VkPhysicalDeviceFeatures m_PhysicalDeviceFeatures;
		VkPhysicalDeviceMemoryProperties m_PhysicalDeviceMemoryProperties;

		std::vector<std::string> m_SupportedExtensions;
		std::vector<VkDeviceQueueCreateInfo> m_QueueCreateInfos;

		QueueFamilyIndices m_QueueFamilyIndices;

		friend class VulkanDevice;
	};

	// Logical Device
	class VulkanDevice
	{
	public:
		VulkanDevice();
		~VulkanDevice();


	private:
		VkDevice m_LogicalDevice = nullptr;
		Ref<VulkanPhysicalDevice> m_PhysicalDevice;
		VkPhysicalDeviceFeatures m_EnabledFeatures;

		VkQueue m_GraphicsQueue;
		VkQueue m_ComputeQueue;
	};
}