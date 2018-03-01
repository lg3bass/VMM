#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    
    ofSetLogLevel("LINK", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("LINKFLIP", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC_TRANSPORT", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC_TRIGGERED", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC_PLAY", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC_IN", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC_OUT", OF_LOG_VERBOSE);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("SAVE", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("LOAD", OF_LOG_VERBOSE);// OF_LOG_ERROR
    ofSetLogLevel("KEYS", OF_LOG_ERROR);// OF_LOG_ERROR
    ofSetLogLevel("KEYBOARD", OF_LOG_ERROR);// OF_LOG_ERROR
    ofSetLogLevel("HEADER", OF_LOG_ERROR);
    ofSetLogLevel("BODY", OF_LOG_ERROR);
    ofSetLogLevel("FOOTER", OF_LOG_ERROR);
    
    ofSetLogLevel("timelineData", OF_LOG_ERROR);
    
    //ableton link setup
    AL.setup(ofGetAppPtr());
    
    //panels setup
    int headerH =   HEADER_PANEL_HEIGHT * ofGetHeight();
    int bodyH =     BODY_PANEL_HEIGHT * ofGetHeight();
    int footerH =   FOOTER_PANEL_HEIGHT * ofGetHeight();
    
    headerPanel.setup(0, 0, ofGetWidth(), headerH, ofGetAppPtr());              //0,    0,         1080,    380*0.17
    timePanel.setup(0, headerH, ofGetWidth(), bodyH, ofGetAppPtr());            //0,    380*0.17,  1080,    380*0.73
    footerPanel.setup(0,headerH+bodyH,ofGetWidth(), footerH, ofGetAppPtr());
    
    myAppData.selected_panel_name = "NONE";
    myAppData.txt_color = ofColor::brown;
    
    //ofxOSC
    receiver_timeline.setup(rPORT);
    sender.setup(HOST, sPORT);
    
    router.setup(ofGetAppPtr());
    
    //events
    //ofAddListener(OscMsgEvent::events, this, &ofApp::oscEvent);
    //ofAddListener(anotherOscMsgEvent::events, this, &ofApp::anotherEvent);
    ofAddListener(VMMOscMessageEvent::events, this, &ofApp::OscSendEvent);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    AL.update();
    
    //panels
    headerPanel.update();
    timePanel.update();
    footerPanel.update();
    
    //listen for OSC
    OscReciever(); 
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetWindowTitle("fps: "+ofToString(ofGetFrameRate())+" - "+ofToString(ofGetWidth())+","+ofToString(ofGetHeight()) + "<" + ofToString(ofGetMouseX()) + "," + ofToString(ofGetMouseY()) + ">");
    
    AL.draw();                                                  //ableton link runner
       
    timePanel.draw();
    headerPanel.draw();//intentionally second.
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
    
    if(headerPanel.getPanelFocus()){
        
        
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    cout << "(" << ofToString(ofGetWidth()) << "," << ofGetHeight() << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
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
    m.addInt32Arg(_track+1);    //VMMtimeline is 0, VMM is 1
    m.addFloatArg(_value);
    
    ofLogVerbose("OSC_OUT") << m.getAddress() << " "
                            << ofToString(m.getArgAsInt(0)) << " "  //_track
                            << ofToString(m.getArgAsFloat(1));      //_value
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::OSCnoteOnAndPlay(int _track, string _address, string _value){
    
    //sample: string _value = "200 1 200"
    //break up the _value to ints
    int VMMnoteID = ofToInt(ofSplitString(_value, " ")[0]);     //could be anything
    int buffer = ofToInt(ofSplitString(_value, " ")[1]);        //starts with 1. not base zero
    int duration = ofToInt(ofSplitString(_value, " ")[2]);
    
    //ofLogVerbose("OSC_OUT") << _address << " " << _value;
    ofxOscMessage m;
    m.setAddress(_address);
    m.addInt32Arg(_track+1);    //VMMtimeline is 0, VMM is 1
    m.addInt32Arg(VMMnoteID);
    m.addInt32Arg(buffer);
    m.addInt32Arg(duration);
    
    ofLogVerbose("OSC_OUT") << m.getAddress() << " "
                            << ofToString(m.getArgAsInt(_track+1)) << " "  //_track
                            << ofToString(m.getArgAsInt(VMMnoteID)) << " "  //VMMnoteID
                            << ofToString(m.getArgAsInt(buffer)) << " "  //buffer
                            << ofToString(m.getArgAsInt(duration));        //duration
    sender.sendMessage(m);
}

/*
void ofApp::oscEvent(OscMsgEvent &e) {
   
    cout << e.msg << endl;
    
}

void ofApp::anotherEvent(anotherOscMsgEvent &e){
    
    cout << e.arg1 << endl;
    cout << e.arg2 << endl;
}
*/
 
void ofApp::OscSendEvent(VMMOscMessageEvent &e){
    
    //tis message is originating from ofxTLVMMControl.
    ofLogVerbose("OSC_OUT") << e.m.getAddress() << " "
                            << ofToString(e.m.getArgAsInt(0)) << " "  //_track  -- preformated base 1
                            << ofToString(e.m.getArgAsInt(1));      //_value
    sender.sendMessage(e.m);
    
}

void ofApp::OSCsendMessage(int track, string address, string message){
    
    ofxOscMessage m;
    m.setAddress(address);
    m.addInt32Arg(track+1);
    m.addStringArg(message);
    
    sender.sendMessage(m);
    
}

void ofApp::sendOSCtestData(int track, int clip){
    
    //TEST 1 -  send commands manually.
    /*
    OSCsendToVMM(0, "playNoteOff", 1.0);
    OSCsendToVMM(0, "playAll", 1.0);
    OSCsendToVMM(0, "mirror", 0.0);
    OSCsendToVMM(0, "mirrorX", 0.0);
    OSCsendToVMM(0, "mirrorY", 0.0);
    OSCsendToVMM(0, "mirrorZ", 0.0);
    OSCsendToVMM(0, "OSCsetMatCap", 19);
    OSCsendToVMM(0, "localSlices", 2);
    OSCsendToVMM(0, "localCopies", 12);
    OSCsendToVMM(0, "globalCopies", 1);
    
    OSCsendToVMM(0, "mirrorDistance", 0);
    OSCsendToVMM(0, "setGlobalRotX", 0);
    OSCsendToVMM(0, "setGlobalRotY", 0);
    OSCsendToVMM(0, "setGlobalRotZ", 0);
    OSCsendToVMM(0, "setGlobalTransX", 0);
    OSCsendToVMM(0, "setGlobalTransY", 12);
    OSCsendToVMM(0, "setGlobalTransZ", 12);
    
    OSCsendToVMM(0, "setLocalRotX", 12);
    OSCsendToVMM(0, "setLocalRotY", 12);
    OSCsendToVMM(0, "setLocalRotZ", 12);
    OSCsendToVMM(0, "setLocalTransX", 12);
    OSCsendToVMM(0, "setLocalTransY", 12);
    OSCsendToVMM(0, "setLocalTransZ", 12);
    
    OSCsendToVMM(0, "setObjRotX", 12);
    OSCsendToVMM(0, "setObjRotY", 12);
    OSCsendToVMM(0, "setObjRotZ", 12);
    
    OSCsendToVMM(0, "localScale", 1.0);
    OSCsendToVMM(0, "globalScale", 20.0);
    
    OSCsendToVMM(0, "clear", 1);
    */
    
    
    //TEST 2 -
    //1. Check if VMM track exists
    //2. Has the VMM track been loaded?  Check flag on VMM track to see if it's been loaded.
    //2a.   Loaded - use the data in ofParams.
    //2b.   Not loaded - load the data.
    
    
    if(timePanel.tracks.timelines[track]->hasTrack("VMM")){
        auto vmmTrack = (ofxTLVMMControl*)timePanel.tracks.timelines[track]->getTrack("VMM");
        OSCsendToVMM(track, "/playNoteOff", vmmTrack->clips[clip].playNoteOff);   //TODO:  confusion track 0 is track 1 in VMM
        OSCsendToVMM(track, "/playAll", vmmTrack->clips[clip].playAll);
        OSCsendToVMM(track, "/mirror", vmmTrack->clips[clip].mirror);
        OSCsendToVMM(track, "/mirrorX", vmmTrack->clips[clip].mirrorX);
        OSCsendToVMM(track, "/mirrorY", vmmTrack->clips[clip].mirrorY);
        OSCsendToVMM(track, "/mirrorZ", vmmTrack->clips[clip].mirrorZ);
        OSCsendToVMM(track, "/OSCsetMatCap", vmmTrack->clips[clip].OSCsetMatCap);
        
        
        OSCsendToVMM(track, "/localSlices", vmmTrack->clips[clip].localSlices);
        OSCsendToVMM(track, "/localCopies", vmmTrack->clips[clip].localCopies);
        OSCsendToVMM(track, "/globalCopies", vmmTrack->clips[clip].globalCopies);
        OSCsendToVMM(track, "/mirrorDistance", vmmTrack->clips[clip].mirrorDistance);

        OSCsendToVMM(track, "/setGlobalRotX", vmmTrack->clips[clip].setGlobalRotX);
        OSCsendToVMM(track, "/setGlobalRotY", vmmTrack->clips[clip].setGlobalRotY);
        OSCsendToVMM(track, "/setGlobalRotZ", vmmTrack->clips[clip].setGlobalRotZ);

        OSCsendToVMM(track, "/setGlobalTransX", vmmTrack->clips[clip].setGlobalTransX);
        OSCsendToVMM(track, "/setGlobalTransY", vmmTrack->clips[clip].setGlobalTransY);
        OSCsendToVMM(track, "/setGlobalTransZ", vmmTrack->clips[clip].setGlobalTransZ);

        OSCsendToVMM(track, "/setGlobalRotX", vmmTrack->clips[clip].setGlobalRotX);
        OSCsendToVMM(track, "/setGlobalRotY", vmmTrack->clips[clip].setGlobalRotY);
        OSCsendToVMM(track, "/setGlobalRotZ", vmmTrack->clips[clip].setGlobalRotZ);

        OSCsendToVMM(track, "/setLocalTransX", vmmTrack->clips[clip].setLocalTransX);
        OSCsendToVMM(track, "/setLocalTransY", vmmTrack->clips[clip].setLocalTransY);
        OSCsendToVMM(track, "/setLocalTransZ", vmmTrack->clips[clip].setLocalTransZ);

        OSCsendToVMM(track, "/setObjRotX", vmmTrack->clips[clip].setObjRotX);
        OSCsendToVMM(track, "/setObjRotY", vmmTrack->clips[clip].setObjRotY);
        OSCsendToVMM(track, "/setObjRotZ", vmmTrack->clips[clip].setObjRotZ);

        OSCsendToVMM(track, "/localScale", vmmTrack->clips[clip].localScale);
        OSCsendToVMM(track, "/globalScale", vmmTrack->clips[clip].globalScale);
        
    }
    
}
