#pragma once
#include "Renderer/GraphicsCore.h"
#include "Core/Window.h"

#include <vulkan/vulkan.h>

namespace Vortex
{
    class VORTEX_API VulkanCore : public GraphicsCore
    {
        public:
            VulkanCore(const WindowProperties& properties, bool enableValidationLayers);
       
        private:
            void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerInfo);

            bool CheckValidationLayerSupport();
            const std::vector<const char*>& GetRequiredExtensions();


        private:
            bool b_EnableValidationLayers;

            std::vector<const char*> m_InstanceExtensions;
            std::vector<const char*> m_ValidationLayers;
        private:
            VkInstance m_Instance;
            VkPhysicalDevice m_PhysicalDevice;
            VkDevice m_Device;
    };
}
