/**
 * ofxDuration
 * openFrameworks addon for interacting with the Duration timeline
 *
 * Copyright (c) 2011-2012 James George
 * Development Supported by YCAM InterLab http://interlab.ycam.jp/en/
 * http://jamesgeorge.org + http://flightphase.com
 * http://github.com/obviousjim + http://github.com/flightphase
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

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
