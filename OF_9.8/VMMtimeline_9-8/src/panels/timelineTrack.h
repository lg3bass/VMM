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
#include "ofxTLVMMControl.h"

#endif /* timelineTrack_h */

class timelineTrack {
    
public:
    
    timelineTrack();
    void init(int _x, int _y, int _w, int _h);
    void draw();
    void update();
    
    void keyPressed(int key);
    void keyReleased(int key);
            
    //display functions
    void displayTimelines(bool _showTimeline);    
    void enableTimelines(bool _enable);
    void showSelectedTimelineTrack(int _track);
    void enableVMMControlTrack(int _track);     //TODO: not used anymore
    
    void addTLTrack(int _track, string _page, string _name, int _type, float _low = -50, float _high = 50);
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
    
    void playbackLoopedEvent(ofxTLPlaybackEventArgs &e);
    
private:
    

    
    
    
    
    
    
};
