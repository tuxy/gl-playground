#version 330 core
in vec3 color;
in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
        // FragColor = mix(texture(texture1, texCoords), texture(texture2, texCoords), 0.2);
        FragColor = vec4(color, 1.0f);
}
