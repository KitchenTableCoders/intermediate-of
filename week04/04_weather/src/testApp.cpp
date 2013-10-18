#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    font.loadFont("frabk.ttf", 48);
    
    ofxJSONElement geolookup;
    geolookup.open("http://api.wunderground.com/api/c7c1fbefd0d9e77d/geolookup/q/autoip.json");
    
    string state = geolookup["location"]["state"].asString();
    string city = geolookup["location"]["city"].asString();
    heading =city+", "+state;
    
    string conditions_url = "http://api.wunderground.com/api/c7c1fbefd0d9e77d/conditions/q/"+state+"/"+city+".json";
    ofxJSONElement conditions;
    conditions.open(conditions_url);
    
    float temperature = conditions["current_observation"]["temp_f"].asFloat();
    ofLogNotice("temperature") << temperature;
    float hue = ofMap(temperature, -10, 110, 117, 255);
    bg.setHsb(hue, 255, 255);
    
    
    
    string icon_url = conditions["current_observation"]["icon_url"].asString();
    icon.loadImage(icon_url);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(bg);

    ofSetColor(0);
    font.drawString(heading, 10, 55);
    
    ofSetColor(255);
    icon.draw(font.getStringBoundingBox(heading,0,0).width+20, 18);
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
