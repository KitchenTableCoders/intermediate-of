#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    
    for(int i=0; i<NUM_BALLS; i++) {
        balls[i].radius = ofRandom(90, 200);
        balls[i].pos.x = ofRandom(balls[i].radius, ofGetWidth()-balls[i].radius);
        balls[i].pos.y = ofRandom(balls[i].radius, ofGetHeight()-balls[i].radius);
        balls[i].vel.set(ofRandom(-2, 2), ofRandom(-2, 2));
    }
    

}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    for(int i=0; i<NUM_BALLS; i++) {
        balls[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofFill();
    ofSetColor(255, 0, 0);
    
    for(int y=0; y<ofGetHeight(); y+=BLOCK_SIZE) {
        for(int x=0; x<ofGetWidth(); x+=BLOCK_SIZE) {
        
            float strength = 0;
            for(int i=0; i<NUM_BALLS; i++) {
                float dist = ofDist(balls[i].pos.x, balls[i].pos.y, x+(BLOCK_SIZE/2), y+(BLOCK_SIZE/2));
                strength += ofMap(dist, 0, balls[i].radius, 100, 0, true);
            }
     
            if(strength>50)
                ofRect(x, y, BLOCK_SIZE, BLOCK_SIZE);
           
            //ofNoFill();
            //ofRect(x, y, BLOCK_SIZE, BLOCK_SIZE);
        }
    }
    
    ofNoFill();
    ofSetColor(0);
    for(int i=0; i<NUM_BALLS; i++) {
        //balls[i].draw();
    }
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
