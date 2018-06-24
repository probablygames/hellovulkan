
#include <string.h>
#include <unistd.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define c(x) case x: return #x
char const *vkResultString(VkResult result) {
  switch (result) {
    c(VK_SUCCESS);
    c(VK_NOT_READY);
    c(VK_TIMEOUT);
    c(VK_EVENT_SET);
    c(VK_EVENT_RESET);
    c(VK_INCOMPLETE);
    c(VK_ERROR_OUT_OF_HOST_MEMORY);
    c(VK_ERROR_OUT_OF_DEVICE_MEMORY);
    c(VK_ERROR_INITIALIZATION_FAILED);
    c(VK_ERROR_DEVICE_LOST);
    c(VK_ERROR_MEMORY_MAP_FAILED);
    c(VK_ERROR_LAYER_NOT_PRESENT);
    c(VK_ERROR_EXTENSION_NOT_PRESENT);
    c(VK_ERROR_FEATURE_NOT_PRESENT);
    c(VK_ERROR_INCOMPATIBLE_DRIVER);
    c(VK_ERROR_TOO_MANY_OBJECTS);
    c(VK_ERROR_FORMAT_NOT_SUPPORTED);
    c(VK_ERROR_FRAGMENTED_POOL);
    c(VK_ERROR_SURFACE_LOST_KHR);
    c(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
    c(VK_SUBOPTIMAL_KHR);
    c(VK_ERROR_OUT_OF_DATE_KHR);
    c(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
    c(VK_ERROR_VALIDATION_FAILED_EXT);
    c(VK_ERROR_INVALID_SHADER_NV);
    c(VK_ERROR_OUT_OF_POOL_MEMORY_KHR);
    c(VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR);
    default: return "Invalid VkResult value";
  }
}

char const *vkPhysicalDeviceTypeString(VkPhysicalDeviceType device_type) {
  switch(device_type) {
    c(VK_PHYSICAL_DEVICE_TYPE_OTHER);
    c(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    c(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    c(VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU );
    c(VK_PHYSICAL_DEVICE_TYPE_CPU);
    default: return "Invalid PhysicalDeviceType value";
  }
}

char const *vkMemoryPropertyFlagBitsString(VkMemoryPropertyFlagBits bit) {
  switch(bit) {
    c(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    c(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
    c(VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    c(VK_MEMORY_PROPERTY_HOST_CACHED_BIT);
    c(VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT);
    // c(VK_MEMORY_PROPERTY_PROTECTED_BIT);
    default: return "Invalid VkMemoryPropertyFlagBits value";
  }
}

char const *vkMemoryHeapFlagBitsString(VkMemoryHeapFlagBits bit) {
  switch(bit) {
    c(VK_MEMORY_HEAP_DEVICE_LOCAL_BIT);
    // c(VK_MEMORY_HEAP_MULTI_INSTANCE_BIT);
    default: return "Invalid VkMemoryHeapFlagBits value";
  }
}

char const *vkQueueFlagBitsString(VkQueueFlagBits bit) {
  switch(bit) {
    c(VK_QUEUE_GRAPHICS_BIT);
    c(VK_QUEUE_COMPUTE_BIT);
    c(VK_QUEUE_TRANSFER_BIT);
    c(VK_QUEUE_SPARSE_BINDING_BIT);
    // c(VK_QUEUE_PROTECTED_BIT);
    default: return "Invalid VkQueueFlagBits value";
  }
}

char const *vkFormatString(VkFormat format) {
  switch(format) {
    c(VK_FORMAT_UNDEFINED);
    c(VK_FORMAT_R4G4_UNORM_PACK8);
    c(VK_FORMAT_R4G4B4A4_UNORM_PACK16);
    c(VK_FORMAT_B4G4R4A4_UNORM_PACK16);
    c(VK_FORMAT_R5G6B5_UNORM_PACK16);
    c(VK_FORMAT_B5G6R5_UNORM_PACK16);
    c(VK_FORMAT_R5G5B5A1_UNORM_PACK16);
    c(VK_FORMAT_B5G5R5A1_UNORM_PACK16);
    c(VK_FORMAT_A1R5G5B5_UNORM_PACK16);
    c(VK_FORMAT_R8_UNORM);
    c(VK_FORMAT_R8_SNORM);
    c(VK_FORMAT_R8_USCALED);
    c(VK_FORMAT_R8_SSCALED);
    c(VK_FORMAT_R8_UINT);
    c(VK_FORMAT_R8_SINT);
    c(VK_FORMAT_R8_SRGB);
    c(VK_FORMAT_R8G8_UNORM);
    c(VK_FORMAT_R8G8_SNORM);
    c(VK_FORMAT_R8G8_USCALED);
    c(VK_FORMAT_R8G8_SSCALED);
    c(VK_FORMAT_R8G8_UINT);
    c(VK_FORMAT_R8G8_SINT);
    c(VK_FORMAT_R8G8_SRGB);
    c(VK_FORMAT_R8G8B8_UNORM);
    c(VK_FORMAT_R8G8B8_SNORM);
    c(VK_FORMAT_R8G8B8_USCALED);
    c(VK_FORMAT_R8G8B8_SSCALED);
    c(VK_FORMAT_R8G8B8_UINT);
    c(VK_FORMAT_R8G8B8_SINT);
    c(VK_FORMAT_R8G8B8_SRGB);
    c(VK_FORMAT_B8G8R8_UNORM);
    c(VK_FORMAT_B8G8R8_SNORM);
    c(VK_FORMAT_B8G8R8_USCALED);
    c(VK_FORMAT_B8G8R8_SSCALED);
    c(VK_FORMAT_B8G8R8_UINT);
    c(VK_FORMAT_B8G8R8_SINT);
    c(VK_FORMAT_B8G8R8_SRGB);
    c(VK_FORMAT_R8G8B8A8_UNORM);
    c(VK_FORMAT_R8G8B8A8_SNORM);
    c(VK_FORMAT_R8G8B8A8_USCALED);
    c(VK_FORMAT_R8G8B8A8_SSCALED);
    c(VK_FORMAT_R8G8B8A8_UINT);
    c(VK_FORMAT_R8G8B8A8_SINT);
    c(VK_FORMAT_R8G8B8A8_SRGB);
    c(VK_FORMAT_B8G8R8A8_UNORM);
    c(VK_FORMAT_B8G8R8A8_SNORM);
    c(VK_FORMAT_B8G8R8A8_USCALED);
    c(VK_FORMAT_B8G8R8A8_SSCALED);
    c(VK_FORMAT_B8G8R8A8_UINT);
    c(VK_FORMAT_B8G8R8A8_SINT);
    c(VK_FORMAT_B8G8R8A8_SRGB);
    c(VK_FORMAT_A8B8G8R8_UNORM_PACK32);
    c(VK_FORMAT_A8B8G8R8_SNORM_PACK32);
    c(VK_FORMAT_A8B8G8R8_USCALED_PACK32);
    c(VK_FORMAT_A8B8G8R8_SSCALED_PACK32);
    c(VK_FORMAT_A8B8G8R8_UINT_PACK32);
    c(VK_FORMAT_A8B8G8R8_SINT_PACK32);
    c(VK_FORMAT_A8B8G8R8_SRGB_PACK32);
    c(VK_FORMAT_A2R10G10B10_UNORM_PACK32);
    c(VK_FORMAT_A2R10G10B10_SNORM_PACK32);
    c(VK_FORMAT_A2R10G10B10_USCALED_PACK32);
    c(VK_FORMAT_A2R10G10B10_SSCALED_PACK32);
    c(VK_FORMAT_A2R10G10B10_UINT_PACK32);
    c(VK_FORMAT_A2R10G10B10_SINT_PACK32);
    c(VK_FORMAT_A2B10G10R10_UNORM_PACK32);
    c(VK_FORMAT_A2B10G10R10_SNORM_PACK32);
    c(VK_FORMAT_A2B10G10R10_USCALED_PACK32);
    c(VK_FORMAT_A2B10G10R10_SSCALED_PACK32);
    c(VK_FORMAT_A2B10G10R10_UINT_PACK32);
    c(VK_FORMAT_A2B10G10R10_SINT_PACK32);
    c(VK_FORMAT_R16_UNORM);
    c(VK_FORMAT_R16_SNORM);
    c(VK_FORMAT_R16_USCALED);
    c(VK_FORMAT_R16_SSCALED);
    c(VK_FORMAT_R16_UINT);
    c(VK_FORMAT_R16_SINT);
    c(VK_FORMAT_R16_SFLOAT);
    c(VK_FORMAT_R16G16_UNORM);
    c(VK_FORMAT_R16G16_SNORM);
    c(VK_FORMAT_R16G16_USCALED);
    c(VK_FORMAT_R16G16_SSCALED);
    c(VK_FORMAT_R16G16_UINT);
    c(VK_FORMAT_R16G16_SINT);
    c(VK_FORMAT_R16G16_SFLOAT);
    c(VK_FORMAT_R16G16B16_UNORM);
    c(VK_FORMAT_R16G16B16_SNORM);
    c(VK_FORMAT_R16G16B16_USCALED);
    c(VK_FORMAT_R16G16B16_SSCALED);
    c(VK_FORMAT_R16G16B16_UINT);
    c(VK_FORMAT_R16G16B16_SINT);
    c(VK_FORMAT_R16G16B16_SFLOAT);
    c(VK_FORMAT_R16G16B16A16_UNORM);
    c(VK_FORMAT_R16G16B16A16_SNORM);
    c(VK_FORMAT_R16G16B16A16_USCALED);
    c(VK_FORMAT_R16G16B16A16_SSCALED);
    c(VK_FORMAT_R16G16B16A16_UINT);
    c(VK_FORMAT_R16G16B16A16_SINT);
    c(VK_FORMAT_R16G16B16A16_SFLOAT);
    c(VK_FORMAT_R32_UINT);
    c(VK_FORMAT_R32_SINT);
    c(VK_FORMAT_R32_SFLOAT);
    c(VK_FORMAT_R32G32_UINT);
    c(VK_FORMAT_R32G32_SINT);
    c(VK_FORMAT_R32G32_SFLOAT);
    c(VK_FORMAT_R32G32B32_UINT);
    c(VK_FORMAT_R32G32B32_SINT);
    c(VK_FORMAT_R32G32B32_SFLOAT);
    c(VK_FORMAT_R32G32B32A32_UINT);
    c(VK_FORMAT_R32G32B32A32_SINT);
    c(VK_FORMAT_R32G32B32A32_SFLOAT);
    c(VK_FORMAT_R64_UINT);
    c(VK_FORMAT_R64_SINT);
    c(VK_FORMAT_R64_SFLOAT);
    c(VK_FORMAT_R64G64_UINT);
    c(VK_FORMAT_R64G64_SINT);
    c(VK_FORMAT_R64G64_SFLOAT);
    c(VK_FORMAT_R64G64B64_UINT);
    c(VK_FORMAT_R64G64B64_SINT);
    c(VK_FORMAT_R64G64B64_SFLOAT);
    c(VK_FORMAT_R64G64B64A64_UINT);
    c(VK_FORMAT_R64G64B64A64_SINT);
    c(VK_FORMAT_R64G64B64A64_SFLOAT);
    c(VK_FORMAT_B10G11R11_UFLOAT_PACK32);
    c(VK_FORMAT_E5B9G9R9_UFLOAT_PACK32);
    c(VK_FORMAT_D16_UNORM);
    c(VK_FORMAT_X8_D24_UNORM_PACK32);
    c(VK_FORMAT_D32_SFLOAT);
    c(VK_FORMAT_S8_UINT);
    c(VK_FORMAT_D16_UNORM_S8_UINT);
    c(VK_FORMAT_D24_UNORM_S8_UINT);
    c(VK_FORMAT_D32_SFLOAT_S8_UINT);
    c(VK_FORMAT_BC1_RGB_UNORM_BLOCK);
    c(VK_FORMAT_BC1_RGB_SRGB_BLOCK);
    c(VK_FORMAT_BC1_RGBA_UNORM_BLOCK);
    c(VK_FORMAT_BC1_RGBA_SRGB_BLOCK);
    c(VK_FORMAT_BC2_UNORM_BLOCK);
    c(VK_FORMAT_BC2_SRGB_BLOCK);
    c(VK_FORMAT_BC3_UNORM_BLOCK);
    c(VK_FORMAT_BC3_SRGB_BLOCK);
    c(VK_FORMAT_BC4_UNORM_BLOCK);
    c(VK_FORMAT_BC4_SNORM_BLOCK);
    c(VK_FORMAT_BC5_UNORM_BLOCK);
    c(VK_FORMAT_BC5_SNORM_BLOCK);
    c(VK_FORMAT_BC6H_UFLOAT_BLOCK);
    c(VK_FORMAT_BC6H_SFLOAT_BLOCK);
    c(VK_FORMAT_BC7_UNORM_BLOCK);
    c(VK_FORMAT_BC7_SRGB_BLOCK);
    c(VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK);
    c(VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK);
    c(VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK);
    c(VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK);
    c(VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK);
    c(VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK);
    c(VK_FORMAT_EAC_R11_UNORM_BLOCK);
    c(VK_FORMAT_EAC_R11_SNORM_BLOCK);
    c(VK_FORMAT_EAC_R11G11_UNORM_BLOCK);
    c(VK_FORMAT_EAC_R11G11_SNORM_BLOCK);
    c(VK_FORMAT_ASTC_4x4_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_4x4_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_5x4_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_5x4_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_5x5_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_5x5_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_6x5_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_6x5_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_6x6_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_6x6_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_8x5_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_8x5_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_8x6_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_8x6_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_8x8_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_8x8_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_10x5_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_10x5_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_10x6_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_10x6_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_10x8_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_10x8_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_10x10_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_10x10_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_12x10_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_12x10_SRGB_BLOCK);
    c(VK_FORMAT_ASTC_12x12_UNORM_BLOCK);
    c(VK_FORMAT_ASTC_12x12_SRGB_BLOCK);
    default: return "Invalid VkFormat value";
  }
}

char const *vkColorSpaceKHRString(VkColorSpaceKHR color_space) {
  switch(color_space) {
    c(VK_COLOR_SPACE_SRGB_NONLINEAR_KHR);
    default: return "Invalid VkColorSpaceKHR value";
  }
}

char const *vkPresentModeKHRString(VkPresentModeKHR mode) {
  switch(mode) {
    c(VK_PRESENT_MODE_IMMEDIATE_KHR);
    c(VK_PRESENT_MODE_MAILBOX_KHR);
    c(VK_PRESENT_MODE_FIFO_KHR);
    c(VK_PRESENT_MODE_FIFO_RELAXED_KHR);
    default: return "Invalid VkPresentModeKHR value";
  }
}

char const *vkSurfaceTransformFlagBitsKHRString(VkSurfaceTransformFlagBitsKHR bit) {
  switch(bit) {
    c(VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR);
    c(VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR);
    c(VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR);
    c(VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR);
    c(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR);
    c(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR);
    c(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR);
    c(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR);
    c(VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR);
    default: return "Invalid VkSurfaceTransformFlagBitsKHR value";
  }
}

char const * vkCompositeAlphaFlagBitsKHRString(VkCompositeAlphaFlagBitsKHR bit) {
  switch(bit) {
    c(VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR);
    c(VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR);
    c(VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR);
    c(VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR);
    default: return "Invalid VkCompositeAlphaFlagBitsKHR value";
  }
}

char const *VkImageUsageFlagBitsString(VkImageUsageFlagBits bit) {
  switch(bit) {
    c(VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
    c(VK_IMAGE_USAGE_TRANSFER_DST_BIT);
    c(VK_IMAGE_USAGE_SAMPLED_BIT);
    c(VK_IMAGE_USAGE_STORAGE_BIT);
    c(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);
    c(VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);
    c(VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT);
    c(VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT);
    default: return "Invalid VkImageUsageFlagBits value";
  }
}

char const * vkFormatFeatureFlagBitsString(VkFormatFeatureFlagBits bit) {
  switch(bit) {
    c(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT);
    c(VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT);
    c(VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT);
    c(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT);
    c(VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT);
    c(VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT);
    c(VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT);
    c(VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT);
    c(VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT);
    c(VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
    c(VK_FORMAT_FEATURE_BLIT_SRC_BIT);
    c(VK_FORMAT_FEATURE_BLIT_DST_BIT);
    c(VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT);
    // c(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT);
    // c(VK_FORMAT_FEATURE_TRANSFER_DST_BIT);
    // c(VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT);
    // c(VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT);
    // c(VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT);
    // c(VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_BIT);
    // c(VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT);
    // c(VK_FORMAT_FEATURE_DISJOINT_BIT);
    // c(VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT);
    /// c(VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_IMG);
    // c(VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT_EXT);
    default: return "Invalid VkFormatFeatureFlagBits value";
  }
}
#undef c

#define vk(cmd) \
do { \
  VkResult result = vk ## cmd ; \
  if (VK_SUCCESS != result) { \
    std::cerr << __FILE__ << " : " << __LINE__  \
        << "  \"" << #cmd << "\" " << vkResultString(result) << std::endl; \
    return -1; \
  } \
} while (0)


#define re(cmd) \
do { \
  int result = cmd ; \
  if (0 != result) { \
    std::cerr << __FILE__ << " : " << __LINE__  \
        << "  \"" << #cmd << "\" " << result << std::endl; \
    return result; \
  } \
} while(0)

#define tr(cmd) \
do { \
  std::cerr << __FILE__ << " : " << __LINE__  << "  \"" << #cmd << "\" "  << std::endl; \
  re(cmd); \
  std::cerr << __FILE__ << " : " << __LINE__  << " OK" << std::endl; \
} while(0)

template<typename FlagsT, typename BitsT>
std::string FlagsString(
    BitsT const bits[], uint32_t nbits, FlagsT flags,
    char const* (*string_fn)(BitsT)) {
  std::string flags_string("");
  for (uint32_t b = 0; b < nbits; ++b) {
    if (!(flags & bits[b])) {
      continue;
    }
    if (flags_string.size() > 0) {
      flags_string += ",";
    }
    flags_string += string_fn(bits[b]);
  }
  return flags_string;
}
    

std::string vkMemoryPropertyFlagsString(VkMemoryPropertyFlags flags) {
  VkMemoryPropertyFlagBits bits[] = {
      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
      VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
      VK_MEMORY_PROPERTY_HOST_CACHED_BIT,
      VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT,
      // VK_MEMORY_PROPERTY_PROTECTED_BIT,
  };
  uint32_t const nbits = sizeof(bits) / sizeof(bits[0]);
  return FlagsString(bits, nbits, flags, vkMemoryPropertyFlagBitsString);
}

std::string vkMemoryHeapFlagsString(VkMemoryHeapFlags flags) {
  VkMemoryHeapFlagBits bits[] = {
    VK_MEMORY_HEAP_DEVICE_LOCAL_BIT,
    // VK_MEMORY_HEAP_MULTI_INSTANCE_BIT
  };
  uint32_t const nbits = sizeof(bits) / sizeof(bits[0]);
  return FlagsString(bits, nbits, flags, vkMemoryHeapFlagBitsString);
}

std::string vkQueueFlagsString(VkQueueFlags flags) {
  VkQueueFlagBits bits[] = {
    VK_QUEUE_GRAPHICS_BIT,
    VK_QUEUE_COMPUTE_BIT,
    VK_QUEUE_TRANSFER_BIT,
    VK_QUEUE_SPARSE_BINDING_BIT,
    // VK_QUEUE_PROTECTED_BIT,
  };
  uint32_t const nbits = sizeof(bits) / sizeof(bits[0]);
  return FlagsString(bits, nbits, flags, vkQueueFlagBitsString);
}

std::string vkSurfaceTransformFlagsKHRString(VkSurfaceTransformFlagsKHR flags) {
  VkSurfaceTransformFlagBitsKHR bits[] = {
    VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
    VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR,
    VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR,
    VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR,
    VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR,
    VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR,
    VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR,
    VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR,
    VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR
  };
  uint32_t const nbits = sizeof(bits) / sizeof(bits[0]);
  return FlagsString(bits, nbits, flags, vkSurfaceTransformFlagBitsKHRString);
}

std::string VkCompositeAlphaFlagsKHRString(VkCompositeAlphaFlagsKHR flags) {
  VkCompositeAlphaFlagBitsKHR bits[] = {
    VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
    VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
    VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
    VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR
  };
  uint32_t const nbits = sizeof(bits) / sizeof(bits[0]);
  return FlagsString(bits, nbits, flags, vkCompositeAlphaFlagBitsKHRString);
}

std::string VkImageUsageFlagsString(VkImageUsageFlags flags) {
  VkImageUsageFlagBits bits[] = {
    VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
    VK_IMAGE_USAGE_TRANSFER_DST_BIT,
    VK_IMAGE_USAGE_SAMPLED_BIT,
    VK_IMAGE_USAGE_STORAGE_BIT,
    VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
    VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
    VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
  };
  uint32_t const nbits = sizeof(bits) / sizeof(bits[0]);
  return FlagsString(bits, nbits, flags, VkImageUsageFlagBitsString);
}

std::string vkFormatFeatureFlagsString(VkFormatFeatureFlags flags) {
  VkFormatFeatureFlagBits bits[] = {
    VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT,
    VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT,
    VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT,
    VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT,
    VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT,
    VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT,
    VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT,
    VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT,
    VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT,
    VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,
    VK_FORMAT_FEATURE_BLIT_SRC_BIT,
    VK_FORMAT_FEATURE_BLIT_DST_BIT,
    VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT,
    // VK_FORMAT_FEATURE_TRANSFER_SRC_BIT,
    // VK_FORMAT_FEATURE_TRANSFER_DST_BIT,
    // VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT,
    // VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT,
    // VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT,
    // VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_BIT,
    // VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT,
    // VK_FORMAT_FEATURE_DISJOINT_BIT,
    // VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT,
    // VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_IMG,
    // VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT_EXT,
  };
  uint32_t const nbits = sizeof(bits) / sizeof(bits[0]);
  return FlagsString(bits, nbits, flags, vkFormatFeatureFlagBitsString);
}

std::string vkPhysicalDeviceFeaturesString(
    VkPhysicalDeviceFeatures const& device_features) {
  std::string features_string("");
  uint32_t num_features = 0;
#define f(feature) \
  if (device_features.feature) { \
    if (num_features++ > 0) \
      features_string += ","; \
    features_string += #feature; \
  }

  f(robustBufferAccess);
  f(fullDrawIndexUint32);
  f(imageCubeArray);
  f(independentBlend);
  f(geometryShader);
  f(tessellationShader);
  f(sampleRateShading);
  f(dualSrcBlend);
  f(logicOp);
  f(multiDrawIndirect);
  f(drawIndirectFirstInstance);
  f(depthClamp);
  f(depthBiasClamp);
  f(fillModeNonSolid);
  f(depthBounds);
  f(wideLines);
  f(largePoints);
  f(alphaToOne);
  f(multiViewport);
  f(samplerAnisotropy);
  f(textureCompressionETC2);
  f(textureCompressionASTC_LDR);
  f(textureCompressionBC);
  f(occlusionQueryPrecise);
  f(pipelineStatisticsQuery);
  f(vertexPipelineStoresAndAtomics);
  f(fragmentStoresAndAtomics);
  f(shaderTessellationAndGeometryPointSize);
  f(shaderImageGatherExtended);
  f(shaderStorageImageExtendedFormats);
  f(shaderStorageImageMultisample);
  f(shaderStorageImageReadWithoutFormat);
  f(shaderStorageImageWriteWithoutFormat);
  f(shaderUniformBufferArrayDynamicIndexing);
  f(shaderSampledImageArrayDynamicIndexing);
  f(shaderStorageBufferArrayDynamicIndexing);
  f(shaderStorageImageArrayDynamicIndexing);
  f(shaderClipDistance);
  f(shaderCullDistance);
  f(shaderFloat64);
  f(shaderInt64);
  f(shaderInt16);
  f(shaderResourceResidency);
  f(shaderResourceMinLod);
  f(sparseBinding);
  f(sparseResidencyBuffer);
  f(sparseResidencyImage2D);
  f(sparseResidencyImage3D);
  f(sparseResidency2Samples);
  f(sparseResidency4Samples);
  f(sparseResidency8Samples);
  f(sparseResidency16Samples);
  f(sparseResidencyAliased);
  f(variableMultisampleRate);
  f(inheritedQueries);
#undef f
  return features_string;
}

int
InitVulkanInstance
(
  VkInstance *instance
)
{
  int major, minor, rev;
  glfwGetVersion(&major, &minor, &rev);
  std::cerr << "GLFW Version: " << major << " " << minor << " " << rev << std::endl;

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

  uint32_t glfw_extensions_count;
  const char **glfw_extensions = glfwGetRequiredInstanceExtensions(
      &glfw_extensions_count);
  std::cerr << "RequiredInstanceExtensions: " << std::endl;
  for (uint32_t k = 0 ; k < glfw_extensions_count; ++k) {
    std::cerr << "    " << glfw_extensions[k] << std::endl;
  }

  uint32_t property_count;
  vk(EnumerateInstanceLayerProperties(&property_count, NULL));
  VkLayerProperties *layer_properties = new VkLayerProperties[property_count];
  vk(EnumerateInstanceLayerProperties(&property_count, layer_properties));
  std::cerr << "Instance Layer Properties: " << std::endl;
  for (uint32_t k = 0; k < property_count; ++k) {
    uint32_t layer_property_count;
    vk(EnumerateInstanceExtensionProperties(
        layer_properties[k].layerName, &layer_property_count,
         NULL)); 
    std::unique_ptr<VkExtensionProperties[]> extension_properties(
        new VkExtensionProperties[layer_property_count]);
    vk(EnumerateInstanceExtensionProperties(
        layer_properties[k].layerName, &layer_property_count,
        extension_properties.get()));
    std::cerr << "    " << layer_properties[k].layerName << " : "
        << layer_properties[k].description << std::endl;
    for (uint32_t n = 0; n < layer_property_count; ++n) {
      std::cerr << "        " <<  extension_properties.get()[n].extensionName
           << std::endl;
    }
  }

  VkApplicationInfo app;
  app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app.pNext = NULL;
  app.pApplicationName = "waveycrocket";
  app.applicationVersion = 1;
  app.pEngineName = "waveycrocket";
  app.engineVersion = 1;
  app.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo create;
  create.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create.pNext = NULL;
  create.flags = 0;
  create.pApplicationInfo = &app;

  char const *enabled_layers[2]= {
    "VK_LAYER_LUNARG_standard_validation",
    "VK_LAYER_LUNARG_parameter_validation"
  };
  create.enabledLayerCount = 1;
  create.ppEnabledLayerNames = enabled_layers;

  char const *enabled_extensions[glfw_extensions_count + 1];
  for (uint32_t k = 0; k < glfw_extensions_count; ++k) {
    enabled_extensions[k] = glfw_extensions[k];
  }
  enabled_extensions[glfw_extensions_count] = "VK_EXT_debug_report";

  create.enabledExtensionCount =  glfw_extensions_count + 1;
  create.ppEnabledExtensionNames = enabled_extensions;

  PFN_vkCreateInstance vk_create_instance = (
      (PFN_vkCreateInstance) glfwGetInstanceProcAddress(
          NULL, "vkCreateInstance"));

  vk(_create_instance(&create, NULL, instance));

  return 0;
}

VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(
    VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType,
    uint64_t object, size_t location, int32_t messageCode,
    const char *pLayerPrefix, const char *pMessage, void *pUserData)
{
  std::cerr
      << "DebugReportCallback [" 
      << ((flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
          ? "ERRR" :
          (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
          ? "WARN" :
          (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
          ? "PERF" : 
          (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
          ? "INFO" :
          (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT)
          ? "DEBG" : "????") << "] "
      << messageCode << " : " << pMessage << std::endl;
  return VK_FALSE;
}

int
CreateDebugReportCallback(
    VkInstance instance,
    VkDebugReportCallbackEXT *callback)
{
  VkDebugReportCallbackCreateInfoEXT drc;
  drc.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  drc.pNext = NULL;
  drc.flags = (
    VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
    VK_DEBUG_REPORT_WARNING_BIT_EXT |
    VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
    VK_DEBUG_REPORT_ERROR_BIT_EXT |
    VK_DEBUG_REPORT_DEBUG_BIT_EXT);
  drc.pfnCallback = DebugReportCallback;
  drc.pUserData = NULL;

  PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT =
      reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(
          vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));

  vk(CreateDebugReportCallbackEXT(instance,  &drc, NULL, callback));
  return 0;
}

int
InitVulkanDevice
(
    VkInstance instance,
    VkPhysicalDevice *physical_device,
    uint32_t *queue_family,
    VkPhysicalDeviceFeatures *device_features
)
{
  uint32_t device_count;
  vk(EnumeratePhysicalDevices(instance, &device_count, NULL));
  std::unique_ptr<VkPhysicalDevice[]> physical_devices(
      new VkPhysicalDevice[device_count]);
  vk(EnumeratePhysicalDevices(instance, &device_count, physical_devices.get()));

  for (uint32_t d = 0; d < device_count; ++d) {
    VkPhysicalDeviceProperties device_props;
    vkGetPhysicalDeviceProperties(physical_devices[d], &device_props);

    VkPhysicalDeviceMemoryProperties memory_props;
    vkGetPhysicalDeviceMemoryProperties(physical_devices[d], &memory_props);

    VkPhysicalDeviceFeatures device_features_d;
    vkGetPhysicalDeviceFeatures(physical_devices[d], &device_features_d);

 
    std::cerr << "Device #" <<  d << std::endl
        << "  apiVersion = " << device_props.apiVersion << std::endl
        << "  driverVersion = " << device_props.driverVersion << std::endl
        << "  vendorID = " << device_props.vendorID << std::endl
        << "  deviceID = " << device_props.deviceID << std::endl
        << "  deviceType = "
            << vkPhysicalDeviceTypeString(device_props.deviceType)
            << std::endl
        << "  deviceName = " << device_props.deviceName << std::endl
        << "  memoryTypeCount = " << memory_props.memoryTypeCount << std::endl
        << "  Features: " 
            << vkPhysicalDeviceFeaturesString(device_features_d) << std::endl;

    for (uint32_t m = 0; m < memory_props.memoryTypeCount; ++m) {
      std::cerr << "  Memory #" << m << std::endl
          << "    propertyFlags = "
               << vkMemoryPropertyFlagsString(
                      memory_props.memoryTypes[m].propertyFlags) << std::endl
          << "    heapIndex = "
               << memory_props.memoryTypes[m].heapIndex << std::endl;
    
    }
    for (uint32_t m = 0; m < memory_props.memoryHeapCount; ++m) {
      std::cerr << "  Heap #" << m << std::endl
          << "    size = " << memory_props.memoryHeaps[m].size << std::endl
          << "    flags = "
               << vkMemoryHeapFlagsString(
                      memory_props.memoryHeaps[m].flags) << std::endl;
    }

    uint32_t queue_family_count;
    vkGetPhysicalDeviceQueueFamilyProperties(
        physical_devices[d], &queue_family_count, NULL);
    std::unique_ptr<VkQueueFamilyProperties[]> queue_family_props(
        new VkQueueFamilyProperties[queue_family_count]);
    vkGetPhysicalDeviceQueueFamilyProperties(
        physical_devices[d], &queue_family_count, queue_family_props.get());

    for (uint32_t q = 0; q < queue_family_count; ++q) {
      std::cerr << "  Queue # " << q << std::endl
          << "    queueFlags = " 
              << vkQueueFlagsString(
                  queue_family_props[q].queueFlags) << std::endl
          << "    queueCount = " << queue_family_props[q].queueCount << std::endl
          << "    timestampValidBits = "
               << queue_family_props[q].timestampValidBits << std::endl
          << "    minImageTransferGranularity = " 
               << queue_family_props[q].minImageTransferGranularity.width
               << " x "
               << queue_family_props[q].minImageTransferGranularity.height
               << std::endl;
      std::cerr << "    glfw presentation: ";
      if (GLFW_TRUE == glfwGetPhysicalDevicePresentationSupport(
              instance, physical_devices[d], q)) {
        std::cerr  << " yes" << std::endl;

        *physical_device = physical_devices[d];
        *queue_family = q;
        *device_features = device_features_d;
    
      } else {
        std::cerr  << " no" << std::endl;
      }
    }
  }
  return 0;
}

int
SelectMemoryTypeWithProperties(
  VkPhysicalDevice physical_device,
  VkMemoryRequirements mem_reqs,
  VkMemoryPropertyFlags properties,
  uint32_t *memory_type
)
{
  VkPhysicalDeviceMemoryProperties mem_props;
  vkGetPhysicalDeviceMemoryProperties(physical_device, &mem_props);
  for (uint32_t m = 0; m < mem_props.memoryTypeCount; ++m) {
    if ((mem_reqs.memoryTypeBits & (1 << m)) &&
        (properties == (mem_props.memoryTypes[m].propertyFlags & properties))) {
      // return the first suitable memory type. 
      *memory_type = m;
      return 0;
    }
  }
  return -1;
}

int
CreateWindowSurface(
    VkInstance instance,
    VkPhysicalDevice physical_device,
    VkFormat surface_format,
    VkExtent2D surface_extent,
    GLFWwindow **window,
    VkSurfaceKHR *surface    
)
{
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  *window = glfwCreateWindow(
      surface_extent.width, surface_extent.height, "Wavey Crocket", NULL, NULL);

  VkResult r = glfwCreateWindowSurface(instance, *window, NULL, surface);
  if (VK_SUCCESS != r) {
    std::cerr << __FILE__ << " : " << __LINE__  \
        << "  \"glfwCreateWindowSurface(instance, *window, NULL, surface)\" "
        << vkResultString(r) << std::endl; \
    return -1;
  }

  uint32_t format_count;
  vk(GetPhysicalDeviceSurfaceFormatsKHR(
      physical_device, *surface, &format_count, NULL));
  std::unique_ptr<VkSurfaceFormatKHR[]> surface_formats(
      new VkSurfaceFormatKHR[format_count]);
  vk(GetPhysicalDeviceSurfaceFormatsKHR(
      physical_device, *surface, &format_count, surface_formats.get()));
  
  bool found_format = false;

  // VkFormat surface_format = VK_FORMAT_R8G8B8A8_UNORM;

  for (uint32_t f = 0; f < format_count; ++f) {
    std::cerr  << "Surface Format #" << f << ": "
        << vkFormatString(surface_formats[f].format) << std::endl;
    if (surface_format == surface_formats[f].format) {
      found_format = true;
    }
  }
  std::cerr << "Found format: " << (found_format ? "yes" : "no") << std::endl;
  return (found_format ? 0 : -1);
}

int
CreateDevice
(
  VkPhysicalDevice physical_device,
  VkPhysicalDeviceFeatures device_features,
  uint32_t queue_family,
  VkDevice *device
)
{
  float queue_priority = 1.0f;

  VkDeviceQueueCreateInfo qcr;
  qcr.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  qcr.pNext = NULL;  // VkDeviceQueueGlobalPriorityCreateInfoEXT
  qcr.flags = 0;
  qcr.queueFamilyIndex = queue_family;
  qcr.queueCount = 1;
  qcr.pQueuePriorities = &queue_priority;

  char const *swapchain_extension = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

  VkDeviceCreateInfo dcr;
  dcr.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  dcr.pNext = NULL;
  dcr.flags = 0;  // VkDeviceCreateFlags is reserved for future use.
  dcr.queueCreateInfoCount = 1;
  dcr.pQueueCreateInfos = &qcr;
  dcr.enabledLayerCount =  0;
  dcr.ppEnabledLayerNames = NULL;
  dcr.enabledExtensionCount = 1;
  dcr.ppEnabledExtensionNames =  &swapchain_extension;
  dcr.pEnabledFeatures = &device_features;

  vk(CreateDevice(physical_device, &dcr, NULL, device));

  return 0;
}

int
CreateCommandPoolAndQueue
(
  VkDevice device,
  uint32_t queue_family,
  VkCommandPool *command_pool,
  VkQueue *queue
)
{
  VkCommandPoolCreateInfo pcr;
  pcr.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pcr.pNext = NULL;
  pcr.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  // VK_COMMAND_POOL_CREATE_TRANSIENT_BIT = 0x00000001,
  // VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT = 0x00000002,
  // VK_COMMAND_POOL_CREATE_PROTECTED_BIT 
  pcr.queueFamilyIndex = queue_family;

  vk(CreateCommandPool(device, &pcr, NULL, command_pool));

  uint32_t queue_index = 0;  // queueCreateInfoCount == 1
  vkGetDeviceQueue(device, queue_family, queue_index, queue);

  return 0;
}

int
CreateCommandBuffer(
  VkDevice device,
  VkCommandPool command_pool,
  VkCommandBuffer *command_buffer
)
{
  VkCommandBufferAllocateInfo cba;
  cba.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cba.pNext = NULL;
  cba.commandPool = command_pool;
  cba.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cba.commandBufferCount = 1;

  vk(AllocateCommandBuffers(device, &cba, command_buffer));

  return 0;
}

int
CreateSemaphore
(
    VkDevice device,
    VkSemaphore *semaphore
)
{
  VkSemaphoreCreateInfo scr;
  scr.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  scr.pNext = NULL;
  scr.flags = 0;
  vk(CreateSemaphore(device, &scr, NULL, semaphore));
  return 0;
}

int
CreateSwapchain(
  VkPhysicalDevice physical_device,
  VkDevice device,
  uint32_t queue_family,
  VkSurfaceKHR surface,
  VkFormat surface_format,
  uint32_t *image_count,
  VkSwapchainKHR *swapchain
)
{
  VkSurfaceCapabilitiesKHR surface_caps;
  vk(GetPhysicalDeviceSurfaceCapabilitiesKHR(
          physical_device, surface, &surface_caps));

  std::cerr << "Surface capabilities:" << std::endl
      << "  minImageCount = " << surface_caps.minImageCount << std::endl
      << "  maxImageCount = " << surface_caps.maxImageCount << std::endl
      << "  currentExtent = "
          << surface_caps.currentExtent.width << " x "
          << surface_caps.currentExtent.height << std::endl
      << "  minImageExtent = "
          << surface_caps.minImageExtent.width << " x "
          << surface_caps.minImageExtent.height << std::endl
      << "  maxImageExtent = "
          << surface_caps.maxImageExtent.width << " x "
          << surface_caps.maxImageExtent.height << std::endl
      << "  supportedTransforms = "
          << vkSurfaceTransformFlagsKHRString(
              surface_caps.supportedTransforms) << std::endl
      << "  currentTransform = "
          << vkSurfaceTransformFlagBitsKHRString( 
              surface_caps.currentTransform) << std::endl
      << "  supportedCompositeAlpha = " 
          << VkCompositeAlphaFlagsKHRString(
              surface_caps.supportedCompositeAlpha) << std::endl
      << "  supportedUsageFlags = "
          << VkImageUsageFlagsString(
              surface_caps.supportedUsageFlags) << std::endl;

  VkExtent2D extent;
  if ((surface_caps.currentExtent.width == 0xFFFFFFFF &&
       surface_caps.currentExtent.height == 0xFFFFFFFF)) {
    extent.width = 1920;
    extent.height = 1080;
  } else {
    extent = surface_caps.currentExtent;
  }

  uint32_t modes_count;
  vk(GetPhysicalDeviceSurfacePresentModesKHR(
      physical_device, surface, &modes_count, NULL));
  std::unique_ptr<VkPresentModeKHR[]> modes(
    new VkPresentModeKHR[modes_count]);
  vk(GetPhysicalDeviceSurfacePresentModesKHR(
      physical_device, surface, &modes_count, modes.get()));
  std::cerr << "Presentation modes:" << std::endl;
  for (uint32_t m = 0; m < modes_count; ++m) {
    std::cerr << "  " << vkPresentModeKHRString(modes[m]) << std::endl;
  }

  VkBool32 supported;
  vk(GetPhysicalDeviceSurfaceSupportKHR(
      physical_device, queue_family, surface, &supported));
  std::cerr << "Physical Device supports surface: " << (supported ? "yes" : "no") << std::endl;
  if (supported != VK_TRUE) {
    return -1;
  }

  VkSwapchainCreateInfoKHR scr;
  scr.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  scr.pNext = NULL;
  scr.flags = 0;
  scr.surface = surface;
  scr.minImageCount = *image_count;
  scr.imageFormat = surface_format;
  scr.imageExtent = extent;
  scr.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR; // only one supported ?
  scr.imageArrayLayers = 1 ;  // non-stereoscopic
  scr.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  scr.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;  // VK_SHARING_MODE_CONCURRENT
  scr.queueFamilyIndexCount = 0; // nonzero only if CONCURRENT
  scr.pQueueFamilyIndices = NULL;
  scr.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  scr.compositeAlpha =  VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  scr.presentMode = VK_PRESENT_MODE_FIFO_KHR;
  scr.clipped = VK_TRUE;
  scr.oldSwapchain = VK_NULL_HANDLE;


  vk(CreateSwapchainKHR(device, &scr, NULL, swapchain));
  vk(GetSwapchainImagesKHR(device, *swapchain, image_count, NULL));
  return 0;
}

int
CreateAndAllocateBuffer(
    VkPhysicalDevice physical_device,
    VkDevice device,
    uint32_t buffer_size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkBuffer *buffer,
    VkDeviceMemory *memory) {
  VkBufferCreateInfo bcr;
  bcr.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bcr.pNext = NULL;
  bcr.flags = 0;
  bcr.size = buffer_size;
  bcr.usage = usage;
  bcr.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  bcr.queueFamilyIndexCount = 0;
  bcr.pQueueFamilyIndices = NULL; // EXCLUSIVE

  vk(CreateBuffer(device, &bcr, NULL, buffer));

  VkMemoryRequirements mem_reqs;
  vkGetBufferMemoryRequirements(device, *buffer, &mem_reqs);

  uint32_t memory_type;
  SelectMemoryTypeWithProperties(
      physical_device, mem_reqs, properties, &memory_type);

  VkMemoryAllocateInfo mal;
  mal.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  mal.pNext = NULL;
  mal.allocationSize = mem_reqs.size;
  mal.memoryTypeIndex = memory_type;

  vk(AllocateMemory(device, &mal, NULL, memory));
  vk(BindBufferMemory(device, *buffer, *memory, 0));
  return 0;
}

int
CreateVertexBuffer(
  VkPhysicalDevice physical_device,
  VkDevice device,
  uint32_t buffer_size,
  VkBuffer *vertex_buffer,
  VkDeviceMemory *vertex_memory
)
{
  re(CreateAndAllocateBuffer(
      physical_device, device, buffer_size,
      VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
       VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
      vertex_buffer, vertex_memory));
  return 0;
}

int
CreateUniformBuffer_float4x4(
  VkPhysicalDevice physical_device,
  VkDevice device,
  VkBuffer *uniform_buffer,
  VkDeviceMemory *uniform_memory)
{
  uint32_t buffer_size =  4 * 4 * sizeof(float);
  re(CreateAndAllocateBuffer(
      physical_device, device, buffer_size,
      VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
      (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
       VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
      uniform_buffer, uniform_memory));
  return 0;
}

template <typename T>
int
MapAndInitializeMemory(
    VkDevice device,
    VkDeviceMemory memory,
    T const *data,
    uint32_t size)
{
  void *mapped_memory;
  vk(MapMemory(device, memory, 0, size, 0, &mapped_memory));
  memcpy(mapped_memory, reinterpret_cast<void const*>(data), size);
  vkUnmapMemory(device, memory);
  return 0;
}

int
CreateAndAllocateImage2D
(
  VkPhysicalDevice physical_device,
  VkDevice device,
  VkExtent2D extent,
  VkFormat format,
  VkImageTiling tiling,
  VkImageUsageFlags usage,
  VkMemoryPropertyFlags properties,
  VkImage *image, VkDeviceMemory *memory
)
{
  VkImageCreateInfo icr;
  icr.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  icr.pNext = NULL;
  // VkDedicatedAllocationImageCreateInfoNV, VkExternalFormatANDROID,
  // VkExternalMemoryImageCreateInfo, VkExternalMemoryImageCreateInfoNV, 
  // VkImageFormatListCreateInfoKHR, or VkImageSwapchainCreateInfoKHR
  icr.flags = 0;  // VkImageCreateFlagBits
  icr.imageType = VK_IMAGE_TYPE_2D;
  icr.format = format; // VK_FORMAT_R8G8B8A8_UNORM;
  icr.extent.width = extent.width;
  icr.extent.height = extent.height;
  icr.extent.depth = 1;
  icr.mipLevels = 1;
  icr.arrayLayers = 1;
  icr.samples = VK_SAMPLE_COUNT_1_BIT;
  icr.tiling = tiling;
  icr.usage = usage;
  icr.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  icr.queueFamilyIndexCount = 0;
  icr.pQueueFamilyIndices = NULL;  // unused becaue EXCLUSIVE
  icr.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;

  vk(CreateImage(device, &icr, NULL, image));

  VkMemoryRequirements mem_reqs;
  vkGetImageMemoryRequirements(device, *image, &mem_reqs);

  uint32_t memory_type;
  re(SelectMemoryTypeWithProperties(
      physical_device, mem_reqs, properties, &memory_type));

  VkMemoryAllocateInfo mal;
  mal.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  mal.pNext = NULL;
  mal.allocationSize = mem_reqs.size;
  mal.memoryTypeIndex = memory_type;

  vk(AllocateMemory(device, &mal, NULL, memory)); 
  vk(BindImageMemory(device, *image, *memory, 0));
  return 0;
}

int
CreateImage2DView
(
  VkDevice device,
  VkImage image,
  VkFormat format,
  VkImageAspectFlags aspect_mask,
  VkImageView *image_view
)
{
  VkImageViewCreateInfo ivc;
  ivc.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  ivc.pNext = NULL; // VkImageViewUsageCreateInfo, VkImageUsageFlagBits
  ivc.flags = 0;
  ivc.image = image,
  ivc.viewType = VK_IMAGE_VIEW_TYPE_2D; // VkImageViewType
  ivc.format = format;
  ivc.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
  ivc.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
  ivc.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
  ivc.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
  // VK_IMAGE_ASPECT_COLOR_BIT,  DEPTH, STENCIL
  ivc.subresourceRange.aspectMask = aspect_mask;
  ivc.subresourceRange.baseMipLevel = 0;
  ivc.subresourceRange.levelCount = 1;
  ivc.subresourceRange.baseArrayLayer = 0;
  ivc.subresourceRange.layerCount = 1;

  vk(CreateImageView(device, &ivc, NULL, image_view));
  return 0;
}

int
CreateDepthBuffer
(
  VkPhysicalDevice physical_device,
  VkDevice device,
  VkExtent2D extent,
  VkImage *depth_image,
  VkDeviceMemory *depth_memory,
  VkImageView *depth_image_view
)
{
  VkFormatProperties format_props;
  vkGetPhysicalDeviceFormatProperties(
      physical_device, VK_FORMAT_D16_UNORM, &format_props);
  
  std::cerr << "Format properties for VK_FORMAT_D16_UNORM" << std::endl
    << "  linearTilingFeatures = "
         << vkFormatFeatureFlagsString(
            format_props.linearTilingFeatures) << std::endl
    << "  optimralTilingFeatures = "
         << vkFormatFeatureFlagsString(
            format_props.optimalTilingFeatures) << std::endl
    << "  bufferFeatures = "
         << vkFormatFeatureFlagsString(
            format_props.bufferFeatures) << std::endl;
  if (!(format_props.optimalTilingFeatures &
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)) {
    return -1;
  }

  re(CreateAndAllocateImage2D(
      physical_device, device, extent, VK_FORMAT_D16_UNORM,
      VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
      0, // No flags
      depth_image, depth_memory));

  re(CreateImage2DView(
      device, *depth_image, VK_FORMAT_D16_UNORM, VK_IMAGE_ASPECT_DEPTH_BIT,
      depth_image_view));
  return 0;
}

 
int
CreateSwapchainImageViews
(
  VkDevice device,
  VkSwapchainKHR swapchain,
  VkFormat surface_format,
  uint32_t image_count,
  std::unique_ptr<VkImage[]> *swapchain_images,
  std::unique_ptr<VkImageView[]> *swapchain_image_views
)
{
  swapchain_images->reset(new VkImage[image_count]);
  vk(GetSwapchainImagesKHR(device, swapchain, &image_count, swapchain_images->get()));

  swapchain_image_views->reset(new VkImageView[image_count]);
  for (uint32_t i = 0; i < image_count; ++i) {
    re(CreateImage2DView(
        device, (*swapchain_images)[i], surface_format, VK_IMAGE_ASPECT_COLOR_BIT,
        &((*swapchain_image_views)[i])));
  }
  return 0;
}

int
CreateRenderPass(
  VkDevice device,
  VkFormat surface_format,
  VkRenderPass *render_pass)
{
  VkAttachmentDescription attachments[2];

  // Pixel buffer
  attachments[0].flags = 0;
  attachments[0].format = surface_format;
  attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[0].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  attachments[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkAttachmentReference color_reference;
  color_reference.attachment = 0;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  // Depth buffer
  attachments[1].flags = 0;
  attachments[1].format = VK_FORMAT_D16_UNORM;
  attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
  attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[1].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference depth_reference;
  depth_reference.attachment = 1;
  depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass;
  subpass.flags = 0;
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.inputAttachmentCount = 0;
  subpass.pInputAttachments = NULL;
  subpass.colorAttachmentCount = 1;
  subpass.pResolveAttachments = NULL;
  subpass.pColorAttachments = &color_reference;
  subpass.pDepthStencilAttachment = &depth_reference;
  subpass.preserveAttachmentCount = 0;
  subpass.pPreserveAttachments = NULL;

  VkRenderPassCreateInfo rpc;
  rpc.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  rpc.pNext = NULL;  // VkRenderPassInputAttachmentAspectCreateInfo or VkRenderPassMultiviewCreateInfo
  rpc.flags = 0;
  rpc.attachmentCount = 2;
  rpc.pAttachments = attachments;
  rpc.subpassCount = 1;
  rpc.pSubpasses = &subpass;
  rpc.dependencyCount = 0;
  rpc.pDependencies = NULL;

  vk(CreateRenderPass(device, &rpc, NULL, render_pass));
  return 0;
}

int
CreateShaderModule(
    VkDevice device,
    char const *spirv_filename,
    VkShaderModule *shader_module
)
{    
  std::vector<char> spirv;
  std::ifstream file(spirv_filename, std::ios::binary);  
  if (!file.good()) {
    return -1;
  }
  file.seekg(0, std::ios_base::end);
  std::streampos size = file.tellg();
  file.seekg(0, std::ios_base::beg);
  spirv.resize(size);
  file.read(spirv.data(), size);

  VkShaderModuleCreateInfo smc;
  smc.sType =  VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  smc.pNext = NULL; // VkShaderModuleValidationCacheCreateInfoEXT
  smc.flags = 0;
  smc.codeSize = size;
  smc.pCode = reinterpret_cast<uint32_t const *>(spirv.data());

  vk(CreateShaderModule(device, &smc, NULL, shader_module));
  return 0;
}

int
CreateVertexShaderModule(
    VkDevice device,
    VkShaderModule *vertex_shader_module)
{
/*
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
  "}\n\n\n";
*/
  re(CreateShaderModule(device, "vertex.spirv", vertex_shader_module));
  return 0;
}

int
CreateFragmentShaderModule(
    VkDevice device,
    VkShaderModule *fragment_shader_module)
{
/*
  static char const fragment_glsl[] =
  "#version 400\n"
  "#extension GL_ARB_separate_shader_objects : enable\n"
  "#extension GL_ARB_shading_language_420pack : enable\n"
  "layout(binding = 1) uniform sampler2D tex;\n"
  "layout(location = 0) in vec2 texcoord;\n"
  "layout(location = 0) out vec4 outColor;\n"
  "void main() { outColor = textureLod(tex, texcoord, 0.0); }\n";
*/
  re(CreateShaderModule(device, "fragment.spirv", fragment_shader_module));
  return 0;
}

int
CreateFramebuffers(
  VkDevice device,
  uint32_t image_count,
  VkExtent2D surface_extent,
  VkRenderPass render_pass,
  VkImageView depth_image_view,
  std::unique_ptr<VkImageView[]> const& swapchain_image_views,
  std::unique_ptr<VkFramebuffer[]> *swapchain_framebuffers)
{
  swapchain_framebuffers->reset(new VkFramebuffer[image_count]);

  for (uint32_t k = 0; k < image_count; ++k) {
    VkImageView attachments[2];
    attachments[0] = swapchain_image_views[k];
    attachments[1] = depth_image_view;

    VkFramebufferCreateInfo fbc;
    fbc.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbc.pNext = NULL;
    fbc.flags = 0;
    fbc.renderPass = render_pass;
    fbc.attachmentCount = 2;
    fbc.pAttachments = attachments;
    fbc.width = surface_extent.width;
    fbc.height = surface_extent.height;
    fbc.layers = 1;

    vk(CreateFramebuffer(device, &fbc, NULL, &((*swapchain_framebuffers)[k])));
  }
  return 0;
}

int
CreateSampler(
  VkDevice device,
  VkSampler *sampler
)
{
  VkSamplerCreateInfo scr;
  scr.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  scr.pNext = NULL;
  scr.flags = 0;
  scr.magFilter = VK_FILTER_LINEAR;
  scr.minFilter = VK_FILTER_LINEAR;
  scr.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
  scr.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  scr.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  scr.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  scr.mipLodBias = 0.0f;
  scr.anisotropyEnable = VK_FALSE;
  scr.maxAnisotropy = 0.0f;
  scr.compareEnable = VK_FALSE;
  scr.compareOp = VK_COMPARE_OP_NEVER;
  scr.minLod = 0.0f;
  scr.maxLod = 0.0f;
  scr.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
  scr.unnormalizedCoordinates = VK_FALSE;

  vk(CreateSampler(device, &scr, NULL, sampler));
  return 0;
}

int
CreateDescriptorSetLayout(
  VkDevice device,
  VkDescriptorSetLayout *descriptor_set_layout)
{
  VkDescriptorSetLayoutBinding layout_bindings[2];
  layout_bindings[0].binding = 0;
  layout_bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  layout_bindings[0].descriptorCount = 1;
  layout_bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  layout_bindings[0].pImmutableSamplers = NULL;

  layout_bindings[1].binding = 1;
  layout_bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  layout_bindings[1].descriptorCount = 1;
  layout_bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  layout_bindings[1].pImmutableSamplers = NULL;

  VkDescriptorSetLayoutCreateInfo dsl;
  dsl.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  dsl.pNext = NULL;  // of VkDescriptorSetLayoutBindingFlagsCreateInfoEXT
  dsl.flags = 0;
  dsl.bindingCount = 2;
  dsl.pBindings = layout_bindings;

  vk(CreateDescriptorSetLayout(device, &dsl, NULL, descriptor_set_layout));
  return 0;
}

int
CreateDescriptorPool(
    VkDevice device,
    VkDescriptorPool *descriptor_pool)
{
  VkDescriptorPoolSize desc_pool_sizes[2];
  desc_pool_sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  desc_pool_sizes[0].descriptorCount = 1;

  desc_pool_sizes[1].type  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  desc_pool_sizes[1].descriptorCount = 1;

  VkDescriptorPoolCreateInfo dpl;
  dpl.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  dpl.pNext = NULL;
  dpl.flags = 0;
  dpl.maxSets = 1;
  dpl.poolSizeCount = 2;
  dpl.pPoolSizes = desc_pool_sizes;
  vk(CreateDescriptorPool(device, &dpl, NULL, descriptor_pool));
  return 0;
}

int
AllocateDescriptorSets(
    VkDevice device,
    VkDescriptorPool descriptor_pool,
    VkDescriptorSetLayout const *descriptor_set_layout,
    VkDescriptorSet *descriptor_set)
{
  VkDescriptorSetAllocateInfo dsa;
  dsa.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  dsa.pNext = NULL;  //  VkDescriptorSetVariableDescriptorCountAllocateInfoEXT
  dsa.descriptorPool = descriptor_pool;
  dsa.descriptorSetCount = 1;
  dsa.pSetLayouts = descriptor_set_layout;

  vk(AllocateDescriptorSets(device, &dsa, descriptor_set));
  return 0;
}

int
UpdateDescriptorSets(
  VkDevice device,
  VkDescriptorSet descriptor_set,
  VkBuffer uniform_buffer,
  VkImageView texture_image_view,
  VkSampler sampler)
{
  VkWriteDescriptorSet write_descriptor[2];

  VkDescriptorBufferInfo uniform_descriptor_buffer;
  uniform_descriptor_buffer.buffer = uniform_buffer;
  uniform_descriptor_buffer.offset = 0;
  uniform_descriptor_buffer.range = 4 * 4 * sizeof(float); // sizeof(mvp) // glm::mat4

  write_descriptor[0].sType =  VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  write_descriptor[0].pNext = NULL;
  write_descriptor[0].dstSet = descriptor_set;
  write_descriptor[0].dstBinding = 0;
  write_descriptor[0].dstArrayElement = 0;
  write_descriptor[0].descriptorCount = 1;
  write_descriptor[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  write_descriptor[0].pImageInfo = NULL;
  write_descriptor[0].pBufferInfo = &uniform_descriptor_buffer;
  write_descriptor[0].pTexelBufferView = NULL;

  VkDescriptorImageInfo descriptor_image;
  descriptor_image.sampler = sampler;
  descriptor_image.imageView = texture_image_view;
  descriptor_image.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

  write_descriptor[1].sType =  VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  write_descriptor[1].pNext = NULL;
  write_descriptor[1].dstSet = descriptor_set;
  write_descriptor[1].dstBinding = 1;
  write_descriptor[1].dstArrayElement = 0;
  write_descriptor[1].descriptorCount = 1;
  write_descriptor[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  write_descriptor[1].pImageInfo = &descriptor_image;
  write_descriptor[1].pBufferInfo = NULL;
  write_descriptor[1].pTexelBufferView = NULL;

  vkUpdateDescriptorSets(device, 2, write_descriptor, 0, NULL);
  return 0;
}

int
CreatePipelineCache(
    VkDevice device,
    VkPipelineCache *pipeline_cache)
{
  VkPipelineCacheCreateInfo pcc;
  pcc.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
  pcc.pNext = NULL;
  pcc.flags = 0;
  pcc.initialDataSize = 0;
  pcc.pInitialData = NULL;

  vk(CreatePipelineCache(device, &pcc, NULL, pipeline_cache));
  return 0;
}

void
ConfigurePipelineVertexInputState(
    VkVertexInputBindingDescription *vib,
    VkVertexInputAttributeDescription attributes[2],
    VkPipelineVertexInputStateCreateInfo *pvi)
{
  vib->binding = 0;
  vib->stride = 6 * sizeof(float); // x y z w u v; vertex_size_bytes;
  vib->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

  attributes[0].location = 0;
  attributes[0].binding = 0;
  attributes[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
  attributes[0].offset = 0;

  attributes[1].location = 1;
  attributes[1].binding = 0;
  attributes[1].format = VK_FORMAT_R32G32_SFLOAT;
  attributes[1].offset = 4 * sizeof(float);

  pvi->sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  pvi->pNext = NULL;  // VkPipelineVertexInputDivisorStateCreateInfoEXT
  pvi->flags = 0;
  pvi->vertexBindingDescriptionCount = 1;
  pvi->pVertexBindingDescriptions = vib;
  pvi->vertexAttributeDescriptionCount = 2;
  pvi->pVertexAttributeDescriptions = attributes;
}

void
ConfigurePipelineInputAssemblyState(
    VkPipelineInputAssemblyStateCreateInfo *pia)
{
  pia->sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  pia->pNext = NULL;
  pia->flags = 0;
  pia->topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  pia->primitiveRestartEnable = VK_FALSE;
}

void
ConfigurePipelineRasterizationState(
    VkPipelineRasterizationStateCreateInfo *prs)
{
  prs->sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  prs->pNext = NULL;
  prs->flags = 0;
  prs->depthClampEnable = VK_TRUE;
  prs->rasterizerDiscardEnable = VK_FALSE;
  prs->polygonMode = VK_POLYGON_MODE_FILL;
  prs->cullMode = VK_CULL_MODE_BACK_BIT;
  prs->frontFace = VK_FRONT_FACE_CLOCKWISE;
  prs->depthBiasEnable = VK_FALSE;
  prs->depthBiasConstantFactor = 0.0f;
  prs->depthBiasClamp = 0.0f;
  prs->depthBiasSlopeFactor = 0.0f;
  prs->lineWidth = 1.0f;
}

void
ConfigurePipelineColorBlendAttachmentState(
    VkPipelineColorBlendAttachmentState *cba){
  cba->blendEnable = VK_FALSE;
  cba->srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  cba->dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  cba->colorBlendOp = VK_BLEND_OP_ADD;
  cba->srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  cba->dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  cba->alphaBlendOp = VK_BLEND_OP_ADD;
  cba->colorWriteMask = (
      VK_COLOR_COMPONENT_R_BIT |
      VK_COLOR_COMPONENT_G_BIT |
      VK_COLOR_COMPONENT_B_BIT |
      VK_COLOR_COMPONENT_A_BIT);
}

void
ConfigurePipelineColorBlendState(
    VkPipelineColorBlendAttachmentState const *cba,
    VkPipelineColorBlendStateCreateInfo *pcb)
{
  pcb->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  pcb->pNext = NULL;
  pcb->flags = 0;
  pcb->logicOpEnable = VK_FALSE;
  pcb->logicOp = VK_LOGIC_OP_CLEAR;
  pcb->attachmentCount = 1;
  pcb->pAttachments = cba;
  pcb->blendConstants[0] = 1.0f;
  pcb->blendConstants[1] = 1.0f;
  pcb->blendConstants[2] = 1.0f;
  pcb->blendConstants[3] = 1.0f;
}

void
ConfigurePipelineViewportState(
    VkPipelineViewportStateCreateInfo *pvs) {
  pvs->sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  pvs->pNext = NULL;
  pvs->flags = 0;
  pvs->viewportCount = 1;
  pvs->pViewports = NULL;
  pvs->scissorCount = 1;
  pvs->pScissors = NULL;
}

void
ConfigurePipelineDynamicState(
    VkDynamicState dynamic_states[2],
    VkPipelineDynamicStateCreateInfo *pds)
{
  dynamic_states[0] = VK_DYNAMIC_STATE_VIEWPORT;
  dynamic_states[1] = VK_DYNAMIC_STATE_SCISSOR;

  pds->sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  pds->pNext = NULL;
  pds->flags = 0;
  pds->dynamicStateCount = 2;
  pds->pDynamicStates = dynamic_states;
}

void
ConfigureStencilOpState (
    VkStencilOpState *sos)
{
  sos->failOp = VK_STENCIL_OP_KEEP;
  sos->passOp = VK_STENCIL_OP_KEEP;
  sos->depthFailOp = VK_STENCIL_OP_KEEP;
  sos->compareOp = VK_COMPARE_OP_ALWAYS;
  sos->compareMask = 0;
  sos->writeMask = 0;
  sos->reference = 0;
}

void
ConfigurePipelineDepthStencilState(
    VkStencilOpState const *sos,
    VkPipelineDepthStencilStateCreateInfo *dss)
{
  dss->sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  dss->pNext = NULL;
  dss->flags = 0;
  dss->depthTestEnable = VK_FALSE;
  dss->stencilTestEnable = VK_FALSE;
  dss->depthWriteEnable = VK_FALSE;
  dss->depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
  dss->depthBoundsTestEnable = VK_FALSE;
  dss->front = *sos;
  dss->back = *sos;
  dss->minDepthBounds = 0.0f;
  dss->maxDepthBounds = 0.0f;
}

void
ConfigurePipelineMultisampleState(
    VkPipelineMultisampleStateCreateInfo *pms)
{
  pms->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  pms->pNext = NULL;
  pms->flags = 0;
  pms->rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  pms->sampleShadingEnable = VK_FALSE;
  pms->minSampleShading = 0.0f;
  pms->pSampleMask = NULL;
  pms->alphaToCoverageEnable = VK_FALSE;
  pms->alphaToOneEnable = VK_FALSE;
}

void
ConfigurePipelineShaderStages(
    VkShaderModule vertex_shader_module,
    VkShaderModule fragment_shader_module,
    VkPipelineShaderStageCreateInfo stages[2])
{
  stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  stages[0].pNext = NULL;
  stages[0].flags = 0;
  stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
  stages[0].module = vertex_shader_module;
  stages[0].pName = "main";
  stages[0].pSpecializationInfo = NULL;

  stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  stages[1].pNext = NULL;
  stages[1].flags = 0;
  stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  stages[1].module = fragment_shader_module;
  stages[1].pName = "main";
  stages[1].pSpecializationInfo = NULL;
}

int
CreatePipelineLayout(
    VkDevice device,
    VkDescriptorSetLayout const *descriptor_set_layout,
    VkPipelineLayout *pipeline_layout)
{
  VkPipelineLayoutCreateInfo plc;
  plc.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  plc.pNext = NULL;
  plc.flags = 0;
  plc.setLayoutCount = 1;
  plc.pSetLayouts = descriptor_set_layout;
  plc.pushConstantRangeCount = 0;
  plc.pPushConstantRanges = NULL;

  vk(CreatePipelineLayout( device, &plc, NULL, pipeline_layout));
  return 0;
}

int
CreateGraphicsPipelines(
    VkDevice device,
    VkPipelineCache pipeline_cache,
    VkPipelineShaderStageCreateInfo shader_stages[2],
    VkPipelineVertexInputStateCreateInfo const *pvi,
    VkPipelineInputAssemblyStateCreateInfo const *pia,
    VkPipelineViewportStateCreateInfo const *pvs,
    VkPipelineRasterizationStateCreateInfo const *prs,
    VkPipelineMultisampleStateCreateInfo const *pms,
    VkPipelineDepthStencilStateCreateInfo const *dss,
    VkPipelineColorBlendStateCreateInfo const *pcb,
    VkPipelineDynamicStateCreateInfo const *pds,
    VkPipelineLayout pipeline_layout,
    VkRenderPass render_pass,
    VkPipeline *pipeline)
{
  VkGraphicsPipelineCreateInfo gpc[1];
  gpc->sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  gpc->pNext = NULL;
  gpc->flags = 0;
  gpc->stageCount = 2;
  gpc->pStages = shader_stages;
  gpc->pVertexInputState = pvi;
  gpc->pInputAssemblyState = pia;
  gpc->pTessellationState = NULL;
  gpc->pViewportState = pvs;
  gpc->pRasterizationState = prs;
  gpc->pMultisampleState = pms;
  gpc->pDepthStencilState = dss;
  gpc->pColorBlendState = pcb;
  gpc->pDynamicState = pds;
  gpc->layout = pipeline_layout;
  gpc->renderPass = render_pass;
  gpc->subpass = 0;
  gpc->basePipelineHandle = VK_NULL_HANDLE;
  gpc->basePipelineIndex = 0;

  vk(CreateGraphicsPipelines(device, pipeline_cache, 1, gpc, NULL, pipeline));
  return 0;
}

int
ConfigureAndCreateGraphicsPipeline(
    VkDevice device,
    VkPipelineCache pipeline_cache,
    VkShaderModule vertex_shader_module,
    VkShaderModule fragment_shader_module,
    VkDescriptorSetLayout const *descriptor_set_layout,
    VkRenderPass render_pass,
    VkPipelineLayout pipeline_layout,
    VkPipeline *pipeline)
{
  VkPipelineShaderStageCreateInfo shader_stages[2];
  ConfigurePipelineShaderStages (
      vertex_shader_module, fragment_shader_module, shader_stages);

  VkVertexInputBindingDescription vib;
  VkVertexInputAttributeDescription vertex_attributes[2];
  VkPipelineVertexInputStateCreateInfo pvi;
  ConfigurePipelineVertexInputState(&vib, vertex_attributes, &pvi);

  VkPipelineInputAssemblyStateCreateInfo pia;
  ConfigurePipelineInputAssemblyState(&pia);

  VkPipelineViewportStateCreateInfo pvs;
  ConfigurePipelineViewportState (&pvs);

  VkPipelineRasterizationStateCreateInfo prs;
  ConfigurePipelineRasterizationState (&prs);

  VkPipelineMultisampleStateCreateInfo pms;
  ConfigurePipelineMultisampleState (&pms);

  VkStencilOpState sos;
  ConfigureStencilOpState (&sos);
  VkPipelineDepthStencilStateCreateInfo dss;
  ConfigurePipelineDepthStencilState (&sos, &dss);

  VkPipelineColorBlendAttachmentState cba;
  ConfigurePipelineColorBlendAttachmentState (&cba);
  VkPipelineColorBlendStateCreateInfo pcb;
  ConfigurePipelineColorBlendState (&cba, &pcb);

  VkDynamicState dynamic_states[2];
  VkPipelineDynamicStateCreateInfo pds;
  ConfigurePipelineDynamicState (dynamic_states, &pds);

  re(CreateGraphicsPipelines(
    device, pipeline_cache, shader_stages,
    &pvi, &pia, &pvs, &prs, &pms, &dss, &pcb, &pds,
    pipeline_layout, render_pass,
    pipeline));

  return 0;
}


int
AcquireSwapchainImage(
    VkDevice device,
    VkSwapchainKHR swapchain,
    VkSemaphore present_complete,
    uint32_t *n_swapchain_image)
{
  vk(AcquireNextImageKHR(
      device, swapchain, 1000, present_complete, VK_NULL_HANDLE,
      n_swapchain_image));
  std::cerr << "Acquired swapchain image: " << *n_swapchain_image << std::endl;
  return 0;
}

void
BeginCommandBuffer(VkCommandBuffer command_buffer)
{
  VkCommandBufferBeginInfo cbb;
  cbb.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  cbb.pNext = NULL;  // VkDeviceGroupCommandBufferBeginInfo
  cbb.flags = 0;  // VK_COMMAND_BUFFER_USAGE_*
  cbb.pInheritanceInfo = NULL;
  vkBeginCommandBuffer(command_buffer, &cbb);
}

void
ConfigureImageMemoryBarrier(
    VkImage image, VkImageAspectFlags aspect,
    VkAccessFlags src_access,  VkImageLayout old_layout,
    VkAccessFlags dst_access,  VkImageLayout new_layout,
    VkImageMemoryBarrier *imb) {
  imb->sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  imb->pNext = NULL;
  imb->srcAccessMask = src_access;
  imb->dstAccessMask = dst_access;
  imb->oldLayout = old_layout;
  imb->newLayout = new_layout;
  imb->srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  imb->dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  imb->image = image;
  imb->subresourceRange.aspectMask = aspect;
  imb->subresourceRange.baseMipLevel = 0;
  imb->subresourceRange.levelCount = 1;
  imb->subresourceRange.baseArrayLayer = 0;
  imb->subresourceRange.layerCount = 1;
}


void
TopOfPipelineImageMemoryBarriers(
    VkCommandBuffer command_buffer,
    VkImage depth_image,
    VkImage texture_image,
    VkImage swapchain_image)
{
  VkImageMemoryBarrier imb[3];
  // depth buffer
  ConfigureImageMemoryBarrier(
      depth_image, VK_IMAGE_ASPECT_DEPTH_BIT,
      0,
      VK_IMAGE_LAYOUT_UNDEFINED,
      VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
      VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
      &imb[0]);

  // frame buffer
  ConfigureImageMemoryBarrier(
      swapchain_image, VK_IMAGE_ASPECT_COLOR_BIT,
      0,
      VK_IMAGE_LAYOUT_UNDEFINED,
      VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
      VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
      &imb[1]);
      
  // texture
  ConfigureImageMemoryBarrier(
      texture_image, VK_IMAGE_ASPECT_COLOR_BIT,
      VK_ACCESS_HOST_WRITE_BIT, VK_IMAGE_LAYOUT_PREINITIALIZED,
      VK_ACCESS_SHADER_READ_BIT, VK_IMAGE_LAYOUT_GENERAL,
      &imb[2]);

  vkCmdPipelineBarrier(
      command_buffer,
      VK_PIPELINE_STAGE_HOST_BIT | VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
      VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
      0,  // VkDependencyFlags
      0, NULL,  // VkMemoryBarrier
      0, NULL,  // VkBufferMemoryBarrier
      3, imb);  // VkimageMemoryBarrier
}

void BeginRenderPass(
    VkCommandBuffer command_buffer,
    VkRenderPass render_pass,
    VkFramebuffer framebuffer,
    VkExtent2D surface_extent)
{
  VkClearValue clear_values[2];
  clear_values[0].color.float32[0] = 0.0f;
  clear_values[0].color.float32[1] = 0.0f;
  clear_values[0].color.float32[2] = 0.8f;
  clear_values[0].color.float32[3] = 1.0f;
  clear_values[1].depthStencil.depth = 1.0f;
  clear_values[1].depthStencil.stencil = 1.0f;

  VkRenderPassBeginInfo rpb;
  rpb.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  rpb.pNext = NULL;  // 
  rpb.renderPass = render_pass;
  rpb.framebuffer = framebuffer;
  rpb.renderArea.offset.x = 0;
  rpb.renderArea.offset.y = 0;
  rpb.renderArea.extent.width = surface_extent.width;
  rpb.renderArea.extent.height = surface_extent.height;
  rpb.clearValueCount = 2;
  rpb.pClearValues = clear_values;

  vkCmdBeginRenderPass(
      command_buffer, &rpb, VK_SUBPASS_CONTENTS_INLINE);

/*
  VkClearAttachment clear_attachments[2];
  clear_attachments[0].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  clear_attachments[0].colorAttachment = 0;
  clear_attachments[0].clearValue.color.float32[0] = 0.2f;
  clear_attachments[0].clearValue.color.float32[1] = 0.2f;
  clear_attachments[0].clearValue.color.float32[2] = 0.2f;
  clear_attachments[0].clearValue.color.float32[3] = 1.0f;

  clear_attachments[1].aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
  clear_attachments[1].clearValue.depthStencil.depth = 1.0f;
  clear_attachments[1].clearValue.depthStencil.stencil = 1.0f;

  VkClearRect clear_rect;
  clear_rect.rect.offset.x = 0;
  clear_rect.rect.offset.y = 0;
  clear_rect.rect.extent.width = surface_extent.width;
  clear_rect.rect.extent.height = surface_extent.height;
  clear_rect.baseArrayLayer = 0;
  clear_rect.layerCount = 1;

  vkCmdClearAttachments(
      command_buffer, 2, clear_attachments, 1, &clear_rect);
*/
}

void
SetViewportAndScissor(
    VkCommandBuffer command_buffer,
    VkExtent2D surface_extent)
{
  VkViewport viewport;
  viewport.x = 0;
  viewport.y = 0;
  viewport.width = surface_extent.width;
  viewport.height = surface_extent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(command_buffer, 0, 1, &viewport);

  VkRect2D scissor;
  scissor.extent.width = surface_extent.width;
  scissor.extent.height = surface_extent.height;
  vkCmdSetScissor(command_buffer, 0, 1, &scissor);
}

void
BindGraphicsPipeline(
    VkCommandBuffer command_buffer,
    VkPipeline pipeline,
    VkPipelineLayout pipeline_layout,
    VkDescriptorSet const *descriptor_set)
{
  vkCmdBindPipeline(
      command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
  vkCmdBindDescriptorSets(
      command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout,
      0, 1, descriptor_set, 0, NULL);
}

void
DrawVertexBuffer(
    VkCommandBuffer command_buffer,
    VkBuffer vertex_buffer,
    uint32_t n_vertices)
{
  VkDeviceSize buffer_offset = 0;
  vkCmdBindVertexBuffers (command_buffer, 0, 1, &vertex_buffer, &buffer_offset);
  vkCmdDraw (command_buffer, n_vertices, 1, 0, 0);
}

void
EndRenderPass(
    VkCommandBuffer command_buffer)
{
  vkCmdEndRenderPass (command_buffer);
}      

void
BottomOfPipelineImageMemoryBarriers(
    VkCommandBuffer command_buffer,
    VkImage swapchain_image)
{
  VkImageMemoryBarrier imb;
  ConfigureImageMemoryBarrier(
      swapchain_image, VK_IMAGE_ASPECT_COLOR_BIT,
      VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
      VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
      VK_ACCESS_MEMORY_READ_BIT,
      VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
      &imb);
      
  vkCmdPipelineBarrier(
      command_buffer,
      VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
      VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
      0,  // VkDependencyFlags
      0, NULL,  // VkMemoryBarrier
      0, NULL,  // VkBufferMemoryBarrier
      1, &imb);  // VkimageMemoryBarrier
}

int
QueueSubmit(
    VkQueue queue,
    VkCommandBuffer command_buffer,
    VkSemaphore present_complete,
    VkSemaphore render_complete)
{
  VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

  VkSubmitInfo sub;
  sub.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  sub.pNext = NULL;
  sub.waitSemaphoreCount = 1;
  sub.pWaitSemaphores = &present_complete;
  sub.pWaitDstStageMask = &wait_stage;
  sub.commandBufferCount = 1;
  sub.pCommandBuffers  = &command_buffer;
  sub.signalSemaphoreCount = 1;
  sub.pSignalSemaphores = &render_complete;

  vk(QueueSubmit (queue, 1, &sub, VK_NULL_HANDLE));
  return 0;
}

int
QueuePresent(
    VkQueue queue,
    VkSwapchainKHR swapchain,
    uint32_t n_swapchain_image,
    VkSemaphore render_complete)
{

  VkResult present_result = VK_INCOMPLETE;
  VkPresentInfoKHR pre;
  pre.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  pre.pNext = NULL;
  pre.waitSemaphoreCount = 1;
  pre.pWaitSemaphores = &render_complete;
  pre.swapchainCount = 1;
  pre.pSwapchains = &swapchain;
  pre.pImageIndices = &n_swapchain_image;
  pre.pResults = &present_result;

  vk(QueuePresentKHR(queue, &pre));
  vk(QueueWaitIdle(queue));
  if (present_result != VK_SUCCESS) {
    std::cerr << __FILE__ << " : " << __LINE__ 
        << "  present_result: " << vkResultString(present_result) << std::endl;
    return -1;
  }
  return 0;
}

int
Draw(
    VkDevice device,
    VkSwapchainKHR swapchain,
    VkCommandBuffer command_buffer,
    VkRenderPass render_pass,
    VkPipeline pipeline,
    VkPipelineLayout pipeline_layout,
    VkDescriptorSet const *descriptor_set,
    VkExtent2D surface_extent,
    VkBuffer vertex_buffer,
    uint32_t n_vertices,
    VkImage texture_image,
    VkImage depth_image,
    VkImage swapchain_image,
    VkFramebuffer framebuffer)
{

  BeginCommandBuffer(command_buffer);


  TopOfPipelineImageMemoryBarriers(
      command_buffer, depth_image, texture_image, swapchain_image);

  BeginRenderPass (command_buffer, render_pass, framebuffer, surface_extent);

  BindGraphicsPipeline (
      command_buffer, pipeline, pipeline_layout, descriptor_set);

  SetViewportAndScissor (command_buffer, surface_extent);

  DrawVertexBuffer (command_buffer, vertex_buffer, n_vertices);

  EndRenderPass (command_buffer);

  BottomOfPipelineImageMemoryBarriers (command_buffer, swapchain_image);

  vk(EndCommandBuffer (command_buffer));
  return 0;
}

void
GetImagePitch(
  VkDevice device,
  VkImage image,
  uint32_t *size, uint32_t *pitch)
{
  VkMemoryRequirements mem_reqs;
  vkGetImageMemoryRequirements(device, image, &mem_reqs);

  *size = mem_reqs.size;

  VkImageSubresource isr;
  isr.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  isr.mipLevel = 0;
  isr.arrayLayer = 0;

  VkSubresourceLayout layout;
  vkGetImageSubresourceLayout(device, image, &isr, &layout);

  *pitch = layout.rowPitch;
}

int
CreateScene(
    VkPhysicalDevice physical_device,
    VkDevice device,
    VkExtent2D surface_extent,

    VkBuffer *vertex_buffer,
    VkDeviceMemory *vertex_memory,
    uint32_t *n_vertices,

    VkBuffer *uniform_buffer,
    VkDeviceMemory *uniform_memory,

    VkImage *texture_image,
    VkDeviceMemory *texture_memory,
    VkImageView *texture_image_view)
{
  uint32_t const nvxs = 3;
  *n_vertices = nvxs;
  uint32_t vertex_buffer_size = nvxs * 6 * sizeof(float); // x y z w u v;
  re(CreateVertexBuffer(
      physical_device, device, vertex_buffer_size,
      vertex_buffer, vertex_memory));

  float vertex_data[nvxs * 6] = {
      -1.0f,  1.0f, 0.5f, 1.0f, 0.0f, 1.0f,
       1.0f,  1.0f, 0.5f, 1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 0.5f, 1.0f, 0.0f, 0.0f,
/*
      -1.0f, -1.0f, 0.5f, 1.0f, 0.0f, 0.0f,
       1.0f,  1.0f, 0.5f, 1.0f, 1.0f, 1.0f,
       1.0f, -1.0f, 0.5f, 1.0f, 1.0f, 0.0f, */
  }; 

  re(MapAndInitializeMemory (device, *vertex_memory, vertex_data, sizeof(vertex_data)));

  tr(CreateUniformBuffer_float4x4(
      physical_device, device,
      uniform_buffer, uniform_memory));

  float fov = glm::radians(45.0f);
  if (surface_extent.width > surface_extent.height) {
    fov *= static_cast<float>(surface_extent.height) /
           static_cast<float>(surface_extent.width);
  }

  glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::lookAt(
      glm::vec3(0, 0, 5),   // Camera is at (0,0,5), in World Space
      glm::vec3(0, 0, 0),   // and looks at the origin
      glm::vec3(0, 1, 0));  // Head is up (set to 0,-1,0 to look upside-down)

  glm::mat4 model = glm::mat4(1.0f);
  // Vulkan clip space has inverted Y and half Z.
  glm::mat4 clip = glm::mat4(1.0f,  0.0f, 0.0f, 0.0f,
                             0.0f, -1.0f, 0.0f, 0.0f,
                             0.0f,  0.0f, 0.5f, 0.0f,
                             0.0f,  0.0f, 0.5f, 1.0f);

  glm::mat4 mvp = clip * projection * view * model;

  re(MapAndInitializeMemory (device, *uniform_memory, &mvp, sizeof(mvp)));

  VkFormat texture_format = VK_FORMAT_B8G8R8A8_UNORM; //VK_FORMAT_R8G8B8A8_UNORM;
  VkExtent2D texture_extent = surface_extent;
  tr(CreateAndAllocateImage2D(
      physical_device,
      device, texture_extent, texture_format,
      VK_IMAGE_TILING_LINEAR,
      VK_IMAGE_USAGE_SAMPLED_BIT,
      (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
       VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
      texture_image, texture_memory));

  tr(CreateImage2DView(
      device, *texture_image, texture_format, VK_IMAGE_ASPECT_COLOR_BIT,
      texture_image_view));

  uint32_t texture_size, texture_pitch;
  GetImagePitch (device, *texture_image, &texture_size, &texture_pitch);
  std::unique_ptr<uint8_t []> texture(new uint8_t [texture_size]);

  for (uint32_t x = 0; x < texture_extent.width; ++x) {
    for (uint32_t y = 0; y < texture_extent.height; ++y) {
      uint8_t red = (255 * x) / texture_extent.width;
      uint8_t green = (255 * (texture_extent.width - x)) / texture_extent.width;
      uint8_t blue = (255 * y) / texture_extent.height;
      uint8_t alpha = (255 * (texture_extent.height - y)) / texture_extent.height;

      texture[0 + 4 * x + texture_pitch * y] = blue;
      texture[1 + 4 * x + texture_pitch * y] = green;
      texture[2 + 4 * x + texture_pitch * y] = red;
      texture[3 + 4 * x + texture_pitch * y] = alpha;
    }
  }

  re(MapAndInitializeMemory (device, *texture_memory, texture.get(), texture_size));
  return 0;
}

int main(int argc, char **argv)
{
  VkInstance instance;
  tr(InitVulkanInstance(&instance));

  VkDebugReportCallbackEXT debug_report_callback;
  tr(CreateDebugReportCallback(instance, &debug_report_callback));

  VkPhysicalDevice physical_device;
  uint32_t queue_family;
  VkPhysicalDeviceFeatures device_features;
  tr(InitVulkanDevice(instance, &physical_device, &queue_family, &device_features));

  VkFormat surface_format = VK_FORMAT_B8G8R8A8_UNORM;
  VkExtent2D surface_extent {1920, 1080};
  VkSurfaceKHR surface;
  GLFWwindow *window;
  tr(CreateWindowSurface(
      instance, physical_device, surface_format, surface_extent, &window, &surface));

  VkDevice device;
  tr(CreateDevice(physical_device, device_features, queue_family, &device));


  VkBuffer vertex_buffer;
  VkDeviceMemory vertex_memory;
  uint32_t n_vertices;

  VkBuffer uniform_buffer;
  VkDeviceMemory uniform_memory;

  VkImage texture_image;
  VkDeviceMemory texture_memory;
  VkImageView texture_image_view;

  tr(CreateScene(
      physical_device, device, surface_extent,
      &vertex_buffer, &vertex_memory, &n_vertices,
      &uniform_buffer, &uniform_memory,
      &texture_image, &texture_memory, &texture_image_view));

  VkCommandPool command_pool;
  VkQueue queue;
  tr(CreateCommandPoolAndQueue(device, queue_family, &command_pool, &queue));
  
  VkCommandBuffer command_buffer;
  tr(CreateCommandBuffer(device, command_pool, &command_buffer));

  VkSemaphore render_complete, present_complete;
  tr(CreateSemaphore(device, &render_complete));
  tr(CreateSemaphore(device, &present_complete));

  VkImage depth_image;
  VkDeviceMemory depth_memory;
  VkImageView depth_image_view;
  tr(CreateDepthBuffer(
      physical_device, device, surface_extent, 
      &depth_image, &depth_memory, &depth_image_view));

  VkSwapchainKHR swapchain;
  uint32_t image_count = 2;
  tr(CreateSwapchain(
      physical_device, device, queue_family, surface, surface_format,
      &image_count, &swapchain));

  std::unique_ptr<VkImage[]> swapchain_images;
  std::unique_ptr<VkImageView[]> swapchain_image_views;
  tr(CreateSwapchainImageViews(
      device, swapchain, surface_format, image_count, 
      &swapchain_images, &swapchain_image_views));

  VkRenderPass render_pass;
  tr(CreateRenderPass(device, surface_format, &render_pass));

  std::unique_ptr<VkFramebuffer[]> swapchain_framebuffers;
  tr(CreateFramebuffers(
      device, image_count, surface_extent, render_pass,
      depth_image_view, swapchain_image_views,
      &swapchain_framebuffers));

  VkSampler sampler;
  tr(CreateSampler(device, &sampler));

  VkShaderModule vertex_shader_module;
  tr(CreateVertexShaderModule(device, &vertex_shader_module));

  VkShaderModule fragment_shader_module;
  tr(CreateFragmentShaderModule(device, &fragment_shader_module));

  VkDescriptorPool descriptor_pool;
  tr(CreateDescriptorPool(device, &descriptor_pool));

  VkDescriptorSetLayout descriptor_set_layout;
  tr(CreateDescriptorSetLayout(device, &descriptor_set_layout));

  VkDescriptorSet descriptor_set;
  tr(AllocateDescriptorSets(
    device, descriptor_pool, &descriptor_set_layout,
    &descriptor_set));

  tr(UpdateDescriptorSets(
      device, descriptor_set, uniform_buffer, texture_image_view, sampler));

  VkPipelineCache pipeline_cache;
  tr(CreatePipelineCache (device, &pipeline_cache));

  VkPipelineLayout pipeline_layout;
  tr(CreatePipelineLayout (device, &descriptor_set_layout, &pipeline_layout));

  VkPipeline pipeline;
  tr(ConfigureAndCreateGraphicsPipeline(
      device, pipeline_cache,
      vertex_shader_module, fragment_shader_module,
      &descriptor_set_layout, render_pass, pipeline_layout,
      &pipeline));

  uint32_t n_swapchain_image;
  tr(AcquireSwapchainImage(
    device, swapchain, present_complete, &n_swapchain_image));

  tr(Draw(
    device, swapchain, command_buffer, render_pass,
    pipeline, pipeline_layout, &descriptor_set, surface_extent,
    vertex_buffer, n_vertices,
    texture_image, depth_image,
    swapchain_images[n_swapchain_image],
    swapchain_framebuffers[n_swapchain_image]));

  tr(QueueSubmit (queue, command_buffer, present_complete, render_complete));
  tr(QueuePresent (queue, swapchain, n_swapchain_image, render_complete));


  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  return 0;
}
