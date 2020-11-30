#version 330

in vec2 fragTexCoord;

out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
	vec4 color = texture(uTexture, fragTexCoord);

	if (!gl_FrontFacing) {
		outColor = color;
	} else {
		outColor = vec4(1.0 - color.r, 1.0 - color.g, 1.0 - color.b, color.a);
	}
}
