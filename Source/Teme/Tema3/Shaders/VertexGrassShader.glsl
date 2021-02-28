#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform float time;
uniform int moveLeft;

out vec2 texcoord;
out vec3 frag_color;

void main()
{
	// TODO : pass v_texture_coord as output to Fragment Shader
	texcoord = v_texture_coord;
	frag_color = object_color;

	if (moveLeft == 1) {
		texcoord = vec2(texcoord.x - time / 100, texcoord.y);
	} else if (moveLeft == 0) {
		texcoord = vec2(texcoord.x + time / 100, texcoord.y);
	}

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}