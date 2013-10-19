//
//  Line.h
//  websockets
//
//  Created by Jeffrey Crouse on 10/18/13.
//
//

#pragma once
#include "ofMain.h"

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
        char myhost[255];
        gethostname(myhost, (size_t)sizeof(myhost));
        
        Json::Value line;
        line["hostname"] = string(myhost);
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

