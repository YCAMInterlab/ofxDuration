
#include "ofxDuration.h"

ofxDuration::ofxDuration(){
	isSetup = false;
	redColor = ofColor(250, 200, 80);
	blueColor = redColor.getInverted();	
}

void ofxDuration::setup(int _port){
	ofxOscReceiver::setup(_port);
	port = _port;
	if(!isSetup){
		ofAddListener(ofEvents().update, this, &ofxDuration::update);
		isSetup = true;
	}
}

void ofxDuration::update(ofEventArgs& args){
	while(hasWaitingMessages()){
		ofxOscMessage m;
		getNextMessage(&m);
		
		cout << "got message " << m.getAddress() << endl;
		//duration will send an info package whenever play begins
		//we use this to set up all the track info
		if(m.getAddress() == "/duration/info"){
			parseInfoMessage(m);
		}
		else {
			parseTrackMessage(m);
		}
	}
}

void ofxDuration::parseInfoMessage(const ofxOscMessage& m){
	
	ofLogVerbose("ofxDuration::parseInfoMessage") << "Received track information from Duration, #args " << m.getNumArgs();
	
	tracks.clear();
	trackNames.clear();
	//pairs of two strings per track, name and type
	for(int i = 0; i < m.getNumArgs()-1; i+=2){
		if(m.getArgType(i  ) == OFXOSC_TYPE_STRING &&
		   m.getArgType(i+1) == OFXOSC_TYPE_STRING)
		{
			string trackType = m.getArgAsString(i  );
			string trackName = m.getArgAsString(i+1);
			ofxDurationTrack t;
			t.type = trackType;
			t.name = trackName;
			t.lastUpdatedTime = ofGetElapsedTimef();
			ofLogVerbose("ofxDuration::parseInfoMessage") << "Adding track " << t.type << " : " << t.name;

			if(trackType == "Curves"){
				//consume two more args for min and max
				if(i+3 < m.getNumArgs() &&
				   m.getArgType(i+2) == OFXOSC_TYPE_FLOAT &&
				   m.getArgType(i+3) == OFXOSC_TYPE_FLOAT)
				{
					t.range = ofRange(m.getArgAsFloat(i+2), m.getArgAsFloat(i+3));
					ofLogVerbose("ofxDuration::parseInfoMessage") << " track range is " << t.range;

					i+=2;
				}
			}
			
			//only add unique names
			if(tracks.find(t.name) == tracks.end()){
				trackNames.push_back(t.name);
				tracks[t.name] = t;
			}
			else{
				ofLogNotice("ofxDuration::parseInfoMessage") << "Duplicate track name received: " << t.name;
			}
		}
	}
	ofLogVerbose("ofxDuration::parseInfoMessage") << "Created " << tracks.size() << " tracks";
}

void ofxDuration::parseTrackMessage(const ofxOscMessage& m){
	for(int i = 0; i < trackNames.size(); i++){
		if(trackNames[i] == m.getAddress()){
			ofxDurationTrack& track = tracks[trackNames[i]];
			bool updated = false;
			
			if(track.type == "Bangs"){
				updated = true;
			}
			else if(track.type == "Curves"){
				if(m.getNumArgs() == 1 && m.getArgType(0) == OFXOSC_TYPE_FLOAT){
					track.value = m.getArgAsFloat(0);
					updated = true;
				}
				else {
					ofLogError("ofxDuration::parseTrackMessage") << "Incorrect arguments sent to Curves track " << track.name;
				}
			}
			else if(track.type == "Colors"){
				if(m.getNumArgs() == 3 &&
				   m.getArgType(0) == OFXOSC_TYPE_INT32 &&
				   m.getArgType(1) == OFXOSC_TYPE_INT32 &&
				   m.getArgType(2) == OFXOSC_TYPE_INT32)
				{
					track.color = ofColor(m.getArgAsInt32(0),
										  m.getArgAsInt32(1),
										  m.getArgAsInt32(2));
					updated = true;
				}
				else {
					ofLogError("ofxDuration::parseTrackMessage") << "Incorrect arguments sent to Colors track " << track.name;
				}
			}
			else if(track.type == "Switches"){
				if(m.getNumArgs() == 1 && m.getArgType(0) == OFXOSC_TYPE_INT32){
					track.on = m.getArgAsInt32(0) != 0;
					updated = true;
				}
				else{
					ofLogError("ofxDuration::parseTrackMessage") << "Incorrect arguments sent to Switches track " << track.name;
				}
			}
			else if(track.type == "Flags"){
				if(m.getNumArgs() == 1 && m.getArgType(0) == OFXOSC_TYPE_STRING){
					track.flag = m.getArgAsString(0);
					updated = true;
				}
				else{
					ofLogError("ofxDuration::parseTrackMessage") << "Incorrect arguments sent to Flags track " << track.name;
				}
			}
			
			if(updated){
				track.lastUpdatedTime = ofGetElapsedTimef();
				ofxDurationEventArgs trackEventArgs;
				trackEventArgs.duration = this;
				trackEventArgs.track = &track;
				ofNotifyEvent(events.trackUpdated, trackEventArgs, this);
			}
			
			return;
		}
	}	
}

