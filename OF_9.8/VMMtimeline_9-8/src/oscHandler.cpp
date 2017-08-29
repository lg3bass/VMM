//
//  oscHandler.cpp
//  VMMtimeline_9-8
//
//  Created by Robert White III on 8/24/17.
//
//

#include "oscHandler.h"
#include "ofApp.h"

ofApp* oscMainApp;

oscHandler::oscHandler(){
    
    
}

void oscHandler::setup(ofBaseApp* appPtr){
    oscMainApp = dynamic_cast<ofApp*>(appPtr);
}


void oscHandler::processOSCmessage(ofxOscMessage &m){
    
    ofLogVerbose("OSC") << "processOSCmessage: " << m.getAddress();
    
    if(m.getAddress() == "/transport_playing"){
        if (m.getArgAsInt32(1) == 0) {
            isAbletonTransportRunning = false;
        } else if (m.getArgAsInt32(1) == 1) {
            isAbletonTransportRunning = true;
        }
        //trigger when transport starts
        if(isAbletonTransportRunning) {
            //do something when the transport starts
            ofLogNotice("OSC_TRANSPORT") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --START TRANSPORT";
            
        } else {
            //close out,clean up function
            ofLogNotice("OSC_TRANSPORT") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --STOP TRANSPORT(stop timline)";
            
            //NOTE: argument does NOTHING YET!!!!!
            oscMainApp->stopTLclip(m.getArgAsInt(1));
            
        }
    } else if (m.getAddress() == "/fired_slot_index"){
        if (m.getArgAsInt32(1) == -2){
            //what does -2 do??? look on LOM.
            //I think this function is called when the stop button is fired while the clip is playing.
            isAbletonClipTriggered = false;
            
        } else if (m.getArgAsInt32(1) == -1){
            isAbletonClipTriggered = false;
        } else {
            isAbletonClipTriggered = true;
            
            //register which clip to PREPARE to play.
            //------------------------------------------
            currentFiredSlotIndex = m.getArgAsInt32(1);
        }
        
        //triggered message recieved
        if(isAbletonClipTriggered){
            
            ofLogNotice("OSC_TRIGGERED") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --CLIP TRIGGERED ON";
            
            //preload the clip data. take this  out for now
            //oscMainApp->timePanel.load(m.getArgAsInt32(1));
            
            
            //TODO - insert function to set current playing.
            //oscMainApp->setSelectedTrack(m.getArgAsInt32(0));
            //oscMainApp->setSelectedClip(m.getArgAsInt32(0), m.getArgAsInt32(1));
            
        } else {
            
            //check if transport has started
            if(isAbletonTransportRunning){
                //do something if transport is running.
                ofLogNotice("OSC_TRIGGERED") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --CLIP TRIGGERED OFF (tranport running still)";
            } else {
                //wait for playing_slot_index
                waitForClipPlaying = true;
                ofLogNotice("OSC_TRIGGERED") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --CLIP TRIGGERED OFF (waitForClipPlaying)";
            }
            
        }
    } else if (m.getAddress() == "/playing_slot_index"){
        if (m.getArgAsInt32(1) == -2){
            isAbletonClipPlaying = false;
            
        } else if (m.getArgAsInt32(1) == -1){
            //what does -1 do? ask LOM.
            
            
        } else {
            isAbletonClipPlaying = true;
            
            //register which clip to PLAY.
            //------------------------------------------
            currentPlayingSlotIndex = m.getArgAsInt32(1);
        }
        
        //play mesage recieved
        if(isAbletonClipPlaying) {
            
            if(waitForClipPlaying) {
                ofLogNotice("OSC_PLAY") << m.getAddress() << " "
                << m.getArgAsInt32(0) << " "
                << m.getArgAsInt32(1)
                << " --CLIP PLAY ON (waitForClipPlaying)";
                
                oscMainApp->playTLclip(m.getArgAsInt32(0), m.getArgAsInt32(1));
                
            } else {
                //play the clip
                ofLogNotice("OSC_PLAY") << m.getAddress() << " "
                << m.getArgAsInt32(0) << " "
                << m.getArgAsInt32(1)
                << " --CLIP PLAY ON (start timeline)";
                
                oscMainApp->playTLclip(m.getArgAsInt32(0), m.getArgAsInt32(1));
                
            }
            
        } else {
            
            ofLogNotice("OSC_IN")   << m.getAddress() << " "
            << m.getArgAsInt32(0) << " "
            << m.getArgAsInt32(1)
            << " --CLIP STOP (stop timeline)";
            
            //NOTE: argument does NOTHING YET!!!!!
            oscMainApp->stopTLclip(m.getArgAsInt(0));
            
            waitForClipPlaying = false;
        }
        
    }//end if
}//end function
