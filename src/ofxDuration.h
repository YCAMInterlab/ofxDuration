#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxDurationEvents.h"
#include "ofxDurationTrack.h"

class ofxDuration : public ofxOscReceiver {
  public:
	
	ofxDuration();
	void setup(int port);
	//Draws a column of tracks showing the name and some instananeous
	//information about each one
	void draw(float x, float y, float width, float height);

    float getValueForTrack(string trackName);
    bool getBoolForTrack(string trackName);
	ofColor getColorForTrack(string trackName);
	
    int getNumTracks();
	vector<string>& getTracks();
	//if you pass in a name for a track name we dont' have you'll get an unitialized track
	ofxDurationTrack getTrack(string trackname);
	
	//register for trackUpdated events to respond only messages come in
	ofxDurationEvents events;
	
	void setupFont(string fontPath, int fontSize);
	
	
  protected:
	int port; //cached for drawing
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
