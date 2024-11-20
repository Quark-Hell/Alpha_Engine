#version 450
layout(location = 0) in vec3 vertex_position;

out vec3 texCoords;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

void main(){
	texCoords = vec3(vertex_position.x, vertex_position.y, -vertex_position.z);
	vec4 pos = projection_matrix * view_matrix * vec4(vertex_position, 1.0);
	gl_Position = pos.xyww;
}