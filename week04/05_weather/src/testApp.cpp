#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofRegisterURLNotification(this);

    font.loadFont("frabk.ttf", 48);
    
    ofLoadURLAsync("http://api.wunderground.com/api/c7c1fbefd0d9e77d/geolookup/q/autoip.json", "autoip");
}

//--------------------------------------------------------------
void testApp::urlResponse(ofHttpResponse & response){
	if(response.status==200) {

        ofxJSONElement json;
        if( json.parse( response.data.getText() ) )
        {
            if( response.request.name == "autoip")
            {
                if(json.isMember("location")) {
                    state = json["location"]["state"].asString();
                    city = json["location"]["city"].asString();
                    heading =city+", "+state;
                    
                    getConditions();
                } else {
                    ofLogError() << "No location found in autoip response";
                }
            }
            else if(response.request.name == "conditions")
            {
                float temperature = json["current_observation"]["temp_f"].asFloat();
                ofLogNotice("temperature") << temperature;
                float hue = ofMap(temperature, -10, 110, 117, 255);
                bg.setHsb(hue, 255, 255);
                string icon_url = json["current_observation"]["icon_url"].asString();
                icon.loadImage(icon_url);
            }
        }
        else {
            ofLogError() << "Couldn't parse json";
        }
        
	} else {
		ofLogError() << response.status << " " << response.error << endl;
	}
}

//--------------------------------------------------------------
void testApp::getConditions() {
    string conditions_url = "http://api.wunderground.com/api/c7c1fbefd0d9e77d/conditions/q/"+state+"/"+city+".json";
    ofLoadURLAsync(conditions_url, "conditions");
}

//--------------------------------------------------------------
void testApp::exit() {
    ofUnregisterURLNotification(this);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(bg);

    ofSetColor(0);
    font.drawString(heading, 10, 55);
    
    if(icon.isAllocated())
    {
        ofSetColor(255);
        icon.draw(font.getStringBoundingBox(heading,0,0).width+20, 18);
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
