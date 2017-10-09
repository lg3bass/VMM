#include "ofApp.h"


//--------------------------------------------------------------
//timePanel functions
//--------------------------------------------------------------
void ofApp::enableOscOut(){
    //cout << "ofApp::enableOscOut()" << endl;
    headerPanel.toggleDrive();
    timePanel.data.TL.tracks[timePanel.data.getTrack()].enableOscOut = !timePanel.data.TL.tracks[timePanel.data.getTrack()].enableOscOut;
    
}

//--------------------------------------------------------------
void ofApp::setControllerData(string name, int data){
    
    if (name == "TRACK") {
        
        timePanel.setTLTrack(data);
    

        
        headerPanel.setClipUI(timePanel.data.getClip(data));
        headerPanel.setPageUI(timePanel.data.getPage(data));
        headerPanel.setUImeasures(timePanel.data.getTrackMeasures(data));
        
        
    } else if(name == "PAGES") {
        
        timePanel.setPage(data);
        
    } else if(name == "CLIP"){
       
        timePanel.setClip(data);
        
    }
    
}


//--------------------------------------------------------------
void ofApp::addChannel(string name, int type){
    //add a track on the current selected page
    timePanel.addTLChannelToSelected(name, type);
}

//--------------------------------------------------------------
void ofApp::remChannel(){
    //remove a track on the current selected page
    timePanel.remTLChannel();
}

//--------------------------------------------------------------
void ofApp::saveTLPage(){
    //saves the current selected page
    timePanel.saveTLPage(timePanel.data.getTrack(), timePanel.data.getPage(), timePanel.data.getClip());
}

//--------------------------------------------------------------
void ofApp::saveTLTrackPages(){
    cout << "ofApp::saveTLTrackPages()" << endl;
    timePanel.saveTLTrackPages();
}

//--------------------------------------------------------------
void ofApp::saveTLAllTracks(){
    cout << "ofApp::saveTLAllTracks()" << endl;
}

//--------------------------------------------------------------
void ofApp::loadTLPage(){
    timePanel.loadTLPage(timePanel.data.getTrack(), timePanel.data.getPage(), timePanel.data.getClip());
}

//--------------------------------------------------------------
void ofApp::loadTLTrackPages(){
    cout << "ofApp::loadTLTrackPages()" << endl;
    timePanel.loadTLTrackPages();
    
    //TODO - ??? When the dropdown closes where is the best place set the dropdownOpen var to FALSE.
    //TEMP, Bob, Find a better place for this.  
    headerPanel.setDropdownOpen(false);
}

//--------------------------------------------------------------
void ofApp::loadTLAllTracks(){
    cout << "ofApp::loadTLAllTracks()" << endl;
}

//--------------------------------------------------------------
void ofApp::nextKey(){
    timePanel.data.setNextKey();
    displayKeyValue(0);
}

//--------------------------------------------------------------
void ofApp::prevKey(){
    timePanel.data.setPrevKey();
    displayKeyValue(0);
}

//--------------------------------------------------------------
void ofApp::setKeyVal(int _val){
    timePanel.data.setSelectedKeyValue(_val);
    
}

//--------------------------------------------------------------
void ofApp::setTimePanelEnabled(bool _val){
    //timePanel.timePanelEnabled = _val;
    timePanel.tracks.enableTimelines(_val);
}

//--------------------------------------------------------------
//headerPanel functions
//--------------------------------------------------------------
void ofApp::setBreadcrumb(){
    
    string selTrackOnPage = "";
        if(timePanel.data.getNumOfChannelsOnPage() > 0) {
            if(timePanel.data.getSelectedChannel() > -1){
                selTrackOnPage = timePanel.data.getSelectedChannelName();
            }
        } else {
            selTrackOnPage = "NULL";
        }
    
    string breadcrumbMsg = "CLIP " + ofToString(timePanel.data.getClip()+1) + " > PAGE " + ofToString(timePanel.data.getPage()+1) + " > " + timePanel.data.getSelectedChannelName();
    
    //set the breadcrumb ui element
    headerPanel.mainUI.breadcrumb->setLabel(breadcrumbMsg);
}

//--------------------------------------------------------------
void ofApp::displayKeyValue(int _val){
    
    if(_val == -1){
        headerPanel.mainUI.keyVal->setText("---");
    } else {
        if(timePanel.data.getNumOfChannelsOnPage()>0){
            ofVec2f key = timePanel.data.getSelectedKeyValue(timePanel.data.getSelectedKeyIndex());
            headerPanel.mainUI.keyVal->setText(ofToString(key.y));
        } else {
            headerPanel.mainUI.keyVal->setText("NULL");
        }
    }
}


//--------------------------------------------------------------
void ofApp::selectChannel(int _index){
    
    timePanel.data.setSelectedChannel(_index);
    timePanel.data.setSelectedKeyIndex(-1);
    displayKeyValue(-1);
    
}

//--------------------------------------------------------------
void ofApp::passTextValue(string _field, string _val){
    
    cout << "passTextValue: " << ofToString(_val) << endl;
    
    if(_field == "MEASURES"){
        timePanel.setTrackMeasures(timePanel.data.getTrack(), _val);
        
    } else if (_field == "BPM") {
        timePanel.data.setBPM(_val);
    
        
    } else if (_field == "FPS"){
        timePanel.data.setFPS(_val);
        
        
    } else if (_field == "LOOP") {
        timePanel.data.setLoop(_val);
        
        
    } else if (_field == "METER"){
        timePanel.data.setMeter(_val);
        
        
    } else if (_field == "BAR|BEAT|FRAME"){
        timePanel.data.setBarsBeatsFrames(_val);
        
    } else if (_field == "LOW"){
        
        timePanel.setChannelRangeLow(ofToFloat(_val));
        
    } else if (_field == "HIGH"){
        
        timePanel.setChannelRangeHigh(ofToFloat(_val));
        
        
    }


    
}

//--------------------------------------------------------------
void ofApp::setLinkSlider(int _beat){
    
    headerPanel.setBeat(_beat);
}

//--------------------------------------------------------------
void ofApp::playTLclip(int _track, int _clip){
    
    timePanel.playTLclip(_track, _clip);
    
    //What Track,Clip is selected on this track
    if(_track == timePanel.data.TL.selected_track){
        
        cout << "You are on the selected track!" << endl;
        //only if you are on the selected track, page, clip.
        headerPanel.setClipUI(_clip);
        
    }
    

}

//--------------------------------------------------------------
void ofApp::stopTLclip(int _clip){
    
    //NOTE: _clip does NOTHING!!! 
    timePanel.stopTLclip(_clip);
    
}
