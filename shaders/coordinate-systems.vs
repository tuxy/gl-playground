#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
// layout (location = 2) in vec3 aColor;

// out vec3 color;
out vec2 texCoords;

uniform mat4 transform;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
        gl_Position = proj * view * model * transform * vec4(aPos, 1.0f);
        // color = aColor;
        texCoords = aTexCoords;
}
