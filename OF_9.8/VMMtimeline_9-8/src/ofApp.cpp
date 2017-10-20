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
    ofSetLogLevel("OSC_OUT", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("SAVE", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("LOAD", OF_LOG_ERROR);// OF_LOG_ERROR
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
    
    ofLogVerbose("OSC_OUT") << _address << " " << _value;
    ofxOscMessage m;
    m.setAddress(_address);
    m.addInt32Arg(_track);
    m.addFloatArg(_value);
    
    sender.sendMessage(m);
}




