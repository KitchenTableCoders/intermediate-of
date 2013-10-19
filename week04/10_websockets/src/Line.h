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
    
    Line() {
       ofAddListener(ofEvents().mouseMoved, this, &Line::mouseMoved);
        bMouseOver = false;
    }
    
    void mouseMoved(ofMouseEventArgs& event){
        if(verts.size()==0) return;
        ofPoint& last = verts.back();
        bMouseOver = ofDist(event.x, event.y, last.x, last.y) < 50;
    }
    
    void draw() {
        ofPushStyle();
        ofSetColor(color);
        ofNoFill();
        ofBeginShape();
        for(auto& vert : verts)
            ofVertex(vert.x, vert.y);
        ofEndShape();
        
        if(bMouseOver && verts.size()>0) {
            ofDrawBitmapString(hostname, verts[verts.size()-1]);
        }
        ofPopStyle();
    }
    
    void reset() {
        color.setHsb(ofRandom(255), 255, 255);
        verts.clear();
    }
    
    Json::Value serialize() {
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
        return line;
    }
    
    void unserialize(Json::Value line) {
        _id = line["_id"].asString();
        hostname = line["hostname"].asString();
        color.r = line["color"]["r"].asInt();
        color.g = line["color"]["g"].asInt();
        color.b = line["color"]["b"].asInt();
        for(int i=0; i<line["verts"].size(); i++) {
            float x = line["verts"][i]["x"].asInt();
            float y = line["verts"][i]["y"].asInt();
            verts.push_back( ofPoint(x, y) );
        }
    }
    
    bool bMouseOver;
    string _id;
    string hostname;
    ofColor color;
    vector<ofPoint> verts;
};

