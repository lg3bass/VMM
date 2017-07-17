//
//  abletonlink.h
//  VMMtimeline_9-8
//
//  Created by Robert White III on 7/15/17.
//
//
#pragma once

#ifndef abletonlink_h
#define abletonlink_h

#include "ofMain.h"
#include "ofxAbletonLink.h"

#endif /* abletonlink_h */


class abletonLinkEngine {
    
public:
    
    int lbeat;//last beat
    int nbeat;//current beat
    
    void setup(ofBaseApp* appPtr);
    void draw();
    void runAbletonLink(ofxAbletonLink &linkObj);
    
    ofxAbletonLink link;
    
};
