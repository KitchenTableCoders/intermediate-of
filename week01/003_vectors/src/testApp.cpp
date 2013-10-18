#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofNoFill();
    
    
    int nPoints = 20;
    float innerRadius = 20;
    float outerRadius = 40;
    bool useInner = true;
    ofBeginShape();
    for(int i=0; i<nPoints; i++)
    {
        float angle = ofMap(i, 0, nPoints, 0, 2*3.141596);
        float radius = (useInner) ? innerRadius : outerRadius;
        float x = 100 + cos(angle) * radius;
        float y = 100 + sin(angle) * radius;
        ofVertex(x, y);
        useInner = !useInner;
    }
    ofEndShape(true);
    
    
    
    ofBeginShape();
    for(int i=0; i<points.size(); i++)
    {
        ofVertex(points[i].x, points[i].y);
    }
    ofEndShape();
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
    ofPoint p;
    p.x = x;
    p.y = y;
    
    
    points.push_back( p );
    
    
    cout << "nPts: " << points.size() << endl;
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
