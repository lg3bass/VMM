//
//  oscHandler.h
//  VMMtimeline_9-8

#pragma once



#include "ofMain.h"
#include "ofxOsc.h"

class oscHandler {
    
public:
    
    bool isAbletonTransportRunning = false;
    bool isAbletonClipTriggered = false;
    bool isAbletonClipPlaying = false;
    int currentFiredSlotIndex = -1;
    int currentPlayingSlotIndex = -2;
    
    oscHandler();
    
    void setup(ofBaseApp* appPtr);
    void processOSCmessage(ofxOscMessage &m);
    
    
private:
    
    bool waitForClipPlaying = false;
    
    
    
    
};
