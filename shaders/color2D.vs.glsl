#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

uniform mat4 uModelMatrix; // matrice de transformations

out vec3 vFragColor;

void main() {
  vFragColor = aVertexColor;
  //gl_Position = vec4(aVertexPosition, 0, 1);
  //gl_Position = vec4( uModelMatrix * vec4(aVertexPosition,1), 1);

  gl_Position = uModelMatrix * vec4(aVertexPosition, 1); //here

  //gl_Position = vec4( (uModelMatrix * vec4(aVertexPosition,1)).xyz, 1);
  //gl_Position = vec4( (uModelMatrix * vec3(aVertexPosition)), 1);
  //gl_Position = vec4( (uModelMatrix * vec3(aVertexPosition,1)).xy , 0, 1);


}
