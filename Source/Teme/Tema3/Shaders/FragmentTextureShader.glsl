#version 330
 
uniform sampler2D texture;
in vec3 frag_color;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec4 color1 = texture2D(texture, texcoord);
	vec4 color2 = vec4(frag_color, 1);

	if (frag_color != vec3(0, 0, 0)) {
		out_color = mix(color1, color2, 0.2f);
	} else {
		out_color = color1;
	}

	if (out_color.a < 0.5f) {
		discard;
	}
	
}