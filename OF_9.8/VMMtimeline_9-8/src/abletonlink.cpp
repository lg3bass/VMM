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
    
    //draw the blinking bar.
    blinkingBottomBar(0.95, 1.0);
}

//-------------------------------------------------
void abletonLinkEngine::update(){

}

//-------------------------------------------------
int abletonLinkEngine::beat(){
    //link
    ofxAbletonLink::Status status = link.update();
    
    b = (int)floor(status.phase);
    return b;
}

//-------------------------------------------------
bool abletonLinkEngine::isDownbeat(){
    return nbeat == 0 ? true : false;
}

//-------------------------------------------------
void abletonLinkEngine::setMeter(int _quantum){
    
    link.setQuantum(_quantum);
}

//-------------------------------------------------
void abletonLinkEngine::setTempo(float _bpm){
    
    link.setTempo(_bpm);
}


//-------------------------------------------------
void abletonLinkEngine::runAbletonLink(ofxAbletonLink &linkObj){
    
    //link
    ofxAbletonLink::Status status = link.update();
    
    //timing info from ofxAbletonLink
    quantum = (int)ceil(link.quantum());
    nbeat = beat();
    
   
    
}

//-------------------------------------------------
void abletonLinkEngine::blinkingBottomBar(float _top, float _bottom){
    //BELOW is all for the bars at the bottom. ableton link.
    //Get the width (dw) evenly spaced by the quantum val
    float dw;
    if(quantum < 1){
        dw = (float)ofGetWidth();
    }else{
        dw = (float)ofGetWidth() / (float)quantum;
    }
    
    //set the location vertically of the blinkng bar
    int top = (int)(ofGetHeight() * _top);
    int bottom = (int)(ofGetHeight() * _bottom);
    int h = bottom - top + 1;
    
    //draw the blinking beats
    for (int i = 0; i < quantum; i++){
        ofPushStyle();
            //BG
            ofFill();
            ofSetColor((i <= nbeat) ? 255 : 128);
            ofDrawRectangle(i * dw, top, dw, h);
        
            //BORDER
            ofNoFill();
            ofSetColor(0);
            ofDrawRectangle(i * dw, top, dw, h);
        
        if(i == nbeat){
            ofNoFill();
            ofSetColor(ofColor::red);
            ofDrawRectangle(i * dw, top, dw, h);
            
        }
        ofPopStyle();
    }
    
}
