//
//  timelinePanel.h
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//
#pragma once

#ifndef timelinePanel_h
#define timelinePanel_h

#include "ofMain.h"
#include "Panel.h"
#include "timelineData.h"
#include "timelineTrack.h"

#endif /* timelinePanel_h */

class timelinePanel : public Panel{

public:
    
    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void runTimelines(int _track);
    void exit(){};
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
#pragma mark - DEBUG/STATS
    
    void drawTrackData();
    void drawPageData(int _mt);
    void toggleDrawTrackData();
    bool showTrackData;

#pragma mark - SELECT CHANNELS
    
    //intercept event from the timeline
    void actOnFocus(ofxTLTrackEventArgs & args);
    void actOnLossFocus(ofxTLTrackEventArgs & args);

#pragma mark - ADD/REMOVE
    
    //add and remove tracks
    void addTLChannel(string _name, int _type);
    void remTLChannel();
    
#pragma mark - SAVE/LOAD
    
    //save and load functions
    string getFilePath(int _track, int _clip);
    
    void saveTLPage(int _track, int _page, int _clip);
    void saveTLTrackPages();
    void saveTLAllTracks();
        
    void loadTLPage(int _track, int _page, int _clip);
    void loadTLTrackPages();
    void loadTLAllTracks();
    
#pragma mark - PLAY FUNCTIONS
    void setClip(int _clip, int _track);
    void setClip(int _clip);
        
    void playTLclip(int _track, int _clip);
    void stopTLclip(int _clip);                             //argument does NOTHING!
    
    void setMeasureLoop(int _track);
    
    void setTrackMeasures(int _track, string _measures);
    
#pragma mark - OSC
    void sendOSCfromTimeline(int _track, string _param);

    //setup the 2 large sections
    timelineData data;
    timelineTrack tracks;
    
#pragma mark - TESTS
    void testKeyframeFunction(int _track, string _channelName);
    
private:
    
    ofTrueTypeFont	verdana9;
    ofColor bordCol;
    int bordWidth;

};
