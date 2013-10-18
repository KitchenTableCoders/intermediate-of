#pragma once

#include "ofMain.h"
#include "ofxLibWebsockets.h"

class Line {
public:
    void draw() {
        ofPushStyle();
        ofSetColor(color);
        ofNoFill();
        ofBeginShape();
        for(auto& vert : verts)
            ofVertex(vert.x, vert.y);
        ofEndShape();
        ofPopStyle();
    }
    void reset() {
        color.setHsb(ofRandom(255), 255, 255);
        verts.clear();
    }
    string serialize() {
        Json::Value line;
        line["color"]["r"] = color.r;
        line["color"]["g"] = color.g;
        line["color"]["b"] = color.b;
        for(int i=0; i<verts.size(); i++) {
            line["verts"][i]["x"] = (int)verts[i].x;
            line["verts"][i]["y"] = (int)verts[i].y;
        }
        
        Json::StyledWriter writer;
        return writer.write( line );
    }
    
    string unserialize(Json::Value line) {

        color.r = line["color"]["r"].asInt();
        color.g = line["color"]["g"].asInt();
        color.b = line["color"]["b"].asInt();
        for(int i=0; i<line["verts"].size(); i++) {
            float x = line["verts"][i]["x"].asInt();
            float y = line["verts"][i]["y"].asInt();
            verts.push_back( ofPoint(x, y) );
        }
    }
    
    ofColor color;
    vector<ofPoint> verts;
};


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofxLibwebsockets::Client client;
        
        // websocket methods
        void onConnect( ofxLibwebsockets::Event& args );
        void onOpen( ofxLibwebsockets::Event& args );
        void onClose( ofxLibwebsockets::Event& args );
        void onIdle( ofxLibwebsockets::Event& args );
        void onMessage( ofxLibwebsockets::Event& args );
        void onBroadcast( ofxLibwebsockets::Event& args );
    
    
        Line drawing;
        vector<Line> lines;
};
