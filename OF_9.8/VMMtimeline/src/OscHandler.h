//
//  OscHandler.h
//  02_timlineLink_test

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class OscHandler {
    
public:
    
    bool isAbletonTransportRunning = false;
    bool isAbletonClipTriggered = false;
    bool isAbletonClipPlaying = false;
    int currentFiredSlotIndex = -1;
    int currentPlayingSlotIndex = -2;
    
    
    OscHandler();
    
    void setup(ofBaseApp* appPtr);
    void processOSCmessage(ofxOscMessage &m);
    
    
    
    
private:
    
    bool waitForClipPlaying = false;
    
    
    
    
};