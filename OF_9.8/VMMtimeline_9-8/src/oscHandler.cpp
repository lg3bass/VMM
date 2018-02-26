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
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", "/transport_playing - FALSE");
        } else if (m.getArgAsInt32(1) == 1) {
            isAbletonTransportRunning = true;
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", "/transport_playing - TRUE");
        }
        //trigger when transport starts
        if(isAbletonTransportRunning) {
            //do something when the transport starts
            ofLogNotice("OSC_TRANSPORT") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --START TRANSPORT";
            
            string msg = "OSC_TRANSPORT " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --START TRANSPORT";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
        } else {
            //close out,clean up function
            ofLogNotice("OSC_TRANSPORT") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --STOP TRANSPORT(stop timline)";
            
            string msg = "OSC_TRANSPORT " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --STOP TRANSPORT(stop timline)";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            //NOTE: argument does NOTHING YET!!!!!
            oscMainApp->stopTLclip(m.getArgAsInt(1));
            
        }
    } else if (m.getAddress() == "/fired_slot_index"){
        if (m.getArgAsInt32(1) == -2){
            //what does -2 do??? look on LOM.
            //I think this function is called when the stop button is fired while the clip is playing.
            isAbletonClipTriggered = false;
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", "/fired_slot_index - isAbletonClipTriggered - FALSE");
        } else if (m.getArgAsInt32(1) == -1){
            isAbletonClipTriggered = false;
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", "/fired_slot_index - isAbletonClipTriggered - FALSE");
        } else {
            isAbletonClipTriggered = true;
            
            string msg = "/fired_slot_index - isAbletonClipTriggered - TRUE (play clip no: "+ofToString(m.getArgAsInt32(1))+")";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
            //register which clip to PREPARE to play.
            //------------------------------------------
            currentFiredSlotIndex = m.getArgAsInt32(1);
            
            //TODO: Here send a /clear message to VMM
            //As a test we want to send some params to set up baseline before the first note is played.
            oscMainApp->sendOSCtestData();
            
        }
        
        //triggered message recieved
        if(isAbletonClipTriggered){
            
            
            ofLogNotice("OSC_TRIGGERED") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --CLIP TRIGGERED ON";
            
            string msg = "OSC_TRIGGERED " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP TRIGGERED ON";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
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
                string msg = "OSC_TRIGGERED " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP TRIGGERED OFF (tranport running still)";
                oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            } else {
                //wait for playing_slot_index
                waitForClipPlaying = true;
                ofLogNotice("OSC_TRIGGERED") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --CLIP TRIGGERED OFF (waitForClipPlaying)";
                string msg = "OSC_TRIGGERED " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP TRIGGERED OFF (waitForClipPlaying)";
                oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            }
            
        }
    } else if (m.getAddress() == "/playing_slot_index"){
        if (m.getArgAsInt32(1) == -2){
            isAbletonClipPlaying = false;
            
            string msg = "/playing_slot_index - isAbletonClipPlaying = false";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
        } else if (m.getArgAsInt32(1) == -1){
            //what does -1 do? ask LOM.
            
            string msg = "/playing_slot_index - isAbletonClipPlaying = undefined";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
        } else {
            isAbletonClipPlaying = true;
            
            string msg = "/playing_slot_index - isAbletonClipPlaying = true";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
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
                
                string msg = "OSC_PLAY " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP PLAY ON (waitForClipPlaying)";
                oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
                
                oscMainApp->playTLclip(m.getArgAsInt32(0), m.getArgAsInt32(1));
                
            } else {
                //play the clip
                ofLogNotice("OSC_PLAY") << m.getAddress() << " "
                << m.getArgAsInt32(0) << " "
                << m.getArgAsInt32(1)
                << " --CLIP PLAY ON (start timeline)";
                
                string msg = "OSC_PLAY " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP PLAY ON (start timeline)";
                oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
                
                oscMainApp->playTLclip(m.getArgAsInt32(0), m.getArgAsInt32(1));
                
            }
            
        } else {
            
            ofLogNotice("OSC_IN")   << m.getAddress() << " "
            << m.getArgAsInt32(0) << " "
            << m.getArgAsInt32(1)
            << " --CLIP STOP (stop timeline)";
            
            string msg = "OSC_IN " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP STOP (stop timeline)";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
            //NOTE: argument does NOTHING YET!!!!!
            oscMainApp->stopTLclip(m.getArgAsInt(0));
            
            waitForClipPlaying = false;
        }
        
    }//end if
}//end function
