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
    void update();
    int beat();
    void setMeter(int _quantum);
    
    void blinkingBottomBar(float _top, float _bottom);
    
    ofxAbletonLink link;
    int lbeat;//last beat
    int nbeat;//current beat
    int quantum;
    

    
private:
    void runAbletonLink(ofxAbletonLink &linkObj);
    
    int b;
    
};
