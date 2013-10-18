#include "testApp.h"

// not polluting the global namespace
void testApp::drawSnowman()
{
    ofPushStyle();
    
    // Head
    ofFill();
    ofSetColor(255,255,255);
    ofCircle(50, 50, 25);
    ofCircle(50, 90, 30);
    ofCircle(50, 160, 50);
    
    // Eyes & Buttons
    ofSetColor(0, 0, 0);
    ofCircle(42, 43, 4);
    ofCircle(57, 43, 4);
    ofCircle(50, 80, 3);
    ofCircle(50, 100, 3);
    ofCircle(50, 120, 3);
    
    // Nose
    ofSetHexColor(0xED9121);
    ofTriangle(45, 51, 55, 51, 50, 65);
    
    //Arms
    ofSetHexColor(0x7B3F00);
    ofSetLineWidth(3);
    ofLine(76, 85, 101, 75);
    ofLine(96, 78, 97, 65);
    ofLine(96, 79, 102, 85);
    ofLine(24, 86, -3, 77);
    ofLine(2, 80, 4, 68);
    
    // Hat
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(0, 0, 0);
    ofRect(50, 25, 50, 5);
    ofRect(50, 15, 30, 20);
    
    ofPopStyle();
}

void drawBoat()
{
    ofPushStyle();
    ofFill();
    
    // Hull
    ofSetHexColor(0x603311);
    ofCurve(800, -400, 50, 200, 400, 200, 200, -400);
    
    // Mast
    ofRect(200, 0, 10, 200);
    
    // Flag
    ofSetColor(0, 0, 0);
    ofRect(100, 0, 100, 60);
    
    ofPopStyle();
}

void drawWater()
{
    ofPushStyle();
    
    ofSetColor(0, 100, 255);
    
    for(int i=0; i<ofGetWidth(); i++)
    {
        float height = 20 * cos(i/30.0) + 40;
        ofRect(i, 0, 5, height);
    }
    
    ofPopStyle();
}


//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(24);
    
    boatPos.x = 30;
    boatPos.y = 450;
    
    snowmanPos.x = 20;
    snowmanPos.y = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    angle += 5;
    
    snowmanPos.x = 150 + cos(ofGetFrameNum()/20.0) * 150;
    
    boatPos.x += 5;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofPushMatrix();
    
    ofTranslate(boatPos.x, boatPos.y);
    
    ofPushMatrix(); // save the matrix state
    ofTranslate(snowmanPos.x, snowmanPos.y);
    drawSnowman();
    ofPopMatrix(); // restore matrix state
    
    drawBoat();
    
    ofPopMatrix();
    
    
    
    ofPushMatrix();
    ofTranslate(0, ofGetHeight());
    ofScale(1, -1);
    drawWater();
    ofPopMatrix();

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
