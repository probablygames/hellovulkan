
#include <chrono>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>


template<typename T>
void *V(T *t) {
  return reinterpret_cast<void*>(t);
}

void InitGLFW() {
  if (GLFW_TRUE != glfwInit()) {
    std::cerr << "glfwInit" << std::endl;
    return -1;
  } else {
    std::cerr << "GLFW_TRUE == glfwInit()" << std::endl;
  }
  if (GLFW_TRUE != glfwVulkanSupported()) {
    std::cerr << "glfwVulkanSupported()" << std::endl;
    return -1;
  } else {
    std::cerr << "GLFW_TURE == glfwVulkanSupported()" << std::endl;
  }

}

void LayersExtensions() {
  uint32_t glfw_extensions_count;
  const char **extensions = glfwGetRequiredInstanceExtensions(&glfw_extensions_count);
  std::cerr << "RequiredInstanceExtensions: " << std::endl;
  for (uint32_t k = 0 ; k < glfw_extensions_count; ++k) {
    std::cerr << extensions[k] << std::endl;
  }

  uint32_t property_count;
  if (VK_SUCCESS != vkEnumerateInstanceLayerProperties(&property_count, NULL)) {
    
  }
  VkLayerProperties *layer_properties = new VkLayerProperties[property_count];

  if (VK_SUCCESS != vkEnumerateInstanceLayerProperties(
          &property_count, layer_properties)) {
    
  }
  for (int k = 0; k < property_count; ++k) {
    uint32_t layer_property_count;
    if (VK_SUCCESS != vkEnumerateInstanceExtensionProperties(
           layer_properties[k].layer_name, &layer_property_count, NULL)) {
    }
    VkExtensionProperties *extension_properties = new VkExtensionproperties[layer_property_count];
     if (VK_SUCCESS != vkEnumerateInstanceExtensionProperties(
            layer_properties[k].layer_name, &layer_property_count, 
            extension_properties)) {
    }
  }
}

void CreateVulkanInstance() {
  PFN_vkCreateInstance create_instance = (
      (PFN_vkCreateInstance) glfwGetInstanceProcAddress(
          NULL, "vkCreateInstance"));
  std::cerr << "vkCreateInstance : " << V(vkCreateInstance) << std::endl;
  std::cerr << " create_instance : " << V(create_instance) << std::endl;

  VkApplicationInfo app_info;
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pNext = NULL;
  app_info.pApplicationName = "waveycrocket";
  app_info.applicationVersion = 1;
  app_info.pEngineName = "waveycrocket";
  app_info.engineVersion = 1;
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo ivc_info;
  ivc_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  ivc_info.pNext = NULL;
  ivc_info.flags = 
  ivc_info.pApplicationInfo = &app_info;
  ivc_info.enabledLayerCount =
  ivc_info.ppEnabledLayerNames =
  ivc_info.enabledExtensionCount = 
  ivc_info.ppEnabledExtensionNames = 

  // VkAllocationCallbacks allocation_callbacks;

  VkInstance instance;
  if (VK_SUCCESS != create_instance(&create_info, NULL,  &instance)) {
    std::cerr << "vkCreateInstance!" << std::endl;
    return -1;
  }
}

