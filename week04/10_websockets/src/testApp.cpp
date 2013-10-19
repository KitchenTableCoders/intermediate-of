#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  
    char myhost[255];
    gethostname(myhost, (size_t)sizeof(myhost));
    hostname = string(myhost);
    
    
    ofxLibwebsockets::ClientOptions options = ofxLibwebsockets::defaultClientOptions();
    options.port = 8080;
    bool connected = client.connect( options );

    client.addListener(this);
}

//--------------------------------------------------------------
void testApp::exit(){
	client.close();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    drawing.draw();
    for(int i=0; i<lines.size(); i++) {
        lines[i].draw();
    }
}


//--------------------------------------------------------------
void testApp::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void testApp::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"on open"<<endl;
}

//--------------------------------------------------------------
void testApp::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
}

//--------------------------------------------------------------
void testApp::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void testApp::onMessage( ofxLibwebsockets::Event& args ){

    Json::Value json;
    Json::Reader reader;
    if ( !reader.parse( args.message, json ) ) {
        std::cout  << "Failed to parse json\n" << reader.getFormattedErrorMessages();
        return;
    }
    
    if(json["route"]=="addline") {
        ofLogNotice() << "received line";
        Line line;
        line.unserialize( json["line"] );
        lines.push_back(line);
    }
    if(json["route"]=="removeline") {
        for(int i=0; i<lines.size(); i++) {
            if(lines[i]._id == json["id"].asString()) {
                lines.erase(lines.begin()+i);
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if (key=='c') {
        for(int i=0; i<lines.size(); i++) {
            Json::Value message;
            message["route"] = "removeline";
            message["id"] = lines[i]._id;
            
            Json::StyledWriter writer;
            client.send( writer.write( message ) );
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    drawing.verts.push_back( ofPoint(x,y) );
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    drawing.reset();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    //ofLogNotice() << drawing.serialize();
    
    Json::Value message;
    message["route"] = "addline";
    message["line"] = drawing.serialize();
    
    ofLogNotice() << "sending line";
    Json::StyledWriter writer;
    client.send( writer.write( message ) );
    
    drawing.reset();
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
