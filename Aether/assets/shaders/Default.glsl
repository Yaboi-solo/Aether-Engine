#type vertex
#version 450

layout (binding = 0) uniform UniformBuffer {
    mat4 u_ViewProjection;
	mat4 u_Model;
} u_Uniforms;

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Color;

layout (location = 0) out vec3 v_Color;

void main() {
    gl_Position = vec4(a_Pos, 1.0);
    v_Color = a_Color;
}

#type fragment
#version 450

layout(location = 0) out vec4 o_Color;

layout (location = 0) in vec3 v_Color;

void main() {
    o_Color = vec4(v_Color, 1.0);
}