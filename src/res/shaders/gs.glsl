#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout (points) in;
layout (triangle_strip, max_vertices = 100) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float r;
uniform int i;

void build_cone(vec4 position, int interations, float rad, float h)
{
    fColor = gs_in[0].color; // gs_in[0] since there's only one input vertex
    for(int i = 0; i<=interations+1; i++){
        float angle = i*(2*M_PI/interations);

        gl_Position = projection * view * model * (position + vec4(cos(angle)*rad, 0.0, sin(angle)*rad, 0.0));
        EmitVertex();
        gl_Position = projection * view * model * (position + vec4(0,h,0,0));
        EmitVertex();

    }
}

void main() {
	build_cone(gl_in[0].gl_Position, i, .1, .1);
}