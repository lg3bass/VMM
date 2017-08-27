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
    
    void drawTrackData();
    void drawPageData(int _mt);
    void toggleDrawTrackData();
    bool showTrackData;
    
    //intercept event from the timeline
    void actOnFocus(ofxTLTrackEventArgs & args);
    void actOnLossFocus(ofxTLTrackEventArgs & args);
    
    //add and remove tracks
    void addTLChannel(string _name, int _type);
    void remTLChannel();
    
    //save and load functions
    string getFilePath(int _track, int _page, int _clip);
    
    void saveTLPage(int _track, int _page, int _clip);
    void saveTLTrackPages();
    void saveTLAllTracks();
        
    void loadTLPage(int _track, int _page, int _clip);
    void loadTLTrackPages();
    void loadTLAllTracks();
    
    #pragma mark - PLAY FUNCTIONS
    void playTLclip(int _track, int _clip);
    void stopTLclip(int _clip);
    
    void setMeasureLoop();
    
    #pragma mark - OSC
    void sendOSCfromTimeline(string _param);

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
