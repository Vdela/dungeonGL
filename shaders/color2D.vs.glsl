#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

uniform mat3 uModelMatrix; // matrice de transformations

out vec3 vFragColor;

void main() {
  vFragColor = aVertexColor;
  //gl_Position = vec4(aVertexPosition, 0, 1);
  gl_Position = vec4( (uModelMatrix * vec3(aVertexPosition,1)).xy , 0, 1);
}
