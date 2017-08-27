//
//  timelineData.h
//  VMM_UI_design
//
//  Created by White, Bob on 6/22/17.
//
//
#pragma once

#define NUMBER_OF_TRACKS 10

#include "ofMain.h"

class timelineData{
    
public:
    
    enum channelType {tlCurves,tlKeyframes,tlMarkers};

    struct key {
        int frm;
        float val;
    };
    
    struct channel {
        string name;
        channelType type;
        int selected_key;
        struct keys{
            vector<key> keys;
            int selected_key;
            float clampValL = 0.0;
            float clampValH = 100.0;
        } keyframes;
    };
    
    struct page {
        string name;
        vector<channel> tlChannels;
        int selected_channel;
    };
    
    struct vmmTrack {
        vector<page> tlPages;
        int selected_clip = 0;
        int selected_page = 0;
        int measureCount = 0;
        int measureLength = 4;
        int beatCount = 0;
        int beatLength = 16;
        bool cuedToPlay = false;
        bool enableOscOut = false;
    };
    
    struct tlData {
        int selected_track = 0;
        vector<vmmTrack> tracks;
        int measures = 8;                   //not used anymore
        int measureCount = 0;               //not used anymore
        int bpm = 120;
        int fps = 30;
        int loop = 300;
        int mBeats = 4;
        int mUnits = 4;
        int bar = 0;
        int beat = 0;
        int frame = 0;
        
        bool snap = false;
        bool drive = false;
        bool osc = false;
        
    } TL;                                           //change to TL
    
    //constuctor
    timelineData();
    
    //GLOBAL DATA
#pragma mark - tlData
    int getTrack();                                 //return the current selected track
    void setTrack(int _track);                      //set current track

    void setMeasures(string _measures);
    void setBPM(string _bpm);
    void setFPS(string _fps);
    void setLoop(string _loop);
    void setMeter(string _meter);
    void setBarsBeatsFrames(string _value);

    
    //TRACK SPECIFIC DATA
#pragma mark - vmmTrack

    int getClip(int _track);                        //return the current selected clip for a specific track
    int getClip();                                  //return the current selected clip on current track
    void setClip(int _clip);                        //set current clip on current track
    
    int getPage(int _track);                        //return the current selected page for a specific track
    int getPage();                                  //return the current selected page on current track
    string getPageName(int _page);                  //return the current page name for a specific page
    string getPageName();                           //return the current selected page name
        
    void setPage(int _page);                        //set the current page on current track
    
    bool getCuedToPlay(int _track);                 //return the flag if to play ALL the timelines on a page for a specific track
    bool getCuedToPlay();                           //return the flag if to play ALL the timelines on a page for current track
    void setCuedToPlay(int _track, bool _status);   //set flag to play ALL the timelines on a page for a specific track
    
    //ADD AND REMOVE TIMELINES TO A PAGE
    void addtlTrack(int _track, int _page, string _name, int _type);       //add a timeline track to a page
    //void addtlTrack(int _track, string _page, string _name, int _type);       //add a timeline track to a page
    void remtlTrack(string _name);                  //remove a timeline from the current page.
    
    int getSelectedChannel();                       //returns the index to the selected timeline on a page.
    void setSelectedChannel(int _channel);          //set the current selected timeline(channel) on a page (by index)
    void setSelectedChannel(string _channel);       //set the current selected timeline(channel) on a page (by index)
    string getSelectedChannelName();                //return the name of the selected timeline(channel) on a page.
    string getChannelName(int _channel);
    int getNumOfChannelsOnPage();                   //return the number of channels on a page.
    int getNumOfChannelsOnPage(int _page);          //return the number of channels on a page (by index).
    
    
#pragma mark - KEYFRAMES
    int getNumOfKeysInChannel();
    ofVec2f getSelectedKeyValue(int _selKey);       //return the selected keyframe in vec2f format
    int getSelectedKeyIndex();
    void setSelectedKeyIndex(int _index);
    void setNextKey();
    void setPrevKey();
    void setSelectedKeyValue(int _value);
    
};
