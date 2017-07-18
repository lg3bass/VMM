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
    abletonLinkEngine();
    void setup(ofBaseApp* appPtr);
    void draw();
    int beat();
    
    ofxAbletonLink link;
    int lbeat;//last beat
    int nbeat;//current beat
    
private:
    void runAbletonLink(ofxAbletonLink &linkObj);
    
};
