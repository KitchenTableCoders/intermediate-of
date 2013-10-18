#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // Set up our application
    ofSetFrameRate(60);
    ofSetWindowShape(800, 600);
    ofBackground(240, 230, 180); // set background to beige
    ofSetCircleResolution(100);
    
    
    // Initialize some variables
    circlePos.x = 0;
    circlePos.y = 300.0;
    radius = 20.0;
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle("fps: "+ofToString(ofGetFrameRate()));
    
    radius = 30 + cos(ofGetFrameNum()/10.0) * 50;    // modulate the radius 10 to 50
    circlePos.x += 50.0 * ofGetLastFrameTime();       // Move to the right 20px/sec
    
    // If the circle moves beyond the right side of the screen, pacman
    if(circlePos.x > ofGetWidth()+radius) {
        circlePos.x = -radius;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 0, 255);    // Set the drawing color
    ofCircle(circlePos.x, circlePos.y, radius);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
