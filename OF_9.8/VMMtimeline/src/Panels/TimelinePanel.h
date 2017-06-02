//
//  TimelinePanel.h
//  02_timlineLink_test

#pragma once

#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxDatGui.h"
#include "ofxAbletonLink.h"
#include "Panel.h"

#define PAGE_TRACKS_NAME "G Rotate"

class TimelinePanel : public Panel{
    
public:

    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void exit(){};
    
    void save(int track, int clip);
    void load(int track, int clip);
    
    void saveCurrent();
    void loadCurrent();
    void loadAllTracks();
    
    void play(int t, int c);
    void pause(int c);
    void stop(int c);
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void showSelectedTimelineTrack(int track);
    
    int calculateFramesInMeasures(int m, float bpm, int fps);
    void runAbletonLink(ofxAbletonLink &linkObj);
    
    void sendOSCfromTimeline();
    
    //EXPERIMENTS:  targeting timeline
    void alterTimeline(int _val);                                               //add keys
    void addKeyFrameToCurrentTrack(float _val, float _timeInMiliseconds);       //add keys at a specific time
    void setRange(ofRange newrange);
    
    vector<ofxTimeline*> timelines;
    

    //settings
    //-----------------------------------
    void loadSettings(int track, int clipSlot);
    void saveSettings(int track, string clipSlot="");
    
    void setMeasureLoop();
    void setMeasuresAtTempo(int _measures, float _tempo);
    
    //bool getFocused(){return gTrackName->getFocused();}//return what is selected
    
    //modifier keys
    bool modkey;
    bool ctrlKey;
    bool rAltKey;
    bool lAltKey;
    bool lShiftKey;
    bool rShiftKey;

private:
    
    //bool cuedToPlay;
    
    //int currentLoaded;
    
    int measures;
    int duration;
    int lbeat;//last beat
    int nbeat;//current beat
    int measureCount;
    int _frameRate;
    float _bpm;
    
    ofxAbletonLink link;
    
    void savePageSettings(string clipSlot,string pageName);
    
    vector<float> _markers;
    
    
};
