#define  GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

using namespace glm;
using namespace std;
int main(){

	vec3 sampleVertex(0.0, 0.0, 0.0); // in the center 
    vec3 sampleNormal(0, 0, -1.0); // face straight against camera


    vec3 kd = vec3(1.0, 1.0, 1.0);
    vec3 ld = vec3(1.0, 1.0, 1.0);

    mat4 modelMatrix = mat4(1.0);
	mat4 viewMatrix = glm::lookAt(vec3(0,0,-5.0), vec3(0,0,0), vec3(0,1,0));

    mat4 mv = viewMatrix * modelMatrix; // model view
    vec4 lightPoisition = viewMatrix * vec4(5.0f, 5.0f, -5.0f, 1.0f);
    mat3 normalMatrix = mat3(vec3(mv[0]), vec3(mv[1]),vec3(mv[2]));

    // in GLSL
 	vec3 tnorm = normalize(normalMatrix * sampleNormal);
    vec4 eyeCoords = mv * vec4(sampleVertex, 1.0);
    vec3 s = normalize(vec3(lightPoisition - eyeCoords)); 
//    vec3 LightIntensity = ld * kd * max(dot(s, tnorm), 0.0);
    vec3 LightIntensity = ld * kd * dot(s, tnorm);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << i << " " << j << ":" << normalMatrix[i][j] << endl; 
        }
    }
    cout << "lightPos:"<< lightPoisition[0] << " " << lightPoisition[1] << " " << lightPoisition[2] << " " << lightPoisition[3] << endl;
    cout << "result:" << LightIntensity[0] << " " << LightIntensity[1] << " " << LightIntensity[2] << endl;
	
	return 0;
}