//
//  abletonlink.cpp
//  VMMtimeline_9-8
//
//  Created by Robert White III on 7/15/17.
//
//

#include "abletonlink.h"
#include "ofApp.h"

ofApp* linkMainApp;         //reference to ofApp()

//-------------------------------------------------
abletonLinkEngine::abletonLinkEngine(){
    lbeat = -1;
    nbeat = -1;
}

//-------------------------------------------------
void abletonLinkEngine::setup(ofBaseApp* appPtr){
    
    linkMainApp = dynamic_cast<ofApp*>(appPtr);
    
    //cout << "linkModule->setup()" << endl;
    
    link.setup(120.0);
    
}

//-------------------------------------------------
void abletonLinkEngine::draw(){
    
    runAbletonLink(link);
    
    
    
}

//-------------------------------------------------
int abletonLinkEngine::beat(){
    //link
    ofxAbletonLink::Status status = link.update();
    
    cout << "status.phase: " << ofToString(floor(status.phase)) << endl;
    
    
    return nbeat;
}

//-------------------------------------------------
void abletonLinkEngine::runAbletonLink(ofxAbletonLink &linkObj){
    
    //link
    ofxAbletonLink::Status status = link.update();
    
    // visualize the current status
    int quantum = (int)ceil(link.quantum());
    
    beat();
    
    //what beat is playing in link?
    float dw;
    if(quantum < 1){
        dw = (float)ofGetWidth();
        nbeat = 0;
    }else{
        dw = (float)ofGetWidth() / (float)quantum;
        nbeat = (int)floor(status.beat) % quantum;
    }
    
    
    //BELOW is all for the bars at the bottom. ableton link.
    //this is not needed cause the UI has a field for this.
    int top = (int)(ofGetHeight() * 0.95);
    int bottom = (int)(ofGetHeight() * 1);
    int h = bottom - top + 1;
    
    //draw the blinking beats
    for (int i = 0; i < quantum; i++){
        ofPushStyle();
        ofFill();
        ofSetColor((i <= nbeat) ? 255 : 128);
        ofDrawRectangle(i * dw, top, dw, h);
        ofNoFill();
        ofSetColor(0);
        ofDrawRectangle(i * dw, top, dw, h);
        ofPopStyle();
    }
    
    //test sent to headerUI
    
    
    
}
