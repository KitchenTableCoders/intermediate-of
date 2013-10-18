#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(24);
    ofBackground(0);
    
    bDrawWireframe = false;
    
    // Load the font
    string filename = "planet_kosmos.ttf";
    int fontSize = 90;
    bool bAntiAliased = false;
    bool bFullCharacterSet = true;
    bool makeContours = true;
    float simplifyAmt = 30; // uses ofPolyline::simplify
    font.loadFont(filename, fontSize, bAntiAliased, bFullCharacterSet, makeContours, simplifyAmt);
    font.setLineHeight(fontSize+10);
    
    
    
    // Get the bounding box of the text
    text = "Kitchen\nTable\nCoders";
    bb = font.getStringBoundingBox(text, 0, 0);
    
    float depth = 20;
    
    // Create a bunch of Letter objects
    vector<ofPath> letterPaths = font.getStringAsPoints(text);
    for(int i=0; i<letterPaths.size(); i++)
    {
        // Tessellation is subdividing a concave polygon into convex polygons.
        ofMesh front = letterPaths[i].getTessellation();
        ofMesh back = front;
        
        // Loop through all of the vertices in the "back" mesh
        // and move them back in on the "z" axis
        vector<ofPoint>& f = front.getVertices();
        vector<ofPoint>& b = back.getVertices();
        for(int j=0; j< f.size(); j++)
        {
            f[j].z += depth/2.0;
            b[j].z -= depth/2.0;
        }
        
        meshes.push_back(front);
        meshes.push_back(back);
    }
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::black);
    
    glEnable(GL_DEPTH_TEST);
    ofPushMatrix();
    {
        ofTranslate((ofGetWidth()/2.0), (ofGetHeight()/2.0));
        ofRotateX(ofGetFrameNum() * 3);
        ofTranslate(-(bb.getWidth()/2.0), (bb.getHeight()/2.0));
        
        for(int i=0; i<meshes.size(); i++)
        {
            ofSetColor(200, 0, 100);
            meshes[i].draw();
            
            if(bDrawWireframe)
            {
                ofSetColor(0);
                meshes[i].drawWireframe();
            }
        }
    }
    ofPopMatrix();
    glDisable(GL_DEPTH_TEST);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key=='w') {
        bDrawWireframe = !bDrawWireframe;
    }
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
