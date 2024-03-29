//
//  timelineData.h
//  VMM_UI_design
//
//  Created by White, Bob on 6/22/17.
//
//
#pragma once

#define NUMBER_OF_TRACKS 10
#define NUMBER_OF_PAGES 10

#include "ofMain.h"
#include "ofRange.h"

class timelineData{
    
public:
    
    enum channelType {tlCurves,tlBangs,tlSwitches,tlFlags,tlColors};

    struct key {
        int frm;
        float val;
    };
    
    struct channel {
        string name;
        channelType type;
        int selected_key;
        ofRange channelRange;
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
    
    struct clip {
        int numberOfMeasures = 8;
        int duration = 120;
        bool loop = true;
        bool mute = false;
        bool solo = false;
        int mBeats = 4;
        int mUnits = 4;
    };
    
    struct vmmTrack {
        vector<page> tlPages;
        vector<clip> tlClips;
        int selected_clip = 0;
        int selected_page = 0;
        int measureCount = 0;
        //int measureLength = 4;
        int beatCount = 0;
        int beatLength = 16;
        bool cuedToPlay = false;
        bool enableOscOut = false;
        int lbeat = -1;//last beat
        int nbeat = -1;//current beat
        int duration = 250;//delete me
        
        bool renderTrackChan = false;
        bool isRenderingChan = false;
    };
    
    struct tlData {
        int selected_track = 0;
        vector<vmmTrack> tracks;
        float bpm = 120.0;
        int fps = 30;
        int loop = 300;
        int bar = 0;
        int beat = 0;
        int frame = 0;
        
        bool snap = false;
        bool drive = false;
        bool render = false;
        bool chan = false; //"CHAN"
        
        bool playing = false;
        
    } TL;                                           //change to TL
    
    //constuctor
    timelineData();
    
    //GLOBAL DATA
#pragma mark - tlData
    int getTrack();                                 //return the current selected track
    void setTrack(int _track);                      //set current track

    void setBPM(string _bpm);
    float getBPM();
    
    void setFPS(string _fps);
    float getFPS();
    
    void setMeter(string _meter);
    string getMeter(int _track, int _clip);
    
    void setBarsBeatsFrameData(string _value);
    
    int calculateFramesInMeasures(int m, float bpm, int fps);
    
    //TRACK SPECIFIC DATA
#pragma mark - vmmTrack
    void setClipMeasures(int _track, int _measures);
    int getClipMeasures(int _track, int _clip);
    int getClipDuration(int _track);
    
    //clips
    int getClip(int _track);                        //return the current selected clip for a specific track
    int getClip();                                  //return the current selected clip on current track
    void setClip(int _clip);                        //set current clip on current track
    void setClip(int _clip, int _track);            //set current clip on a specific track
    
    //void setNumberOfMeasures(int m);//not needed
    
    void setLoop(string _loop);

    void setMute(bool muteStatus);
    void setSolo(bool soloStatus);

    
    
    int getPage(int _track);                        //return the current selected page for a specific track
    int getPage();                                  //return the current selected page on current track
    string getPageName(int _page);                  //return the current page name for a specific page
    string getPageName();                           //return the current selected page name
        
    void setPage(int _page);                        //set the current page on current track
    
    bool getCuedToPlay(int _track);                 //return the flag if to play ALL the timelines on a page for a specific track
    bool getCuedToPlay();                           //return the flag if to play ALL the timelines on a page for current track
    void setCuedToPlay(int _track, bool _status);   //set flag to play ALL the timelines on a page for a specific track
    
    //ADD AND REMOVE TIMELINES TO A PAGE
    //add a timeline track to a page.  ofRange(_low, _high) are set by default.
    void addtlTrack(int _track, int _page, string _name, int _type, float _low=-100.0, float _high=100.0);
    void remtlTrack(string _name);                  //remove a timeline from the current page.
    
    int getSelectedChannel();                       //returns the index to the selected timeline on a page.
    void setSelectedChannel(int _channel);          //set the current selected timeline(channel) on a page (by index)
    void setSelectedChannel(string _channel);       //set the current selected timeline(channel) on a page (by index)
    string getSelectedChannelName();                //return the name of the selected timeline(channel) on a page.
    string getSelectedChannelOnTrackPage(int _track, int _page);
    string getChannelName(int _channel);
    string getChannelNameOnPage(int _page, int _channel);
    int getNumOfChannelsOnPage();                   //return the number of channels on a page.
    int getNumOfChannelsOnPage(int _page);          //return the number of channels on a page (by index).
    
    bool isChannelOnPage(string name);              //returns TRUE if the page contains a specific channel
    bool isChannelOnPage(string name, int _page);   //returns TRUE if the page contains a specific channel
#pragma mark - KEYFRAMES
    int getNumOfKeysInChannel();
    ofVec2f getSelectedKeyValue(int _selKey);       //return the selected keyframe in vec2f format
    int getSelectedKeyIndex();
    void setSelectedKeyIndex(int _index);
    void setNextKey();
    void setPrevKey();
    void setSelectedKeyValue(int _value);
    
#pragma mark - LINK
    void setNBeat(int _track, int _beat);
    void setLBeat(int _track, int _beat);
    int getNBeat(int _track);
    int getLBeat(int _track);
    
    bool isDownbeat(int _track);
    
};
