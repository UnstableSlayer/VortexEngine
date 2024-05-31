#include "SDL_vulkan.h"
#include "vpch.h"
#include "VulkanCore.h"

#include "Core/App.h"

namespace Vortex 
{
        

    VulkanCore::VulkanCore(const WindowProperties &properties, bool enableValidationLayers) : b_EnableValidationLayers(enableValidationLayers)
    {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = properties.title.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "VortexEngine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        VkInstanceCreateInfo instanceInfo = {};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pApplicationInfo = &appInfo;

        uint32_t sdlExtensionCount = 0;
        SDL_Vulkan_GetInstanceExtensions((SDL_Window*)App::Get().GetWindow().GetAPIWindow(), &sdlExtensionCount, nullptr);
        std::vector<const char*> extensions(sdlExtensionCount);
        SDL_Vulkan_GetInstanceExtensions((SDL_Window*)App::Get().GetWindow().GetAPIWindow(), &sdlExtensionCount, extensions.data());
        
        if(enableValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        instanceInfo.enabledExtensionCount = sdlExtensionCount;
        instanceInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugMessengerInfo = {};
        if(enableValidationLayers)
        {
            //instanceInfo.enabledLayerCount =  
        }
    }
}
