//
//  linkModule.h
//  VMMtimeline_9-8
//
//  Created by Robert White III on 7/15/17.
//
//
#pragma once

#ifndef linkModule_h
#define linkModule_h

#include "ofMain.h"
#include "ofxAbletonLink.h"

#endif /* linkModule_h */

class linkModule {

    public:
    
        int lbeat;//last beat
        int nbeat;//current beat
    
        void setup(ofBaseApp* appPtr);
        void draw();
        void runAbletonLink(ofxAbletonLink &linkObj);
    
        ofxAbletonLink link;
    
};
