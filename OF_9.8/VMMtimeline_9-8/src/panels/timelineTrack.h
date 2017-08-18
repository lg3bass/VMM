//
//  timelineTrack.h
//  VMMtimeline_9-8
//
//  Created by Robert White III on 7/18/17.
//
//
#pragma once

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
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    void displayTimelines(bool _showTimeline);    
    void enableTimelines(bool _enable);
    
    void showSelectedTimelineTrack(int _track);
    
    void addTLTrack(int _track, int _page, string _name, int _type);
    void remTLTrack(int _track, int _page, string _name);
    
    void setPage(int _track, int _page);
    void highlightFocuedTrack(int _track, string _name);
    
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
