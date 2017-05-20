#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetLogLevel("LINK", OF_LOG_SILENT);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC_TRANSPORT", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC_TRIGGERED", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC_PLAY", OF_LOG_NOTICE);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC_OUT", OF_LOG_SILENT);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("TRACK", OF_LOG_VERBOSE);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("FILE", OF_LOG_VERBOSE);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("KEY", OF_LOG_SILENT);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("GUI", OF_LOG_VERBOSE);//DEFAULT: OF_LOG_ERROR
 
    ofSetBackgroundColor(ofColor::black);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    _frameRate = INIT_FPS;
    ofSetFrameRate(_frameRate);
    
    
    myAppData.selected_track = 0;
    myAppData.tempo = 120.0;
    
    
    for(int i=0; i<NUMBER_OF_TRACKS; i++){
        trackData t;
        t.selected_clip = 0;
        t.slices = 2;
        t.measures = 8;
        t.current_page = 0;
        t.cuedToPlay = false;
        myAppData.tracks.push_back(t);
        

    }
    
    //ofxOSC
    receiver_timeline.setup(rPORT);
    sender.setup(HOST, sPORT);
    
    
    
    //panels setup
    int headerH = MAIN_PANEL_HEIGHT * ofGetHeight();
    int timeH = TIME_PANEL_HEIGHT * ofGetHeight() - 100;
    int buttonPanelW = BUTTON_PANEL_WIDTH;
    
    //int metersH = METER_PANEL_HEIGHT * ofGetHeight();
    
    headerPanel.setup(0, 0, ofGetWidth(), headerH, ofGetAppPtr());
    buttonPanel.setup(0, headerH, buttonPanelW, timeH, ofGetAppPtr());
    timePanel.setup(buttonPanelW+10, headerH, ofGetWidth()-(buttonPanelW+10), timeH, ofGetAppPtr());
    
    
    router.setup(ofGetAppPtr());
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //panel flowthrough update();
    headerPanel.update();
    buttonPanel.update();
    timePanel.update();
    
    OscReciever();                                              //process ALL incoming OSC!
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //panel flowthrough draw();
    headerPanel.draw();
    buttonPanel.draw();
    timePanel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    timePanel.keyPressed(key);
    
    switch (key) {
            
        default:
            break;
            
    }
    
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

//-------------------------------------------------
#pragma mark - Getters and Setters
//-------------------------------------------------

//TEMPO
//--------------------------------------------------------------
float ofApp::getGlobalTempo(){
    return myAppData.tempo;
    
}

//--------------------------------------------------------------
void ofApp::setGlobalTempo(float _t){
    myAppData.tempo = _t;
    ofLogNotice("GUI") << "New Global Tempo: " << myAppData.tempo ;
}

//TRACKS
//--------------------------------------------------------------
void ofApp::showMeCurrentTrackClipPage(int _track){

    ofLogNotice("TRACK")    << "ofApp::showMeCurrentTrackClipPage("
                            << getSelectedTrack() << ","
                            << getSelectedClip(_track) << ","
                            << getCurrentPage(_track) << ")";
    
}

//--------------------------------------------------------------
void ofApp::play(int _track, int _clip){
    
    
    myAppData.tracks[_track].selected_clip = _clip;             //update which clip is active in the track.
    
    timePanel.play(_track, _clip);                              //load the xml then cue to play on next ofApp::update()
    
    setClipAndPageButtons(_track);
}

//--------------------------------------------------------------
void ofApp::resetAllTrackAndClips(){
    
    setSelectedTrack(0);
    
    for(int i=0;i<NUMBER_OF_TRACKS;i++){
        setSelectedClip(i, 0);
        setCurrentPage(i, 0);
        
    }
    
    displayTrack(0);
}


//--------------------------------------------------------------
int ofApp::getSelectedTrack(){

    return myAppData.selected_track;
}

//--------------------------------------------------------------
void ofApp::setSelectedTrack(int _track){

    myAppData.selected_track = _track;

    ofLogNotice("GUI")  << "ofApp.setSelectedTrack : ["
                        << myAppData.selected_track << ","
                        << myAppData.tracks[myAppData.selected_track].selected_clip << ","
                        << myAppData.tracks[myAppData.selected_track].current_page << "]";
}

//CLIPS
//--------------------------------------------------------------
int ofApp::getSelectedClip(int _track){

    return myAppData.tracks[_track].selected_clip;
}

//--------------------------------------------------------------
void ofApp::setSelectedClip(int _track, int _clip){

    myAppData.tracks[_track].selected_clip = _clip;
    
    timePanel.loadCurrent();
    
    ofLogNotice("GUI")  << "ofApp::setSelectedClip : ["
                        << myAppData.selected_track << ","
                        << myAppData.tracks[myAppData.selected_track].selected_clip << ","
                        << myAppData.tracks[myAppData.selected_track].current_page << "]";
}

//PAGES
//--------------------------------------------------------------
int ofApp::getCurrentPage(int _track){

    return myAppData.tracks[_track].current_page;
}

//--------------------------------------------------------------
void ofApp::setCurrentPage(int _track, int _page){

    myAppData.tracks[_track].current_page = _page;
    timePanel.timelines[_track]->setCurrentPage(_page);
    
    ofLogNotice("GUI")  << "ofApp::setCurrentPage : ["
                        << myAppData.selected_track << ","
                        << myAppData.tracks[myAppData.selected_track].selected_clip << ","
                        << myAppData.tracks[myAppData.selected_track].current_page << "]";
    
}

//--------------------------------------------------------------
bool ofApp::getIsCuedToPlay(int _track){

    return myAppData.tracks[_track].cuedToPlay;
}

//--------------------------------------------------------------
void ofApp::setCuedToPlay(int _track, bool _val){
    
    myAppData.tracks[_track].cuedToPlay = _val;                 //enable the timeline to run on the main draw() loop.
}

//--------------------------------------------------------------
void ofApp::displayTrack(int _track){
    
    timePanel.showSelectedTimelineTrack(_track);
}

//--------------------------------------------------------------
void ofApp::setClipAndPageButtons(int _track){
    
    if(_track == getSelectedTrack()){                           //only toggle the buttons if track is selected
        buttonPanel.setButtonClipToggle(getSelectedClip(_track));
        buttonPanel.setButtonPageToggle(getCurrentPage(_track));
    }
}

//--------------------------------------------------------------
void ofApp::OscReciever(){
    while(receiver_timeline.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver_timeline.getNextMessage(&m);
        
        router.processOSCmessage(m);
        
    }//end while    
}


//--------------------------------------------------------------
void ofApp::OSCsendToVMM(int _track, string _address, float _value){
    ofxOscMessage m;
    m.setAddress(_address);
    m.addInt32Arg(_track);
    m.addFloatArg(_value);
        
    sender.sendMessage(m);
}




