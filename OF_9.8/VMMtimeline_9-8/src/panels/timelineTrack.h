//
//  timelineTrack.h
//  VMMtimeline_9-8
//
//  Created by Robert White III on 7/18/17.
//
//

#ifndef timelineTrack_h
#define timelineTrack_h

#include "ofMain.h"
#include "ofxTimeline.h"

#endif /* timelineTrack_h */

class timelineTrack {
    
public:
    
    timelineTrack();
    void init(int _x, int _y, int _w, int _h);
    void draw();
    void displayTimelines(bool _showTimeline);    
    void enableTimelines(bool _enable);
    
    int duration;
    int _x;
    int _y;
    int _w;
    int _h;
    int _bpm;
    int _frameRate;
    
    vector<ofxTimeline*> timelines;
    
    bool showHideFlag;
    
private:
    

    
    
    
    
    
    
};
