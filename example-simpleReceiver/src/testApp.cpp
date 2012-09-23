#include "testApp.h"
#include <locale>
bool isNumber(const string& s){
	locale loc;
	std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it, loc))) ++it;
	return !s.empty() && it == s.end();
}

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofEnableSmoothing();
	ofBackground(255*.15);
	
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	//SimpleReceiverPort.txt should just have the port number
	ofBuffer settings = ofBufferFromFile("SimpleReceiverPort.txt");
	string portString = settings.getText();
	if(isNumber(portString)){
		port = ofToInt(portString);
	}
	else {
		port = 12345;
		ofSystemAlertDialog("SimpleReceiverPort.txt in data/ needs to contain a valid listening port number. Defaulting to 12345");
	}
	
	duration.setup(port);
	//ofxDuration is an OSC receiver, with special functions to listen for Duration specific messages
	//optionally set up a font for debugging
	duration.setupFont("GUI/NewMedia Fett.ttf", 12);
	ofAddListener(duration.events.trackUpdated, this, &testApp::trackUpdated);

}

//--------------------------------------------------------------
void testApp::update(){
	
	//the ofxDuration receiver is automatically updated.
	//You can iterate through the tracks every frame like this:
	vector<string>& allTracks = duration.getTracks();
	for(int i = 0; i < allTracks.size(); i++){
		ofxDurationTrack track = duration.getTrack(allTracks[i]);
		//do something with the track!
	}
}

//--------------------------------------------------------------
//Or wait to receive messages, sent only when the track changed
void testApp::trackUpdated(ofxDurationEventArgs& args){
	ofLogVerbose("Duration Event") << "track type " << args.track->type << " updated with name " << args.track->name << " and value " << args.track->value << endl;
}

//--------------------------------------------------------------
void testApp::draw(){
	duration.draw(0,0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
