#version 450
layout(location = 0) in vec3 vertex_position;
layout(location = 3) in vec2 vertex_tex_coords;

out vec2 TexCoords;
out vec3 frag_Pos;

uniform mat4 model_matrix;
uniform mat4 MVP;

void main() {
    TexCoords = vertex_tex_coords;

    frag_Pos = vec3(model_matrix * vec4(vertex_position, 1.0f));
    gl_Position = MVP * vec4(vertex_position, 1.0f);
}
