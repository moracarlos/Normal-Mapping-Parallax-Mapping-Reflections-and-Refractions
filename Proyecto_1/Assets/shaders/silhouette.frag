#version 330
#extension GL_ARB_separate_shader_objects :enable

in vec3 vVertexColor;
in vec3 fPosition;
in vec3 fNormal;

layout(location = 0) out vec4 vFragColor;

void main(void)
{
	vFragColor = vec4(0.0, 0.0, 0.0, 0.0);
}

