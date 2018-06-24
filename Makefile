
all: vulkan vertex.spirv fragment.spirv

vertex.spirv: vertex.glsl
	cat vertex.glsl | ~/VulkanSDK/1.1.73.0/x86_64/bin/glslangValidator -V -o vertex.spirv  --stdin -S vert

fragment.spirv: fragment.glsl
	cat fragment.glsl | ~/VulkanSDK/1.1.73.0/x86_64/bin/glslangValidator -V -o fragment.spirv  --stdin -S frag

vulkan: vulkan.cc
	g++ -o vulkan vulkan.cc -Wall -g -L/usr/lib/x86_64-linux-gnu -lglfw -lvulkan 

clean:
	rm -f vulkan vertex.spirv fragment.spirv
