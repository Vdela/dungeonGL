#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform sampler2D uTexture;
uniform vec3 uLightPos;
uniform vec3 uLightIntensity;

out vec3 fFragColor;


void main() {
    fFragColor = texture( uTexture, vTexCoords ).rgb;
    vec3 ray = uLightPos - vPosition_vs;
    float angle = dot(vNormal_vs, ray);
    float distanceSqr = dot(ray, ray);
    fFragColor = fFragColor * angle * uLightIntensity;
    fFragColor = fFragColor * (1 / distanceSqr);
}


