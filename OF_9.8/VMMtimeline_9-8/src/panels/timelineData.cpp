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
        mytrack.enableOscOut = false;
        
        //add blank pages
        for(int p = 0;p<NUMBER_OF_TRACKS;p++){
            
            page myPage;                                //add pages
            myPage.name = "P"+ofToString(p+1);
            myPage.selected_channel = -1;
            
            mytrack.tlPages.push_back(myPage);            
            
        }
        
        TL.tracks.push_back(mytrack);
        
    }
}

#pragma mark - TRACK

//-------------------------------------------------
int timelineData::getTrack(){
    return TL.selected_track;
}

//-------------------------------------------------
void timelineData::setTrack(int _track){
    TL.selected_track = _track;
    
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

#pragma mark - vmmTrack

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
string timelineData::getPageName(int _page){
    return TL.tracks[getTrack()].tlPages[_page].name;
}

//-------------------------------------------------
string timelineData::getPageName(){
    return TL.tracks[getTrack()].tlPages[getPage()].name;
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
void timelineData::setCuedToPlay(int _track, bool _status){
    TL.tracks[_track].cuedToPlay = _status;
}





//-------------------------------------------------
void timelineData::addtlTrack(int _track, int _page, string _name, int _type){
    
    channel newTrack;
    newTrack.name = _name;
    newTrack.type = channelType(_type);
    newTrack.selected_key = -1;
    
    //add dummy keys to the new track
    for(int k=0;k<3;k++){
        
        key ky;
        ky.frm = 15*k;
        ky.val = 100*k;
    
        newTrack.keyframes.keys.push_back(ky);
        
    }
    
    TL.tracks[_track].tlPages[_page].tlChannels.push_back(newTrack);
    
    
}



//-------------------------------------------------
void timelineData::remtlTrack(string _data){
    
    //determine the index of the TRACK
    for(int i=0; i<getNumOfChannelsOnPage();i++){
        
        string trackName = getChannelName(i);
        if(_data == trackName){
            
            cout << "timelineData::remtlTrack(" << _data << ")" << endl;
            TL.tracks[getTrack()].tlPages[getPage()].tlChannels.erase(TL.tracks[getTrack()].tlPages[getPage()].tlChannels.begin()+i);
            
            
        }
    }
    
    
    //NOT WORKING
    //erase at index. (source: //stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index)
    //TL.tracks[getTrack()].tlPages[getPage()].tlChannels.erase(TL.tracks[getTrack()].tlPages[getPage()].tlChannels.begin()+getSelectedChannel());

    
}


//-------------------------------------------------
int timelineData::getSelectedChannel(){
    return TL.tracks[getTrack()].tlPages[getPage()].selected_channel;
}

//-------------------------------------------------
void timelineData::setSelectedChannel(int _channel){
    TL.tracks[getTrack()].tlPages[getPage()].selected_channel = _channel;
    setSelectedKeyIndex(-1);                                                        //reset all the keys
    ofLog() << "Selected - Page " << ofToString(getPage()) << " Channel " << getChannelName(_channel);
    
}

//-------------------------------------------------
void timelineData::setSelectedChannel(string _channel){
    int channels_on_page = getNumOfChannelsOnPage();
    
    for (int i=0; i< channels_on_page; i++){
        if(_channel == getChannelName(i)){
            TL.tracks[getTrack()].tlPages[getPage()].selected_channel = i;
            ofLog() << "Selected - Page " << ofToString(getPage()) << " Channel " << getChannelName(i);
        }
    }
    setSelectedKeyIndex(-1);                                                        //reset all the keys

}

//-------------------------------------------------
string timelineData::getSelectedChannelName(){
    
    string channelName = "";
    
    if(getSelectedChannel() == -1) {
        channelName = "NULL";
    } else {
        //returns the name of a selected channel on a page.
        channelName = TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].name;
    }
    
    return channelName;
}

//-------------------------------------------------
string timelineData::getChannelName(int _channel){
    
    return TL.tracks[getTrack()].tlPages[getPage()].tlChannels[_channel].name;      //returns the name of a selected channel on a page.
}

//-------------------------------------------------
int timelineData::getNumOfChannelsOnPage(){
    
    int num_tracks_on_page = TL.tracks[getTrack()].tlPages[getPage()].tlChannels.size();
    return num_tracks_on_page;                                                      //returns how many channels are on a page.
    
}

//-------------------------------------------------
int timelineData::getNumOfChannelsOnPage(int _page){
    
    int num_tracks_on_page = TL.tracks[getTrack()].tlPages[_page].tlChannels.size();
    return num_tracks_on_page;                                                      //returns how many channels are on a page.
    
}

//-------------------------------------------------
int timelineData::getNumOfKeysInChannel(){
    return TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys.size();
}


//-------------------------------------------------
ofVec2f timelineData::getSelectedKeyValue(int _selKey){
    ofVec2f key;
    
    if(getSelectedChannel() > 0){
        int kf = TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys[_selKey].frm;
        float kv = TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys[_selKey].val;
        ofVec2f key = ofVec2f(kf,kv);
    } else {
        ofVec2f key = ofVec2f(0,0);
    }
    
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