void CreateDebugReport() {
  PFN_vkCreateDebugReportCallbackEXT create_debug_report_func =
      reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(
          vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
  assert(create_debug_report_func != nullptr);

  VkDebugReportcallbackEXT *callback;
  VkDebugReportCallbackCreteInfoEXT create_info;
  
  vkCreateDebugReportCallbackEXT(
    instance, &create_info, NULL, callback)
}

void DestroyDebugReport() {
  PFN_vkDestroyDebugReportCallbackEXT destroy_debug_callback_func =
        reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(
            vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
  destroy_debug_callback_func(instance, callback, nullptr);
}

void EnumerateDevices() {
  uint32_t device_count;
  if (VK_SUCCESS != vkEnumeratePhysicalDevices(instance, &device_count, NULL)){ 
  }

  VkPhysicalDevice *devices = new VkPhysicalDevice[device_count];
  if (VK_SUCCESS != vkEnumeratePhysicalDevices(instance, &device_count, devices)){ 
  }
}

void DeviceQueueFamily() {
  uint32_t *queue_family_property_count;
  vkGetPhysicalDeviceQueueFamilyProperties(
      physical_device, &queue_family_property_count, NULL);

  VkQueueFamilyProperties *queue_family_properties = (
      new VkQueueFamilyProperties[queue_family_property_count]);
  vkGetPhysicalDeviceQueueFamilyProperties(
      physical_device, &queue_family_property_count, queue_family_properties);

}

void DeviceProperties() {
  VkPhysicalDeviceMemoryProperties memory_properties;
  vkGetPhysicalDeviceMemoryProperties(physical_device, &memory_properties);

  VkPhysicalDeviceProperties device_properties;
  vkGetPhysicalDeviceProperties(physical_device, &device_properties); 

  VkPhysicalDeviceFeatures device_features;
  vkGetPhysicalDeviceFeatures(physical_device, &device_features);

}


void CreateSurface() {
  for (uint32_t k = 0; k < *queue_family_property_count; ++k) {
    if (GLFW_TRUE != glfwGetPhysicalDevicePresentationSupport(
            instance, physical_device, queue_family_index)) {
    } else {
      queue_family_index = k;
  }

  /*
  vkGetPhysicalDeviceSurfaceSupportKHR(
      physicalDevice, queueFamilyIndex, static_cast<VkSurfaceKHR>( surface ), pSupported )
  */

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow *window = glfwCreateWindow(640, 480, "Wavey Crocket", NULL, NULL);

  VkSurfaceKHR surface;
  VkAllocationCallbacks *allocator = NULL;
  if (VK_SUCCESS != glfwCreateWindowSurface(instance, window, allocator, &surface)) {

  }

  uint32_t surface_format_count;
  if (VK_SUCCESS != vkGetPhysicalDeviceSurfaceFormatsKHR(
          physical_device, surface, &surface_format_count, NULL)) {
  }

  VkSurfaceFormatKHR *surface_formats = new VkSurfaceFormatKHR[surface_format_count];
   if (VK_SUCCESS != vkGetPhysicalDeviceSurfaceFormatsKHR(
          physical_device, surface, &surface_format_count, surface_formats)) {
  }
  VkSurfaceFormatKHR surface_format = VK_FORMAT_B8G8R8A8_UNORM;
}

void CreateDevice() {
  PFN_vkCreateDevice create_device = (
      (PFN_vkCreateDevice) glfwGetInstanceProcAddress(
          NULL, "vkCreateDevice"));
  std::cerr << "vkCreateDevice : " << V(vkCreateDevice) << std::endl; 
  std::cerr << " create_device : " << V(create_device) << std::endl;


  PFN_vkGetDeviceProcAddr get_device_proc_addr = (
      (PFN_vkGetDeviceProcAddr) glfwGetInstanceProcAddress(
          NULL, "vkGetDeviceProcAddr"));

  std::cerr << " vkGetDeviceProcAddr : " << V(vkGetDeviceProcAddr) << std::endl;
  std::cerr << "get_device_proc_addr : " << V(get_device_proc_addr) << std::endl;

  float queue_priority = 1.0f;


  VkDeviceQueueCreateInfo qcr_info;
  qcr_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  qcr_info.pNext = NULL;  // VkDeviceQueueGlobalPriorityCreateInfoEXT
  qcr_info.flags = 0;
  qcr_info.queueFamilyIndex = queue_family_index;
  qcr_info.queueCount = 1;
  qcr_info.pQueuePriority = &queue_priority;
  
  char *swapchain_extension = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

  VkCreateDeviceInfo dcr_info;
  dcr_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  dcr_info.pNext = NULL;
  dcr_info.flags = 0;  // VkDeviceCreateFlags
  dcr_info.queueCreateInfoCount = 1
  dcr_info.pQueueCreateInfos = &qcr_info;
  //dcr_info.enabledLayerCount =  ;
  //dcr_info.ppEnabledLayerNames =  ;
  dcr_info.enabledExtensionCount = 1;
  dcr_info.ppEnabledExtensionNames =  &swapchain_extension;
  dcr_info.pEnabledFeatures = &device_features;

  VkDevice device;
  if (VK_SUCCESS != VkCreateDevice(
          physical_device, &dcr_info, NULL, &device)) {
  }
}

void CreateCommandPool() {
  VkCommandPoolCreateInfo pcr_info;

  pcr_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pcr_info.pNext = NULL;
  pcr_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  pcr_info.queueFamilyIndex = queue_family_index;
    // VK_COMMAND_POOL_CREATE_TRANSIENT_BIT = 0x00000001,
    // VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT = 0x00000002,
    // VK_COMMAND_POOL_CREATE_PROTECTED_BIT 

  VkCommandPool command_pool;
  if (VK_SUCCESS != vkCreateCommandPool(
          device, &pcr_info, NULL, &command_pool)) {
  }

  VkQueue queue;
  uint32_t queue_index = 0;  // queueCreateInfoCount == 1
  vkGetDeviceQueue(device, queue_family_index, queue_index, &queue);

  // make present_complete and render_complete
  VkSemaphore semaphore[2];
  for (int k = 0; k < 2; ++k) {
    VkSemaphoreCreateInfo scr_info;
    scr_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    scr_info.pnext = NULL;
    scr_info.flags = 0;
    if (VK_SUCCESS != VkCreateSemaphore(
            device, &scr_info, NULL, &semaphore[k])) {
    }
  }
}

void CreateSwapchain() {
  VkSurfaceCapabilitiesKHR surface_capabilities;
  if (VK_SUCCESS != vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
          physical_device, surface, &surface_capabilities)) {
  }

  VkExtent2D extent;
  if ((surface_capabilities.currentExtent.width == 0xFFFFFFFF &&
       surface_capabilities.currentExtent.height == 0xFFFFFFFF)) {
    extent = ;
  } else {
    extent = surface_capabilities.currentExtent;
  }

  uint32_t present_modes_count;
  if (VK_SUCCESS != vkGetPhysicalDeviceSurfacePresentModesKHR(
          physical_device, surface, &present_modes_count, NULL)) {

  }
  VkPresentModeKHR *present_modes = new VkPresentModesKHR[present_modes_count];
  // VK_PRESENT_MODE_IMMEDIATE_KHR = 0,
  //  VK_PRESENT_MODE_MAILBOX_KHR = 1,
  //  VK_PRESENT_MODE_FIFO_KHR = 2,
  //  VK_PRESENT_MODE_FIFO_RELAXED_KHR = 3,
  if (VK_SUCCESS != vkGetPhysicalDeviceSurfacePresentModesKHR(
          physical_device, surface, &present_modes_count, present_modes)) {

  }
  
  uint32_t image_count;
  if (surface_capabilities.maxImageCount != 0) {
    image_count = std::min(
        surface_capabilities.maxImageCount,
        surface_capabilities.minImageCount + 1);
  } else {
    image_count = surface_capabilities.minImageCount + 1;
  }

  VkSurfaceTransformFlagBitsKHR transform;
  if (surface_cappabilities.supportedTransforms  & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
    transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  } else {
    transform = surface_cappabilities.currentTransform;
  }
  // VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
  // VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR,
  // VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR,
  // VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR,
  // VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR,
  // VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR,
  // VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR,
  // VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR,
  // VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR

  VkSwapchainCreateInfoKHR scr_info;
  scr_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  scr_info.pNext = NULL;
  scr_info.flags = 0;
  scr_info.surface = surface;
  scr_info.minImageCount = image_count;
  scr_info.imageFormat = surface_format;
  scr_info.imageExtent = extent;
  scr_info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR; // only one supported ?
  scr_info.imageArrayLayers = 1 ;  // non-stereoscopic
  scr_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT 
  // VK_IMAGE_USAGE_TRANSFER_SRC_BIT
  // VK_IMAGE_USAGE_TRANSFER_DST_BIT
  // VK_IMAGE_USAGE_SAMPLED_BIT 
  // VK_IMAGE_USAGE_STORAGE_BIT
  // VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT 
  //  VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT 
  //  VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT
  //  VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
  scr_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;  // VK_SHARING_MODE_CONCURRENT
  scr_info.queueFamilyIndexCount = 0; // nonzero only if CONCURRENT
  scr_info.pQueueFamilyIndices = NULL;
  scr_info.preTransform = transform;
  scr_info.compositeAlpha =  VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  // VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR = 0x00000001,
  //  VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR = 0x00000002,
  //  VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR = 0x00000004,
  //  VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR = 0x00000008,
  scr_info.clipped = VK_TRUE;
  scr_info.oldSwapchain = VK_NULL_HANDLE;

  VkSwapchainKHR swapchain;
  if (VK_SUCCESS != vkCreateSwapchainKHR(
          device, &scr_info, NULL, &swapchain)) {
  }
}

void GetSwapchainImages() {
  uint32_t swapchain_image_count;
  if (VK_SUCCESS != vkGetSwapchainImagesKHR(
          device, swapchain, &swapchain_image_count, NULL)) {
  }
  VkImage *swapchain_images = new VkImage[swapchain_image_count];
  if (VK_SUCCESS != vkGetSwapchainImagesKHR(
          device, swapchain, &swapchain_image_count, swapchain_images)) {
  }

  for (int k = 0; k < swapchain_image_count; ++k) {
    VkImageViewCreateInfo ivc_info;
    ivc_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivc_info.pNext = NULL; // VkImageViewUsageCreateInfo, VkImageUsageFlagBits
    ivc_info.flags = 0;
    ivc_info.image = swapchain_images[k];
    ivc_info.viewType = VK_IMAGE_VIEW_TYPE_2D; // VkImageViewType
    ivc_info.format = surface_format;
    ivc_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    ivc_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    ivc_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    ivc_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    ivc_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;  // DEPTH, STENCIL
    ivc_info.subresourceRange.baseMipLevel = 0;
    ivc_info.subresourceRange.levelCount = 1;
    ivc_info.subresourceRange.baseArrayLayer = 0;
    ivc_info.subresourceRange.layerCount = 1;
  
    VkImageView image_view;
    if (VK_SUCCESS != vkCreateImageView(
            device, &ivc_info, NULL, &image_view)) {
    }
  }
}



void SetImageLayout() {
  VkImageSubresourceRange x;
  VkImageMemoryBarrier y;
  vkCmdPipelineBarrier ;
}

int32_t HostVisibleCoherentMemoryType() {
  VkMemoryType desired_type = (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                               VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

  int32_t selected = -1;
  for (int32_t k = 0; k < memory_properties.memoryTypeCount; ++k) {
    if (memory_requirements.memoryTypeBits & (1 << k)) {
      if ((memory_properties.memoryTypes[k].propertyFlags & desired_type) == desired_type) {
        selected = k;
        break;
      }
    }
  }
  if (selected == -1) {
    // ruh roh
  }

}

void CreateImage() {
  VkImageCreateInfo icr_info;
  icr_info.sType = K_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  icr_info.pNext = NULL;
  // VkDedicatedAllocationImageCreateInfoNV, VkExternalFormatANDROID,
  // VkExternalMemoryImageCreateInfo, VkExternalMemoryImageCreateInfoNV, 
  // VkImageFormatListCreateInfoKHR, or VkImageSwapchainCreateInfoKHR
  icr_info.flags = 0;  // VkImageCreateFlagBits
  icr_info.imageType = VK_IMAGE_TYPE_2D;
  icr_info.format = VK_FORMAT_R8G8B8A8_UNORM;
  icr_info.extent.width = width;
  icr_info.extent.height = height;
  icr_info.extent.depth = depth;
  icr_info.mipLevels = 1;
  icr_info.arrayLayers = 1;
  icr_info.samples = VK_SAMPLE_COUNT_1_BIT;
  icr_info.tiling = VK_IMAGE_TILING_LINEAR;
  icr_info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
  icr_info.sharingMode = VK_SHARING_MODE_EXLUCSIVE;
  icr_info.queueFamilyIndexCount = 0;
  icr_info.pQueueFamilyIndices = NULL;  // unused becaue EXCLUSIVE
  icr_info.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;

  VkImage image;
  if (VK_SUCCESS != vkCreateImage(device, &ivc_info, NULL, &image)) {
  }

  VkMemoryRequirements memory_requirements;
  vkGetImageMemoryRequirements(device, image, &memory_requirements);

  int32_t selected = HostVisibleCoherentMemoryType();
  
  VkMemoryAllocateInfo mal_info;
  mal_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  mal_info.pNext = NULL;  
  mal_info.allocationSize = memory_requirements.size;
  mal_info.memoryTypeIndex = selected;

  VkDeviceMemory memory;
  if (VK_SUCCESS != vkAllocateMemory(device, &mal_info, NULL, &memory)) {
  }
  
  if (VK_SUCCESS != vkBindImageMemory(device, image, memory, 0)) {
  }

}

void CreateImageView() {
  VkImageSubresource subresource;
  subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  subresource.mipLevel = 0;
  subresource.arrayLayer = 0;
  
  VkSubresourceLayout layout;
  vkGetImageSubresourceLayout(device, image, &subresource, &layout);

  VkImageSubresourceRange range;

  VkImageViewCreateInfo ivc_info;
  ivc_info.stype = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  ivc_info.pNext = NULL; // VkImageViewUsageCreateInfo, VkImageUsageFlagBits
  ivc_info.flags = 0;
  ivc_info.image = image;
  ivc_info.viewType = VK_IMAGE_VIEW_TYPE_2D; // VkImageViewType
  ivc_info.format = VK_FORMAT_B8G8R8A8_UNORM;
  ivc_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
  ivc_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
  ivc_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
  ivc_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
  ivc_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  ivc_info.subresourceRange.baseMipLevel = 0;
  ivc_info.subresourceRange.levelCount = 1;
  ivc_info.subresourceRange.baseArrayLayer = 0;
  ivc_info.subresourceRange.layerCount = 1;
  
  VkImageView image_view;
  if (VK_SUCCESS != vkCreateImageView( device, &ivc_info, NULL, &image_view)) {
  }

}

void MapMemory() {
  void *data;
  if (VK_SUCCESS != vkMapMemory(device, memory, 0, memory_requirements.size, 0, &data) {
  }

}

void CreateSampler() {
  VkSamplerCreateInfo scr_info;
  scr_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  scr_info.pNext = NULL;  // VkSamplerReductionModeCreateInfoEXT or VkSamplerYcbcrConversionInfo
  scr_info.flags = 0;
  scr_info.magFilter = VK_FILTER_LINEAR;
  scr_info.minFilter = VK_FILTER_LINEAR;
  scr_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
  scr_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  scr_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  scr_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  scr_info.mipLodBias = 0.0f;
  scr_info.anisotropyEnable = VK_FALSE;
  scr_info.maxAnisotropy = 0.0f;
  scr_info.compare_enable = VK_FALSE;
  scr_info.compareOp = VK_COMPARE_OP_NEVER;
  scr_info.minLod = 0.0f;
  scr_info.maxLod = 0.0f;
  scr_info.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
  scr_info.unnormalizedCoordinaets = VK_FALSE;
  
  VkSampler sampler;
  if (VK_SUCCESS != vkCreateSampler(device, &scr_info, NULL, &sampler)) {
  }

  VkDescriptorImageInfo descriptor_image_info;
  descriptor_image_info.sampler = sampler;
  descriptor_image_info.imageView = image_view;
  descriptor_image_info.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
}

void CreateCommandBuffer() {
  VkCommandBufferAllocateInfo cba_info;
  cba_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cba_info.pNext = NULL;
  cba_info.commandPool = command_pool;
  cba_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cba_info.commandBufferCount = 1;

  VkCommandBuffer command_buffers[1];
  if (VK_SUCCESS != vkAllocateCommandBuffers(
          device, &cba_info, command_buffers)) {
  }
}

void InitDepthBuffer() {
  VkFormatProperties format_properties;
  vkGetPhysicalDeviceFormatProperties(
      physical_device, VK_FORMAT_D16_UNORM, &format_properties); 
  
  if (format_properties.linearTilingFeatures &
      VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
    tiling = VK_IMAGE_TILING_LINEAR;
  } else
  if (format_properties.optimalTilingFeatures &
      VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
    tiling = VK_IMAGE_TILING_OPTIMAL;
  } else {
  }
  VkImage depth_image;
  CreateImage(tiling);
  
  VkImageView depth_image_view;
  CreateImageView();

  VkCommandBufferBeginInfo cbb_info;
  cbb_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  cbb_info.pNext = NULL;  // VkDeviceGroupCommandBufferBeginInfo
  cbb_info.flags = 0;  // VK_COMMAND_BUFFER_USAGE_*
  cbb_info.pInheritanceInfo = NULL;
  vkBeginCommandBuffer(command_buffer, &cbb_info);

  VkImageMemoryBarrier image_memory_barrier;
  image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  image_memory_barrier.pNext = NULL;  // VkSampleLocationsInfoEXT
  image_memory_barrier.srcAccessMask = 
  image_memory_barrier.dstAccessMask = 
  image_memory_barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  image_memory_barrier.newlayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  image_memory_barrier.srcQueueFamilyIndex = 
  image_memory_barrier.dstQueueFamilyIndex = 
  image_memory_barrier.image
  image_memory_barrier.subresourcerange

  vkCmdPipelineBarrier(
      command_buffer,
      VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT , // srcStage
      VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT , // dstStage
      0,  // VkDependencyFlagBits
      memoryBarrierCount = 0, NULL,   
      bufferMemoryBarrierCount = 0, NULL,
      imageMemoryBarrierCount = 1,
      &image_memory_barrier);
}


void CreateVertexBuffer() {
  vertex_size_bytes == 6 * sizeof(float); // x y z w u v

  VkBufferCreateInfo bcr_info;
  bcr_info.pNext = NULL;  // VkDedicatedAllocationBufferCreateInfoNV or VkExternalMemoryBufferCreateInfo
  bcr_info.flags = 0;
  bcr_info.size = vertex_count * vertex_size_bytes;
  bcr_info.usage =  VK_BUFFER_USAGE_VERTEX_BUFFER_BIT ;
  bcr_info.sharingMode = VK_SHARING_MODE_EXLUCSIVE;
  bcr_info.queueFamilyIndexCount = 0;
  bcr_info.pQueueFamilyIndices = NULL; // EXCLUSIVE

  VkBuffer buffer;
  if (VK_SUCCESS != vkCreateBuffer(device, &bcr_info, NULL, &buffer)) {
  }

  VkMemoryRequirements memory_requirements;
  vkGetBufferMemoryRequirements(device, vuffer, &memory_requirements);

  int32_t selected = HostVisibleCoherentMemoryType();
  
  VkMemoryAllocateInfo mal_info;
  mal_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  mal_info.pNext = NULL;  
  mal_info.allocationSize = memory_requirements.size;
  mal_info.memoryTypeIndex = selected;

  VkDeviceMemory memory;
  if (VK_SUCCESS != vkAllocateMemory(device, &mal_info, NULL, &memory)) {
  }
 
  if (VK_SUCCESS != vkBindBufferMemory(device, buffer, memory, 0)) {
    
  }

  VkVertexInputBindingDescription vertex_input_binding;
  vertex_input_binding.binding = 0;
  vertex_input_binding.stride = vertex_size_bytes;
  vertex_input_binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

  VkVertexInputAttributeDescription attributes[2];
  attributes[0].location = 0;
  attributes[0].binding = 0;
  attributes[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
  attributes[0].offset = 0;
  attributes[1].location = 1;
  attributes[1].binding = 0;
  attributes[1].format = VK_FORMAT_R32G32_SFLOAT;
  attributes[1].offset = 4 * sizeof(float);

  VkPipelineVertexInputStateCreateInfo pvi_info;
  pvi_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  pvi_info.pNext = NULL;  // VkPipelineVertexInputDivisorStateCreateInfoEXT
  pvi_info.flags = 0;
  pvi_info.vertexBindingDescriptionCount = 1;
  pvi_info.pVertexBindingDescriptions = &binding;
  pvi_info.vertexAttributeDcescriptionCount = 2;
  pvi_info.pVertexAttributeDescriptions = attributes;

  VkPipelineInputAssemblyStateCreateInfo pia_info;
  pia_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  pia_info.pNext = NULL;
  pia_info.flags = 0;
  pia_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  pia_info.primiteRestartEnable = VK_FALSE;
}

void UniformBuffer4x4() {
  float fov = glm::radians(45.0f);
  vk::Extent2D surface_size = device_->SurfaceSize();
  if (surface_size.width > surface_size.height) {
    fov *= static_cast<float>(surface_size.height) /
           static_cast<float>(surface_size.width);
  }
  glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::lookAt(
      glm::vec3(0, 0, 5),   // Camera is at (0,0,5), in World Space
      glm::vec3(0, 0, 0),   // and looks at the origin
      glm::vec3(0, 1, 0));  // Head is up (set to 0,-1,0 to look upside-down)

  glm::mat4 model = glm::mat4(1.0f);
  // Vulkan clip space has inverted Y and half Z.
  glm::mat4 clip = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, -1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.5f, 0.0f,
                             0.0f, 0.0f, 0.5f, 1.0f);
  glm::mat4 mvp = clip * projection * view * model;

  

  // A lot like VertexBuffer, but
  bcr_info.usage =  VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT ;
  // and is mapped / initialized with the geometry transofrm matrix.

  VkDescriptorBufferInfo uniform_descriptor_buffer_info;
  uniform_descriptor_buffer_info.buffer = buffer;
  uniform_descriptor_buffer_info.offset = 0;
  uniform_descriptor_buffer_info.range = sizeof(mvp);  // glm::mat4
}

void CreateRenderPass() {
  VkAttachmentDescription attachments[2];
  attachments[0].flags = 0;
  attachments[0].format = surface_format;
  attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  attachments[0].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  attachments[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  attachments[1].flags = 0;
  attachments[1].format = VK_FORMAT_D16_UNORM;
  attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
  attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[0].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  attachments[0].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference color_reference;
  color_reference.attachment = 0;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  
  VkAttachmentRefernece depth_reference;
  depth_reference.attachment = 1;
  depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  
  VkSubpassDescription subpass;
  subpass.flags = 0;
  subpass.pipelineBindingPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.inputAttachmentCount = 0;
  subpass.pInputAttachment
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &color_reference;
  subpass.pDepthStencilAttachment = &depth_reference

  VkRenderPassCreateInfo rpc_info;
  rpc_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  rpc_info.pNext = NULL;  // VkRenderPassInputAttachmentAspectCreateInfo or VkRenderPassMultiviewCreateInfo
  rpc_info.flags = 0;
  rpc_info.attachmentCount = 2;
  rpc_info.pAttachments = attachments;
  rpc_info.subpassCount = 1;
  rpc_info.pSubpasses = &subpass;
  rpc_info.dependencyCount = 0;
  rpc_info.pDependencies = NULL;

  VkRenderPass render_pass;
  if (VK_SUCCESS != vkCreateRenderPass(
          device, &rpc_info, NULL, &render_pass)) {
  }
}


void CreateShaders() {
  static char const vertex_glsl[] = 
  "#version 400\n"
  "#extension GL_ARB_separate_shader_objects : enable\n"
  "#extension GL_ARB_shading_language_420pack : enable\n"
  "layout(std140, binding = 0) uniform buf { mat4 mvp; }\n"
  "ubuf;\n"
  "layout(location = 0) in vec4 pos;\n"
  "layout(location = 1) in vec2 inTexCoords;\n"
  "layout(location = 0) out vec2 texcoord;\n"
  "out gl_PerVertex { vec4 gl_Position; };\n"
  "void main() {\n"
  "  texcoord = inTexCoords;\n"
  "  gl_Position = ubuf.mvp * pos;\n"
  "}\n";

  VkShaderModuleCreateInfo vtx_info;
  vtx_info.sType =  VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  vtx_info.pNext = NULL; // VkShaderModuleValidationCacheCreateInfoEXT
  vtx_info.flags = 0;
  vtx_info.codeSize = sizeof(vertex_glsl);
  vtx_info.pCode = vertex_glsl;

  VkShaderModule vertex_shader_module;
  if (VK_SUCCESS != vkCreateShaderModule(device, &vtx_info, NULL, vertex_shader_module)) {
  }

  static char const fragment_glsl[] = 
  "#version 400\n"
  "#extension GL_ARB_separate_shader_objects : enable\n"
  "#extension GL_ARB_shading_language_420pack : enable\n"
  "layout(binding = 1) uniform sampler2D tex;\n"
  "layout(location = 0) in vec2 texcoord;\n"
  "layout(location = 0) out vec4 outColor;\n"
  "void main() { outColor = textureLod(tex, texcoord, 0.0); }\n";

  VkShaderModuleCreateInfo pix_info;
  pix_info.sType =  VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  pix_info.pNext = NULL; // VkShaderModuleValidationCacheCreateInfoEXT
  pix_info.flags = 0;
  pix_info.codeSize = sizeof(vertex_glsl);
  pix_info.pCode = fragment_glsl;

  VkShaderModule fragment_shader_module;
  if (VK_SUCCESS != vkCreateShaderModule(device, &pix_info, NULL, fragment_shader_module)) {
  }
}


void CreateFramebuffers() {
  for (int k = 0; k < swapchain_image_count; +k) {
    VkImageView attachments[2];
    attachments[0] = swapchain_image_view[k];
    attachments[1] = depth_image_view;
    VkFramebufferCreateInfo fbc_info;
    fbc_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbc_info.pNext = NULL;
    fbc_info.flags = 0;
    fbc_info.renderPass = render_pass;
    fbc_info.attachmentCount = 2;
    fbc_info.pAttachments = attachments;
    fbc_info.width = surface_extent.width;
    fbc_info.height = surface_extent.height;
    fbc_info.layers = 1;
  
    VkFramebuffer framebuffer;
    if (VK_SUCCESS != vkCreateFramebuffer(device, &fbc_info, NULL, &framebuffer)) {
    }
  }
}

void CreateDescriptorSet() {
  VkDescriptorSetLayoutBinding layout_bindings[2];
  layout_bindings[0].binding = 0;
  layout_bindings[0].descriptorType = VK_DECRIPTOR_TYPE_UNIFORM_BUFFER;
  layout_bindings[0].descriptorCount = 1;
  layout_bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  layout_bindings[0].pImmutableSamplers = NULL;

  layout_bindings[1].binding = 1;
  layout_bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  layout_bindings[1].descriptorCount= 1;
  layout_bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  layout_bindings[1].pImmutableSamplers = NULL;
  

  VkDescriptorSetLayoutCreateInfo dsl_info;
  dsl_info.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  dsl_info.pNext = NULL;  // of VkDescriptorSetLayoutBindingFlagsCreateInfoEXT
  dsl_info.flags = 0;
  dsl_info.bindingCount = 2;
  dsl_info.pBindings = layout_bindings;

  
  VkDescriptorSetLayout descriptor_set_layout;
  if (VK_SUCCESS != vkCreateDescriptorSetLayout(
          device, &dsl_info, NULL, &descriptor_set_layout)) {
  }

  VkDescriptorPoolSize desc_pool_sizes[2];
  desc_pool_sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  desc_pool_sizes[0].descriptorCount = 1;
  desc_pool_sizes[1].type  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  desc_pool_sizes[1].descriptorCount = 1;

  VkDescriptorPoolCreateInfo dpl_info;
  dpl_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  dpl_info.pNext = NULL;
  dpl_info.flags = 0
  dpl_info.maxSets = 1;
  dpl_info.poolSizeCount = 2;  
  dpl_info.pPoolSizes = desc_pool_sizes;
  VkDecriptorPool descriptor_pool;
  if (VK_SUCCESS != vkCreateDescriptorPool(
          device, &dpl_info, NULL, &descriptor_pool)) {
  }

  VkDescriptorSetAllocateInfo dsa_info;
  dsa_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  dsa_info.pNext = NULL;  //  VkDescriptorSetVariableDescriptorCountAllocateInfoEXT
  dsa_info.descriptorPool = descriptor_pool
  dsa_info.descriptorSetCount = 1;
  dsa_info.pSetLayouts = &descriptor_set_layout;

  VkDescriptorSet descriptor_set;
  if (VK_SUCCESS != vkAllocateDescriptorSets(
          device, &dsa_info, &descriptor_set)) {
  }

  VkWriteDescriptorSet write_descriptor[2];
  write_descriptor[0].sType =  VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  write_descriptor[0].pNext = NULL;
  write_descriptor[0].dstSet = descriptor_set;
  write_descriptor[0].dstBinding = 0;
  write_descriptor[0].dstArrayElement = 0;
  write_descriptor[0].descriptorCount = 1;
  write_descriptor[0].descriptorType = VK_DESTRIPTOR_TYPE_UNIFORM_BUFFER;
  write_descriptor[0].pImageInfo = NULL;
  write_descriptor[0].pBufferInfo = &uniform_descriptor_buffer_info; 
  write_descriptor[0].pTexelBufferView = NULL;

  write_descriptor[1].sType =  VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  write_descriptor[1].pNext = NULL;
  write_descriptor[1].dstSet = descriptor_set;
  write_descriptor[1].dstBinding = 1;
  write_descriptor[1].dstArrayElement = 0;
  write_descriptor[1].descriptorCount = 1;
  write_descriptor[1].descriptorType = VK_DESTRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  write_descriptor[1].pImageInfo = &descriptor_image_info;
  write_descriptor[0].pBufferInfo = NULL;
  write_descriptor[0].pTexelBufferView = NULL;

  
  vkUpdateDescriptorSets(device, 2, write_descriptor, 0, NULL);
}

void CreatePipeline() {
  VkPipelineCacheCreateInfo pcc_info;
  pcc_info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
  pcc_info.pNext = NULL;
  pcc_info.flags = 0;
  pcc_info.initialDataSize = 0;
  pcc_info.pInitialData = NULL;
  
  VkPipelineCache pipeline_cache;
  if (VK_SUCCESS != vkCreatePipelineCache(
          device, &pcc_info, NULL, &pipeline_cache)) {
  } 
  

  VkPipelineRasterizationStateCreateInfo prs_info;
  prs_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  prs_info.pNext = NULL;  //  VkPipelineRasterizationConservativeStateCreateInfoEXT or VkPipelineRasterizationStateRasterizationOrderAMDType
  prs_info.flags = 0;
  prs_info.depthClampEnable = VK_TURE;
  prs_info.rasterizerDiscardEnable = VK_FALSE;
  prs_info.polygonMode = VK_POLYGON_MODE_FILL;
  prs_info.cullMode = VK_CULL_MODE_BACK_BIT;
  prs_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
  prs_info.depthBiasEnable = VK_FALSE;
  prs_info.depthBiasClap = 0.0f;
  prs_info.depthBiasSlopeFactor = 0.0f;
  prs_info.lineWidth = 1.0f;

  VkPipelineColorBlendAttachmentState color_blend_state;
  color_blend_state.blendEnable = VK_FALSE;
  color_blend_state.srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  color_blend_state.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  color_blend_state.colorBlendOp = VK_BLEND_OP_ADD;
  color_blend_state.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  color_blend_state.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  color_blend_state.alphaBlendOp = VK_BLEND_OP_ADD;
  color_blend_state.colorWriteMask = (
      VK_COLOR_COMPOENENT_R_BIT |
      VK_COLOR_COMPOENENT_G_BIT |
      VK_COLOR_COMPOENENT_B_BIT |
      VK_COLOR_COMPOENENT_A_BIT);
  
  VkPipelineColorBlendStateCreateInfo pcb_info;
  pcb_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  pcb_info.pNext = NULL;
  pcb_info.logicOpEnable = VK_FALSE;
  pcb_info.logicOp = VK_LOGIC_OP_CLEAR;
  pcb_info.attachmentCount = 1;
  pcb_info.pAtachments = &color_blend_state;
  pcb_info.blendConstants[0] = 1.0f;
  pcb_info.blendConstants[1] = 1.0f;
  pcb_info.blendConstants[2] = 1.0f;
  pcb_info.blendConstants[3] = 1.0f;

  VkPipelineViewportStateCreateInfo pvs_info;
  pvs_info.sType = K_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  pvs_info.pNext= NULL;
  pvs_info.flags = 0;
  pvs_info.viewportCount = 1;
  pvs_info.pViewports = NULL;
  pvs_info.scissorCount = 1;
  pvs_info.pScissors = NULL;

  VkDynamicState dynamic_states[2];
  dynamic_states[0] = VK_DYNAMIC_STATE_VIEWPORT;
  dynamic_states[1] = VK_DYNAMIC_STATE_SCISSOR;

  VkPipelineDynamicStateCreateInfo pds_info;
  pds_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  pds_info.pNext = NULL;
  pds_info.flags = 0;
  pds_info.dynamicStateCount = 2; 
  pds_info.pDynamicStates = dynamic_states;


  VkStencilOpState stencil_op_state;
  stencil_op_state.failOp = VK_STENCIL_OP_KEEP;
  stencil_op_state.passOp = VK_STENCIL_OP_KEEP;
  stencil_op_state.depthFailOp = VK_STENCIL_OP_KEEP;
  stencil_op_state.compareOp = VK_COMPARE_OP_ALWAYS;
  stencil_op_state.writeMask = 0;
  stencil_op_state.reference = 0;

  VkPipelineDepthStencilStateCreateInfo dss_info;
  dss_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  dss_info.pNext = NULL;
  dss_info.flags = 0;
  dss_info.depthTestEnable = VK_FALSE;
  dss_info.depthWriteEnable = VK_FALSE;
  dss_info.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
  dss_info.depthBoundsTestEnable = VK_FALSE;
  dss_info.front = stencil_op_state;
  dss_info.back = stencil_op_state;
  dss_info.minDepthBounts = 0.0f;
  dss_info.max/epthBounts = 0.0f;
  
  VkPipelineMultisampleStateCreateInfo pms_info;
  pms_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  pms_info.pNext = NULL; // VkPipelineCoverageModulationStateCreateInfoNV, VkPipelineCoverageToColorStateCreateInfoNV, or VkPipelineSampleLocationsStateCreateInfoEXT
  pms_info.flags = 0;
  pms_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  pms_info.sampleShadingEnable = VK_FALSE;
  pms_info.minSampleShading = 0.0f;
  pms_info.pSampleMask = NULL;
  pms_info.alphaToCoverageEnable = VK_FALSE;
  pms_info.alphaToOneEnable = VK_FALSE;
  

  VkGraphicsPipelineCreateInfo pip_info;
  pip_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pip_info.pNext = NULL;  // VkPipelineDiscardRectangleStateCreateInfoEXT
  pip_info.layout = pipeline_layout

  VkPipelineLayoutCreateInfo plc_info;
  plc_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  plc_info.pNext = NULL;
  plc_info.flags = 0;
  plc_info.setLayoutCount = 1;
  plc_info.pSetLayouts = &descriptor_set_layout;
  plc_info.pushConstantRangeCount = 0;
  plc_info.pPushConstantRanges = NULL;
  
  VkPipelineLayout pipeline_layout;
  if (VK_SUCCESS != vkCreatePipelineLayout(
          device, &plc_info, NULL, &pipeline_layout)) {
  }

  VkShaderStageCreateInfo ssc_info[2];
  ssc_info[0]
  ssc_info[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
  ssc_info[0].pName = "main";
  ssc_info[0].module =

  ssc_info[1]
  ssc_info[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  ssc_info[1].pName = "main";
  ssc_info[1].module =
  

  VkGraphicsPipelineCreateInfo gpc_info;
  gpc_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  gpc_info.pNext = NULL;
  gpc_info.flags = 0;
  gpc_info.stageCount = 2;
  gpc_info.pStages = ssc_info;
  gpc_info.pVertexInputState = &pvi_info;
  gpc_info.pInputAssemblyState = &pia_info;
  gpc_info.pTesselationState = NULL;
  gpc_info.pViewportState = &pvs_info;
  gpc_info.pRasterizationState = &prs_info;
  gpc_info.pMultisampleState = &pms_info;
  gpc_info.pDepthStencilState = &dss_info;
  gpc_info.pColorBlendState = &pcb_info;
  gpc_info.pDynamicState = &pdsinfo;
  gpc_info.layout = pipeline_layout
  gpc_info.renderPass = render_pass;
  gpc_info.subpass = 0;
  gpc_info.basePipelineHandle = VK_NULL_HANDLE
  gpc_info.basePipelineIndex = 0;

  VkPipeline pipeline;
  if (VK_SUCCESS != vkCreateGrahicsPipelines(
        device, pipeline_cache, 1, &pipeline_create_info, NULL, &pipeline)) {
  }
  
}

int main() {
  // Call all the things above :)
}
