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
            
            //LOG TO VMM
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", "/transport_playing - FALSE");
            
        } else if (m.getArgAsInt32(1) == 1) {
            isAbletonTransportRunning = true;
            
            //LOG TO VMM
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", "/transport_playing - TRUE");
            
        }
        //trigger when transport starts
        if(isAbletonTransportRunning) {
            //do something when the transport starts
            ofLogNotice("OSC_TRANSPORT") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --START TRANSPORT";
            
            //LOG TO VMM
            string msg = "OSC_TRANSPORT " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --START TRANSPORT";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
        } else {
            //close out,clean up function
            ofLogNotice("OSC_TRANSPORT") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --STOP TRANSPORT(stop timline)";
            
            //LOG TO VMM
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
            
            //LOG TO VMM
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", "/fired_slot_index - isAbletonClipTriggered - FALSE");
            
        } else if (m.getArgAsInt32(1) == -1){
            isAbletonClipTriggered = false;
            
            //LOG TO VMM
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", "/fired_slot_index - isAbletonClipTriggered - FALSE");
            
        } else {
            isAbletonClipTriggered = true;
            
            //LOG TO VMM
            string msg = "/fired_slot_index - isAbletonClipTriggered - TRUE (play clip no: "+ofToString(m.getArgAsInt32(1))+")";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
            //register which clip to PREPARE to play.
            //------------------------------------------
            currentFiredSlotIndex = m.getArgAsInt32(1);
            
            //TODO: Here send a /clear message to VMM
            
            //Send some params to set up baseline before the first note is played.
            //Setting this here triggers this data BEFORE the first not is played in Ableton.
            //At some point I'll put the triggering of notes in VMM timeline but for now this is coming from an Ableton M4L device.
            oscMainApp->sendOSCtestData(m.getArgAsInt32(0), m.getArgAsInt32(1));
            
            
        }
        
        //triggered message recieved
        if(isAbletonClipTriggered){
            
            
            ofLogNotice("OSC_TRIGGERED") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --CLIP TRIGGERED ON";
            
            //LOG TO VMM
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
                
                //LOG TO VMM
                string msg = "OSC_TRIGGERED " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP TRIGGERED OFF (tranport running still)";
                oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            } else {
                //wait for playing_slot_index
                waitForClipPlaying = true;
                ofLogNotice("OSC_TRIGGERED") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " --CLIP TRIGGERED OFF (waitForClipPlaying)";
                
                //LOG TO VMM
                string msg = "OSC_TRIGGERED " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP TRIGGERED OFF (waitForClipPlaying)";
                oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            }
            
        }
    } else if (m.getAddress() == "/playing_slot_index"){
        if (m.getArgAsInt32(1) == -2){
            isAbletonClipPlaying = false;
            
            //LOG TO VMM
            string msg = "/playing_slot_index - isAbletonClipPlaying = false";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
        } else if (m.getArgAsInt32(1) == -1){
            //what does -1 do? ask LOM.
            
            //LOG TO VMM
            string msg = "/playing_slot_index - isAbletonClipPlaying = undefined";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
        } else {
            isAbletonClipPlaying = true;
            
            //LOG TO VMM
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
                
                //LOG TO VMM
                string msg = "OSC_PLAY " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP PLAY ON (waitForClipPlaying)";
                oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
                
                //20180304 - tried moving sendOscdata here.  data is recieved AFTER first note still.
                //TODO: create a object to hold next params.
                //oscMainApp->sendOSCtestData(m.getArgAsInt32(0), m.getArgAsInt32(1));
                oscMainApp->playTLclip(m.getArgAsInt32(0), m.getArgAsInt32(1));
                
            } else {
                //play the clip
                ofLogNotice("OSC_PLAY") << m.getAddress() << " "
                << m.getArgAsInt32(0) << " "
                << m.getArgAsInt32(1)
                << " --CLIP PLAY ON (start timeline)";
                
                //LOG TO VMM
                string msg = "OSC_PLAY " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP PLAY ON (start timeline)";
                oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
                
                //TODO: create a object to hold next params.
                //20180304 - tried moving sendOscdata here.  data is recieved AFTER first note still.
                //oscMainApp->sendOSCtestData(m.getArgAsInt32(0), m.getArgAsInt32(1));
                oscMainApp->playTLclip(m.getArgAsInt32(0), m.getArgAsInt32(1));
                
            }
            
        } else {
            
            ofLogNotice("OSC_IN")   << m.getAddress() << " "
            << m.getArgAsInt32(0) << " "
            << m.getArgAsInt32(1)
            << " --CLIP STOP (stop timeline)";
            
            //LOG TO VMM
            string msg = "OSC_IN " + ofToString(m.getAddress()) + " " + ofToString(m.getArgAsInt32(0)) + " " + ofToString(m.getArgAsInt32(1)) + " --CLIP STOP (stop timeline)";
            oscMainApp->OSCsendMessage(m.getArgAsInt32(0), "LINK", msg);
            
            //NOTE: argument does NOTHING YET!!!!!
            oscMainApp->stopTLclip(m.getArgAsInt(0));
            
            waitForClipPlaying = false;
        }
        
    }//end if
}//end function
