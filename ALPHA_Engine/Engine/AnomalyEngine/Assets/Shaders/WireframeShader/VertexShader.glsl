#version 460
layout(location = 0) in vec3 vertex_position;

out vec3 frag_Pos;

uniform mat4 model_matrix;
uniform mat4 trans_model_mat;
uniform mat4 MVP;

void main() {
   gl_Position = MVP * vec4(vertex_position, 1.0f);
   frag_Pos = vec3(model_matrix * vec4(vertex_position, 1.0f));
}