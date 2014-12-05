#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    mesh.addVertex(ofVec3f(0, 0, 0));
    mesh.addVertex(ofVec3f(-100, 100, 0));
    mesh.addVertex(ofVec3f(100, 100, 0));
    mesh.disableColors();
    frame.getMesh() = mesh;
    child.getMesh() = mesh;
    child.setPosition(100, 100, 0);
    child.setParent(frame);
    
    ofRectangle
}

//--------------------------------------------------------------
void ofApp::update(){
    frame.setPosition(ofGetMouseX(), 240, 0  );

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::black);

    frame.drawWireframe();
    child.drawWireframe();
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
