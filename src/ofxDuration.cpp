
#include "ofxDuration.h"

ofxDuration::ofxDuration(){
	isSetup = false;
}

void ofxDuration::setup(int port){
	ofxOscReceiver::setup(port);
	if(!isSetup){
		ofAddListener(ofEvents().update, this, &ofxDuration::update);
		isSetup = true;
	}
}

void ofxDuration::update(ofEventArgs& args){
	while(hasWaitingMessages()){
		ofxOscMessage m;
		getNextMessage(&m);
		
		//duration will send an info package whenever play begins
		//we use this to set up all the track info
		if(m.getAddress() == "/duration/info"){
			tracks.clear();
			trackNames.clear();
			//pairs of two strings per track, name and type
			for(int i = 0; i < m.getNumArgs()-1; i+=2){
				if(m.getArgType(i) == OFXOSC_TYPE_STRING &&
				   m.getArgType(i+1) == OFXOSC_TYPE_STRING)
				{
					string trackName = m.getArgAsString(i  );
					string trackType = m.getArgAsString(i+1);
					ofxDurationTrack t;
					t.name = trackName;
					t.type = trackType;
					trackNames.push_back(t.name);
				}
			}
		}
	}
}

//just for debug purposes
void ofxDuration::draw(){
	
}

float ofxDuration::getValueForTrack(string trackName){
	
}

bool ofxDuration::getBoolForTrack(string trackName){
	
}

int ofxDuration::getNumTracks(){
	
}

vector<string>& ofxDuration::getTracks(){
	
}

void ofxDuration::drawDebug(){
	
}

void ofxDuration::setupFont(string fontPath, int fontSize){
	
}
