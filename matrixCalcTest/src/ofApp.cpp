#include "ofApp.h"
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

//--------------------------------------------------------------
void ofApp::setup(){

    
    ofMatrix4x4 ofModel, ofView;
    
    /********* oF **********/
    ofModel.makeIdentityMatrix();
    ofModel.translate(0.5, -0.4, -2.2);
    ofView.makeLookAtViewMatrix(ofVec3f(0,0,-5), ofVec3f(1.3, -1.4 ,2.0 ), ofVec3f(0,1,0));
    // vec * mat
    ofVec4f oFlightPos = ofVec4f(1.0, 2.0, -3.0, 1.0);

    oFlightPos =  oFlightPos * ofView; // light * view
    ofMatrix4x4 ofResult =  ofModel*ofView; // model * view
    
    
    /********* glm **********/
    mat4 glmModel, glmView;
    glmModel = mat4(1.0); // identity matrix;
    glmModel = glm::translate(glmModel, vec3(0.5, -0.4, -2.2));
    glmView = glm::lookAt(vec3(0.0, 0.0, -5.0), vec3(1.3,-1.4,2.0), vec3(0, 1, 0));
    
    // vec * mat
    vec4 glmLightPos = vec4(1.0, 2.0, -3.0, 1.0);
    glmLightPos = glmView * glmLightPos; //  view * lightPos
    mat4 glmResult =  glmView * glmModel; // view * model
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j ++){
            float *p = ofResult.getPtr();
            ofLog() <<"of :" << i << ' ' << j << ": "<< p[i*4 +j];
            ofLog() <<"glm:" << i << ' ' << j << ": "<< glmResult[i][j];
        }
    }
    
    for(int i = 0 ;i < 4; i++){
        ofLog() <<"of :" << i << " " << oFlightPos[i];
        ofLog() <<"glm:" << i << " " << glmLightPos[i];

    }
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
