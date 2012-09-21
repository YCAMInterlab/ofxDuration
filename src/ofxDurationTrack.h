
#pragma once

#include "ofMain.h"
#include "ofRange.h"

class ofxDurationTrack {
  public:
    string name;
    string type;
    bool on;
    float value;
	ofColor color;
	ofRange range;	
};