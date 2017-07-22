#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    AL.setup(ofGetAppPtr());
    
    //panels setup
    int headerH =   HEADER_PANEL_HEIGHT * ofGetHeight();
    int bodyH =     BODY_PANEL_HEIGHT * ofGetHeight();
    int footerH =   FOOTER_PANEL_HEIGHT * ofGetHeight();
    
    headerPanel.setup(0, 0, ofGetWidth(), headerH, ofGetAppPtr());
    timePanel.setup(0, headerH, ofGetWidth(), bodyH, ofGetAppPtr());
    footerPanel.setup(0,headerH+bodyH,ofGetWidth(), footerH, ofGetAppPtr());
    
    myAppData.selected_panel_name = "NONE";
    myAppData.txt_color = ofColor::brown;
    
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //panels
    headerPanel.update();
    timePanel.update();
    footerPanel.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle("fps: "+ofToString(ofGetFrameRate())+" - "+ofToString(ofGetWidth())+","+ofToString(ofGetHeight()));
    
    AL.draw();                                                  //ableton link runner
    
    
    
    //panels
    
    timePanel.draw();
    headerPanel.draw();    
    footerPanel.draw();
    
    setBreadcrumb();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    headerPanel.keyPressed(key);
    timePanel.keyPressed(key);
    footerPanel.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    timePanel.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    headerPanel.mousePressed(x, y, button);
    timePanel.mousePressed(x, y, button);
    footerPanel.mousePressed(x, y, button);
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    headerPanel.mouseReleased(x, y, button);
    timePanel.mouseReleased(x, y, button);
    footerPanel.mouseReleased(x, y, button);
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}





