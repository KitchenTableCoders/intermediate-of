#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetFullscreen(true);
    ofSetCircleResolution(100);
    ofBackgroundGradient(ofColor::black, ofColor::white);
    
    n = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    
    mouseSpeed = ofDist(mouse.x, mouse.y, pmouse.x, pmouse.y);
    pmouse.set(mouse);
    
    mouseSpeedEased += (mouseSpeed-mouseSpeedEased)/10.0;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    for(int i=0; i<NUM_POINTS; i++) {
        ofSetColor(colors[i]);
        ofCircle(points[i], radii[i]);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    colors[n].set(ofRandom(255), ofRandom(255), ofRandom(255));
    radii[n] = ofRandom(10, 50);
    points[n].set(ofRandomWidth(), ofRandomHeight());
    
    ++n %= NUM_POINTS;
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    mouse.set(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    mouse.set(x, y);
    
    colors[n].set(ofRandom(255), ofRandom(255), ofRandom(255));
    radii[n] = mouseSpeedEased;
    points[n].set(x, y);
    
    ++n %= NUM_POINTS;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    colors[n].set(ofRandom(255), ofRandom(255), ofRandom(255));
    radii[n] = ofRandom(10, 50);
    points[n].set(x, y);
    
    ++n %= NUM_POINTS;
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
