
#include "ofMain.h"

class ofxDuration;
class ofxDurationTrack;

class ofxDurationEventArgs : public ofEventArgs {
 public:
	ofxDuration* duration;
	ofxDurationTrack* track;
};

class ofxDurationEvents {
  public:
	ofEvent<ofxDurationEventArgs> trackUpdated;
};