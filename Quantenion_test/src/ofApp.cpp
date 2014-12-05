#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camera.setPosition(0, 0, -100);
    camera.lookAt(ofVec3f(0, 0, 0));

}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::black);
    prim.setPosition(0, 0, 0);
    prim.set(30);
    
    
    camera.begin();
    prim.drawWireframe();
    
    camera.end();
    
    ofDrawBitmapString(ofToString(prim.getOrientationEuler()), 5, 20);
    ofDrawBitmapString(ofToString(prim.getOrientationQuat().asVec3()), 5, 40);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    prim.setOrientation(ofVec3f(x , 0, 0));

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
