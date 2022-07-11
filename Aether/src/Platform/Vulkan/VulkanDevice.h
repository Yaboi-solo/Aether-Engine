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

		bool isExtensionSupported(const std::string& extensionName);

		VkPhysicalDevice GetVulkanPhysicalDevice() const { return m_PhysicalDevice; }

		uint32_t GetMemoryTypeIndex(uint32_t typeBits, VkMemoryPropertyFlags properties);

		static Scope<VulkanPhysicalDevice> Select();
	private:
		VkPhysicalDevice m_PhysicalDevice = nullptr;
		VkPhysicalDeviceProperties m_PhysicalDeviceProperties;
		VkPhysicalDeviceFeatures m_PhysicalDeviceFeatures;
		VkPhysicalDeviceMemoryProperties m_PhysicalDeviceMemoryProperties;

		std::set<std::string> m_SupportedExtensions;
		std::vector<VkDeviceQueueCreateInfo> m_QueueCreateInfos;

		QueueFamilyIndices m_QueueFamilyIndices;

		float m_DefaultQueuePriority = 0.0f;

		friend class VulkanDevice;
	};

	// Logical Device
	class VulkanDevice
	{
	public:
		VulkanDevice(const Ref<VulkanPhysicalDevice>& physicalDevice, VkPhysicalDeviceFeatures enabledFeatures);
		~VulkanDevice();

		void Destroy();

		VkQueue GetGraphicsQueue() { return m_GraphicsQueue; }
		VkQueue GetComputeQueue() { return m_ComputeQueue; }
		VkQueue GetTransferQueue() { return m_TransferQueue; }

		const Ref<VulkanPhysicalDevice>& GetPhysicalDevice() const { return m_PhysicalDevice; }
		VkDevice GetVulkanDevice() const { return m_LogicalDevice; }
	private:
		VkDevice m_LogicalDevice = nullptr;
		Ref<VulkanPhysicalDevice> m_PhysicalDevice;
		VkPhysicalDeviceFeatures m_EnabledFeatures;

		VkQueue m_GraphicsQueue;
		VkQueue m_ComputeQueue;
		VkQueue m_TransferQueue;

		VkCommandPool m_GraphicsCommandPool;
		VkCommandPool m_ComputeCommandPool;
	};
}