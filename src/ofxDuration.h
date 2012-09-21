#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxDurationEvents.h"
#include "ofxDurationTrack.h"

class ofxDuration : public ofxOscReceiver {
  public:
	
	ofxDuration();
	void setup(int port);
	//just debug
	void draw(float x, float y, float width, float height);

    float getValueForTrack(string trackName);
    bool getBoolForTrack(string trackName);
    int getNumTracks();
    
	vector<string>& getTracks();
		
	ofxDurationEvents events;
	
	void setupFont(string fontPath, int fontSize);
	
  protected:
	bool isSetup;
    ofTrueTypeFont font;
    void update(ofEventArgs& args);
	
	void parseInfoMessage(const ofxOscMessage& m);
	void parseTrackMessage(const ofxOscMessage& m);
	
	vector<string> trackNames;
    map<string, ofxDurationTrack> tracks;

	//debug colors
	ofColor redColor;
	ofColor blueColor;

};
