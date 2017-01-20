//
//  oscRouter.h
//  ofxObjLoader_test10
//
//  Created by bob white III on 4/28/16.
//
//

#pragma once

#include "ofMain.h"
#include "bwUtil.h"
#include "ofxOsc.h"
#include "vboMeshObj.h"
//#include "trackParams.h"


class oscRouter {

public:
    int idx;
    int VMMnoteID;
    float amplitude;
    int noteLength;
    
    int numberOfSequences;
    
    oscRouter();
    void setup();
    void processOSCmessage(ofxOscMessage &m, vector<vboMeshObj> &tracks, int num_tracks);
    
    void transformTrack();
    
private:
    



};