#version 450
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec3 vertex_color;
layout(location = 3) in vec2 vertex_tex_coords;

out vec3 color;
out vec3 normal;
out vec3 frag_Pos;
out vec2 texCoords;

uniform mat4 MVP;
uniform mat4 model_matrix;
uniform mat3 trans_model_mat;

void main() {
   color = vertex_color;
   texCoords = vertex_tex_coords;

   gl_Position = MVP * vec4(vertex_position, 1.0f);
   frag_Pos = vec3(model_matrix * vec4(vertex_position, 1.0f));
   normal = trans_model_mat * vertex_normal;
}