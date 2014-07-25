#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    camera.setPosition(0,0, -20);
    camera.lookAt(ofVec3f(0,0,0));
    ofVec3f vert[3];
    ofFloatColor col[3];
    
    vert[0] = ofVec3f(-5,-5,0);
    vert[1] = ofVec3f(0,5,0);
    vert[2] = ofVec3f(5,-5,0);

    col[0] = ofFloatColor(1.0, 0.0, 0.0);
    col[1] = ofFloatColor(0.0, 1.0, 0.0);
    col[2] = ofFloatColor(0.0, 0.0, 1.0);

    int vertId, colorId;
    vbo.setVertexData(vert, 3, GL_DYNAMIC_DRAW);
    vbo.setColorData(col,3, GL_DYNAMIC_DRAW);
    vertId =vbo.getVertId();
    colorId = vbo.getColorId();
    
    shader.load("shader");
    shader.setAttribute1s(<#GLint location#>, <#short v1#>)
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.begin();
    shader.begin();
    vbo.draw(GL_TRIANGLE_STRIP, 0, 3);
    shader.end();
    camera.end();
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
