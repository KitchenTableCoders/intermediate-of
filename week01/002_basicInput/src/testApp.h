#pragma once

#include "ofMain.h"

#define NUM_POINTS 200

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
    
        
        int n;
    
        // TO DO:  Convert these individual arrays to a class
        // TO DO:  Use a vector instead of array
        // TO DO:  z sorting?
        ofPoint points[NUM_POINTS];
        ofColor colors[NUM_POINTS];
        float radii [NUM_POINTS];

    
        ofPoint mouse;
        ofPoint pmouse;
        float mouseSpeed, mouseSpeedEased;
};
