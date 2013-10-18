#include "testApp.h"

/**
 *  TO DO:  Framerate is too slow!  How can we increase it?
 */

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetWindowShape(800, 600);
    
    
    theCount.loadImage("images/count.png");
    //cam.initGrabber(320, 240);
}

//--------------------------------------------------------------
void testApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    angle += 5;
    //cam.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofTranslate(ofGetWidth()/2.0, ofGetHeight()/2.0);
    ofRotateX(angle);
    ofTranslate(-theCount.getWidth()/2.0, -theCount.getHeight()/2.0);
    
    
    ofSetColor(255);
    
    
    
    //theCount.draw(20, 20);
    ofPixels pix = theCount.getPixelsRef();
    for(int y=0; y<pix.getHeight(); y++)
    {
        for(int x=0; x<pix.getWidth(); x++)
        {
            ofColor c = pix.getColor(x, y);
            float b = c.getBrightness();
            float z = ofMap(b, 0, 255, -100, 100);
            
            ofSetColor(c);
            ofRect(x, y, z, 1, 1);
        }
    }
    
    
    /*
     // an array of unsigned chars that is widht*height*nChannels
     unsigned char* pix = cam.getPixels();
     for(int y = 0; y<cam.getHeight(); y++)
     {
         for(int x=0; x<cam.getWidth(); x++)
         {
             int i = (y * cam.getWidth() + x) * 3;
             int r = pix[i + 0];
             int g = pix[i + 1];
             int b = pix[i + 2];
             //int a = pix[i + 3];
             int bri = (r + g + b) / 3.0;
             int z = ofMap(bri, 0, 255, -100, 100);
             
             ofSetColor(r, g, b);
             ofRect(x, y, z, 1, 1);
         }
     }
     */
    
    
    //ofSetColor(255, 0, 0, 100);
    //ofRect(200, 200, 500, 80);
    //ofDisableAlphaBlending();
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
