//
//  timelineData.cpp
//  VMM_UI_design
//
//  Created by Robert White III on 7/2/17.
//
//

#include "timelineData.h"
#include <regex>

//-------------------------------------------------
timelineData::timelineData(){
    for(int i = 0;i<NUMBER_OF_TRACKS;i++){              //add blank tracks
        //add a track
        vmmTrack mytrack;
        mytrack.cuedToPlay = false;
        
        //add blank pages
        for(int p = 0;p<10;p++){
            
            page myPage;                                //add pages
            myPage.name = "PAGE_"+ofToString(p);
            myPage.selected_channel = 0;
            
            mytrack.tlPages.push_back(myPage);            
            
        }
        
        TL.tracks.push_back(mytrack);
        
    }
}

//-------------------------------------------------
void timelineData::setMeasures(string _measures){
    TL.measures = ofToInt(_measures);
    
}

//-------------------------------------------------
void timelineData::setBPM(string _bpm){
    TL.bpm = ofToInt(_bpm);
    
}

//-------------------------------------------------
void timelineData::setFPS(string _fps){
    TL.fps = ofToInt(_fps);
    
}

//-------------------------------------------------
void timelineData::setLoop(string _loop){
    TL.loop = ofToInt(_loop);
    
}

//-------------------------------------------------
void timelineData::setMeter(string _meter){
    
    std::regex re("\\s*(\\d+)\\s*/\\s*(\\d+)\\s*\\");
    std::smatch m;
    bool found = std::regex_search(_meter,m,re);
    
    cout << std::regex_search(_meter,m,re) << " - numerator:" << m[1] << " - denominator:" << m[2] << endl;

    if(found){
        
        TL.mBeats = ofToInt(m[1]);
        TL.mUnits = ofToInt(m[2]);
    }
    
}

//-------------------------------------------------
void timelineData::setBarsBeatsFrames(string _value){
    
    std::regex re("\\s*(\\d+)\\s*\\|\\s*(\\d+)\\s*\\|*\\s*(\\d*)\\s*");
    std::smatch m;
    
    bool found = std::regex_search(_value,m,re);
    
    cout << std::regex_search(_value,m,re) << " - bar:" << m[1] << " - beat:" << m[2] << " - frame:" << m[3] << endl;
    
    if(found){
        
        TL.bar = ofToInt(m[1]);
        TL.beat = ofToInt(m[2]);
        
        //TODO - calculate frame if none in given.
        TL.frame = ofToInt(m[3]);
        
        
    } else {
        
        cout << "Please format the field <bar>|<beat>|<frame>" << endl;
    }
    
    
}


//-------------------------------------------------
int timelineData::getTrack(){
    return TL.selected_track;
}

//-------------------------------------------------
void timelineData::setTrack(int _track){
    TL.selected_track = _track;
    
}

//-------------------------------------------------
int timelineData::getClip(int _track){
    return TL.tracks[_track].selected_clip;
}

//-------------------------------------------------
int timelineData::getClip(){
    return TL.tracks[getTrack()].selected_clip;
}

//-------------------------------------------------
void timelineData::setClip(int _clip){
    TL.tracks[getTrack()].selected_clip = _clip;
}

//-------------------------------------------------
int timelineData::getPage(int _track){
    return TL.tracks[_track].selected_page;
}

//-------------------------------------------------
int timelineData::getPage(){
    return TL.tracks[getTrack()].selected_page;
}

//-------------------------------------------------
void timelineData::setPage(int _page){
    TL.tracks[getTrack()].selected_page = _page;
}

//-------------------------------------------------
bool timelineData::getCuedToPlay(int _track){
    return TL.tracks[_track].cuedToPlay;
}

//-------------------------------------------------
bool timelineData::getCuedToPlay(){
    return TL.tracks[getTrack()].cuedToPlay;
}

//-------------------------------------------------
void timelineData::addtlTrack(string _name, int _type){
    
    channel newTrack;
    newTrack.name = _name;
    newTrack.type = channelType(_type);
    newTrack.selected_key = -1;
    
    for(int k=0;k<3;k++){
        
        key ky;
        ky.frm = 15*k;
        ky.val = 100*k;
    
        newTrack.keyframes.keys.push_back(ky);
        
    }
    
    TL.tracks[getTrack()].tlPages[getPage()].tlChannels.push_back(newTrack);
    
}

//-------------------------------------------------
void timelineData::remtlTrack(){
    //note: currently this removes the current selected timeline and then selects index 0.
    int currentTrackOnPage = TL.tracks[getTrack()].tlPages[getPage()].selected_channel;
    
    //erase at index. (source: //stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index)
    TL.tracks[getTrack()].tlPages[getPage()].tlChannels.erase(TL.tracks[getTrack()].tlPages[getPage()].tlChannels.begin()+currentTrackOnPage);
    TL.tracks[getTrack()].tlPages[getPage()].selected_channel = 0;  //set selected to 0;
}


//-------------------------------------------------
int timelineData::getSelectedChannel(){
    return TL.tracks[getTrack()].tlPages[getPage()].selected_channel;
}

//-------------------------------------------------
void timelineData::setSelectedChannel(int _page){
    TL.tracks[getTrack()].tlPages[getPage()].selected_channel = _page;
    
    setSelectedKeyIndex(-1);
    
    
    ofLog() << "Selected - Page " << ofToString(getPage()) << " Timeline " << getSelectedChannelName(_page);
    
}

//-------------------------------------------------
string timelineData::getSelectedChannelName(int _pageIndex){
    return TL.tracks[getTrack()].tlPages[getPage()].tlChannels[_pageIndex].name;
}


//-------------------------------------------------
int timelineData::getNumOfChannelsOnPage(){
    
    int num_tracks_on_page = TL.tracks[getTrack()].tlPages[getPage()].tlChannels.size();
        
    return num_tracks_on_page;
    
}

//-------------------------------------------------
int timelineData::getNumOfKeysInChannel(){
    return TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys.size();
}


//-------------------------------------------------
ofVec2f timelineData::getSelectedKeyValue(int _selKey){
    
    int kf = TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys[_selKey].frm;
    float kv = TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys[_selKey].val;
    
    ofVec2f key = ofVec2f(kf,kv);
    
    return key;
}

//-------------------------------------------------
int timelineData::getSelectedKeyIndex(){
    
    return TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].selected_key;
    
}

//-------------------------------------------------
void timelineData::setSelectedKeyIndex(int _index){
    TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].selected_key = _index;
}

//-------------------------------------------------
void timelineData::setNextKey(){
    
    if(getNumOfChannelsOnPage()>0){
        int k = getSelectedKeyIndex();
        
        if(k < getNumOfKeysInChannel()-1){
            k++;
            
        } else {
            k = 0;
        }
       
        setSelectedKeyIndex(k);
    }
    
}

//-------------------------------------------------
void timelineData::setPrevKey(){
    cout << "setPrevKey()";
    if(getNumOfChannelsOnPage()>0){
        int k = getSelectedKeyIndex();
        
        if(k == 0){
            k = getNumOfKeysInChannel()-1;
            
        } else {
            k--;
        }
        
        setSelectedKeyIndex(k);
        
    }
    
}

//-------------------------------------------------
void timelineData::setSelectedKeyValue(int _val){
    cout << "setSelectedKeyValue" << endl;
    
    TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys[getSelectedKeyIndex()].val = _val;
    
    
}
