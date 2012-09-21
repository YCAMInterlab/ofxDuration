#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofBackground(255*.15);
	
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	duration.setup(PORT);
	ofAddListener(duration.events.trackUpdated, this, &testApp::trackUpdated);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::trackUpdated(ofxDurationEventArgs& args){
//	ofLogVerbose("Duration Event") << "Track updated " << args.track->name << endl;
}

//--------------------------------------------------------------
void testApp::draw(){
	duration.draw(0,0, ofGetWidth(), 150);
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
