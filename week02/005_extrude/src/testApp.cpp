#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(24);
    ofBackground(0);
    ofSetSmoothLighting(true);
    
    bDrawWireframe = false;
    
    
    // Point lights emit light in all directions //
    pointLight.setPointLight();
    
    // set the diffuse color, color reflected from the light source //
    pointLight.setDiffuseColor(ofColor(255, 255, 255));
    
    // specular color, the highlight/shininess color //
	pointLight.setSpecularColor(ofColor(0, 0, 255));
    
    pointLight.enable();
    
    
    
    // turn the light into spotLight, emit a cone of light //
    spotLight.setSpotlight();
    spotLight.setDiffuseColor( ofColor(255.f, 0.f, 0.f));
	spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    
    // size of the cone of emitted light, angle between light axis and side of cone //
    // angle range between 0 - 90 in degrees //
    spotLight.setSpotlightCutOff( 45 );
    
    // rate of falloff, illumitation decreases as the angle from the cone axis increases //
    // range 0 - 128, zero is even illumination, 128 is max falloff //
    spotLight.setSpotConcentration( 0 );
    
    spotLight.enable();
    
    
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
    float halfDepth = depth/2;
    
    // Create a bunch of Letter objects
    vector<ofPath> letters = font.getStringAsPoints(text);
    for(int i=0; i<letters.size(); i++)
    {
        // Tessellation is subdividing a concave polygon into convex polygons.
        ofMesh front = letters[i].getTessellation();
        ofMesh back = front;
        ofMesh side;
        
        // Loop through all of the vertices in the "back" mesh
        // and move them back in on the "z" axis
        vector<ofPoint>& f = front.getVertices();
        vector<ofPoint>& b = back.getVertices();
        for(int j=0; j< f.size(); j++)
        {
            f[j].z += halfDepth;
            b[j].z -= halfDepth;
        }
        
        // NORMALS!
        for(int i=0; i<front.getNumVertices(); i++)
        {
            front.addNormal(ofVec3f(0, 0, 1));
        }
        
        for(int i=0; i<back.getNumVertices(); i++)
        {
            back.addNormal(ofVec3f(0, 0, -1));
        }
        
        // TIP - class heirarchy
        // an ofPath is basically a container for a bunch of ofPolyLines
        // an ofPolyline is a single, continuous line that has lots of useful functions
        // such as getSmoothed, getResampledBySpacing, getClosestPoint
        
        vector<ofPolyline> lines = letters[i].getOutline();
        for(int j=0; j<lines.size(); j++)
        {
            vector<ofPoint>& points = lines[j].getVertices();
            for(int k=0; k<points.size(); k++)
            {
                ofPoint p1 = points[(k+0)%points.size()];
                ofPoint p2 = points[(k+1)%points.size()];
                
                side.addVertex(ofPoint(p1.x, p1.y, p1.z+halfDepth));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z+halfDepth));
                side.addVertex(ofPoint(p1.x, p1.y, p1.z-halfDepth));
                
                side.addColor(ofColor::white);
                side.addColor(ofColor::white);
                side.addColor(ofColor::white);
                
                side.addVertex(ofPoint(p1.x, p1.y, p1.z-halfDepth));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z-halfDepth));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z+halfDepth));
                
                side.addColor(ofColor::white);
                side.addColor(ofColor::white);
                side.addColor(ofColor::white);
            }
        }

        
        meshes.push_back(side);
        meshes.push_back(front);
        meshes.push_back(back);
    }
}

//--------------------------------------------------------------
void testApp::update(){
    float x = (ofGetWidth()/2.0) + cos(ofGetElapsedTimef()*.6f) * (ofGetWidth()/3.0);
    pointLight.setPosition(x, ofGetHeight()/2.0, 100);
    
    spotLight.setOrientation( ofVec3f( 0, cos(ofGetElapsedTimef()) * RAD_TO_DEG, 0) );
	spotLight.setPosition( mouseX, mouseY, 100);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::black);
    
    glEnable(GL_DEPTH_TEST);
    ofEnableLighting();
    cam.begin();
    {
        ofPushMatrix();
        {
            //ofScale(1, -1);
            ofTranslate(-(bb.getWidth()/2.0), (bb.getHeight()/2.0));
        
            for(int i=0; i<meshes.size(); i++)
            {
                if(bDrawWireframe) {
                    meshes[i].drawWireframe();
                } else {
                     meshes[i].draw();
                }
            }
        }
        ofPopMatrix();
    }
    cam.end();
    
    spotLight.draw();
    pointLight.draw();
    
    ofDisableLighting();
    glDisable(GL_DEPTH_TEST);
    
    
    ofSetColor(200, 0, 100);
    stringstream message;
    message << "DRAG YOUR MOUSE!" << endl;    message << "(w) bDrawWireframe: " << (bDrawWireframe ? "on" : "off") << endl;
    ofDrawBitmapString(message.str(), 10, ofGetHeight()-40);
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