//just for debug purposes
void ofxDuration::draw(float x, float y, float width, float height){
	if(!isSetup){
		return;
	}

	ofPushStyle();
	ofEnableAlphaBlending();
	
    map<string, ofxDurationTrack>::iterator trackit;
	int numTracks = tracks.size();
	float heightPerTrack = height / numTracks;
	for (int trackIdx = 0; trackIdx < trackNames.size(); trackIdx++) {
		ofPushStyle();
		ofxDurationTrack& track = tracks[trackNames[trackIdx]];
		ofRectangle drawSpace(x, y+(heightPerTrack*trackIdx), width, heightPerTrack);
		//fade out indicator over 2 seconds
		float fadeValue = ofMap(track.lastUpdatedTime, ofGetElapsedTimef(), ofGetElapsedTimef()-2, 150, 0, true);

		if(track.type == "Bangs"){
			ofFill();
			ofSetColor(blueColor, fadeValue);
			ofRect(drawSpace);
		}
		else if(track.type == "Curves"){
			ofSetColor(redColor);
			float height = ofMap(track.value, track.range.min, track.range.max, drawSpace.getMaxY(), drawSpace.getMinY());
			ofLine(drawSpace.getMinX(), height,
				   drawSpace.getMaxX(), height);			
		}
		else if(track.type == "Colors"){
			ofFill();
			ofSetColor(track.color);
			ofRect(drawSpace);
			
		}
		else if(track.type == "Switches"){
			if(track.on){
				ofFill();
				ofSetColor(blueColor, 150);
				ofRect(drawSpace);
			}
		}
		else if(track.type == "Flags"){
			ofFill();
			ofSetColor(blueColor, fadeValue);
			ofRect(drawSpace);
			ofSetColor(255);
			if(font.isLoaded()){
				font.drawString(track.flag, drawSpace.x + 10, drawSpace.y + (font.getLineHeight()+3)*2);
			}
			else{
				ofDrawBitmapString(track.flag, drawSpace.x + 10, drawSpace.y + 30);
			}
		}
		
		//draw border
		ofNoFill();
		ofSetColor(redColor);
		ofRect(drawSpace);
		//draw label
		if(track.type == "Colors"){
			ofSetColor(track.color.getInverted());
		}
		else{
			ofSetColor(255);
		}
		
		if(font.isLoaded()){
			font.drawString(track.name, drawSpace.x + 10, drawSpace.y + font.getLineHeight()+3);
		}
		else{
			ofDrawBitmapString(track.name, drawSpace.x + 10, drawSpace.y + 15);
		}
	
		ofPopStyle();
	}
	
	ofSetColor(255);
	if(font.isLoaded()){
		font.drawString("listening on port " + ofToString(port), x + 10, y+height-5);
	}
	else{
		ofDrawBitmapString("listening on port " + ofToString(port), x + 10, y+height-5);
	}
	
	ofPopStyle();
}

float ofxDuration::getValueForTrack(string trackName){
	if(tracks.find(trackName) != tracks.end()){
		return tracks[trackName].value;
	}
	ofLogWarning("ofxDuration::getValueForTrack") << "Couldn't find track named " + trackName;	
	return false;
}

bool ofxDuration::getBoolForTrack(string trackName){
	if(tracks.find(trackName) != tracks.end()){
		return tracks[trackName].on;
	}
	ofLogWarning("ofxDuration::getBoolForTrack") << "Couldn't find track named " + trackName;
	return false;
}

ofColor ofxDuration::getColorForTrack(string trackName){
	if(tracks.find(trackName) != tracks.end()){
		return tracks[trackName].color;
	}
	ofLogWarning("ofxDuration::getColorForTrack") << "Couldn't find track named " + trackName;
	return ofColor(0,0,0);
}

int ofxDuration::getNumTracks(){
	return trackNames.size();
}

ofxDurationTrack ofxDuration::getTrack(string trackName){
	if(tracks.find(trackName) != tracks.end()){
		return tracks[trackName];
	}
	ofLogWarning("ofxDuration::getTrack") << "Couldn't find track named " + trackName;	
	return ofxDurationTrack();
}

vector<string>& ofxDuration::getTracks(){
	return trackNames;
}

void ofxDuration::setupFont(string fontPath, int fontSize){
	font.loadFont(fontPath, fontSize);
}
