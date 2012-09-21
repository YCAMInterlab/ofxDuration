
#pragma once

#include "ofMain.h"
#include "ofRange.h"

class ofxDurationTrack {
  public:
    string type;
    string name;
	float lastUpdatedTime;
	string flag; //for flags
    bool on; //for switches
    float value; //for Curves
	ofRange range; //for Curves
	ofColor color; //for Colors
};