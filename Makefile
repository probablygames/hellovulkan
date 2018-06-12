
all: triangle vertex.spirv fragment.spirv

vertex.spirv: vertex.glsl
	cat vertex.glsl | ~/VulkanSDK/1.1.73.0/x86_64/bin/glslangValidator -V -o vertex.spirv  --stdin -S vert

fragment.spirv: fragment.glsl
	cat fragment.glsl | ~/VulkanSDK/1.1.73.0/x86_64/bin/glslangValidator -V -o fragment.spirv  --stdin -S frag

triangle: triangle.cc
	g++ -Wall -g `pkg-config --libs vulkan` `pkg-config --libs glfw3` ./triangle.cc -o triangle
