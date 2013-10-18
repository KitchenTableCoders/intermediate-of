#pragma once

#include "ofMain.h"

#define NUM_BALLS 5
#define BLOCK_SIZE 4

class Ball {
public:
    float radius;
    ofPoint pos;
    ofPoint vel;
    void draw() {
        ofCircle(pos, radius);
    }
    void update() {
        pos += vel;
 
        if(pos.x > ofGetWidth()-radius) {
            pos.x = ofGetWidth()-radius;
            vel.x *= -1;
        }
        if(pos.x < radius) {
            pos.x = radius;
            vel.x *= -1;
        }
        if(pos.y > ofGetHeight()-radius) {
            pos.y = ofGetHeight()-radius;
            vel.y *= -1;
        }
        if(pos.y < radius) {
            pos.y = radius;
            vel.y *= -1;
        }
    }
};

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        Ball balls[NUM_BALLS];
};
