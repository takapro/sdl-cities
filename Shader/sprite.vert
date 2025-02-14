#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 fragTexCoord;

void main()
{
	gl_Position = vec4(inPosition, 1.0) * uWorldTransform * uViewProjection;
	fragTexCoord = inTexCoord;
}
