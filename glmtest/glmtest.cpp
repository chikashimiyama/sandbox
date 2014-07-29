#define  GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

using namespace glm;
using namespace std;
int main(){

	mat4 view;
    vec3 kd = vec3(0.9, 0.5, 0.3);
    vec3 ld = vec3(1.0, 1.0, 1.0);
    vec4 lightPoisition = vec4(5.0f, 5.0f, -5.0f, 1.0f);

    mat4 modelMatrix = mat4(1.0);
	mat4 viewMatrix = mat4
    vec3 VertexNormal = mat3(vec3(mv[0]), vec3(mv[1]),vec3(mv[2]));
    vec4 modelViewMatrix =
    vec4 VertexPosition ~;


 	vec3 tnorm = normalize(normalMatrix * VertexNormal);
    vec4 eyeCoords = modelViewMatrix * vec4(VertexPosition, 1.0);
    vec3 s = normalize(vec3(lightPoisition - eyeCoords)); 
    vec3 LightIntensity = ld * kd * max(dot(s, tnorm), 0.0);
    cout << LightIntensity[0] << " " << LightIntensity[1] << " " LightIntensity[2] << end;
	
	return 0;
}