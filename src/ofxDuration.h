#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#include "ofxDurationTrack.h

class ofxDuration : public ofxOscReceiver {
  public:
	ofxDuration();
	virtual void setup(int port);
	virtual void draw();

    virtual float getValueForTrack(string trackName);
    virtual bool getBoolForTrack(string trackName);
    int getNumTracks();
    
	vector<string>& getTracks();
		
	void drawDebug();
	void setupFont(string fontPath, int fontSize);
	
  protected:
	bool isSetup;
    ofTrueTypeFont font;
    void update(ofEventArgs& args);
	
	vector<string> trackNames;
    map<string, ofxDurationTrack> tracks;
};