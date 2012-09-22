
#pragma once

#include "ofMain.h"
#include "ofRange.h"

class ofxDurationTrack {
  public:
	ofxDurationTrack(){
		lastUpdatedTime = 0;
		on = false;
		value = 0;
		range = ofRange(0,1.0);
		color = ofColor(0,0,0);
	}
	
    string type;
    string name;
	float lastUpdatedTime;
	string flag; //for flags
    bool on; //for switches
    float value; //for Curves
	ofRange range; //for Curves
	ofColor color; //for Colors
};