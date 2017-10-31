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
        headerPanel.setMeasuresUI(timePanel.data.getClipMeasures(data,timePanel.data.getClip()));
        headerPanel.setMeterUI(timePanel.data.getMeter(timePanel.data.getTrack(),data));
        
        
    } else if(name == "PAGES") {
        
        timePanel.setPage(data);
    } else if(name == "CLIP"){
       
        //1. load the clip.xml
        //2. set number of measures in clip
        //3. set the duration in frames of the clip.
        timePanel.loadTLClip(timePanel.data.getTrack(), data);
        
        //4. set the clip in the current track
        //5. load the track keyframe data.
        //6. set the duration in the timeline on the track.
        timePanel.setClip(data);
        
        //UI
        int m = timePanel.data.getClipMeasures(timePanel.data.getTrack(),data);
        headerPanel.setMeasuresUI(m);
        headerPanel.setMeterUI(timePanel.data.getMeter(timePanel.data.getTrack(),data));

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

#pragma mark - ofAppRouter.cpp save/load functions
//--------------------------------------------------------------
void ofApp::setTLProject(string dialogMsg){
    
    
    //File Dialog
    ofFileDialogResult saveFileResult = ofSystemSaveDialog("new_project.vmm", dialogMsg);
    
    if (saveFileResult.bSuccess){
        //setup where to save the project.
        timePanel.setProjectPathAndFile(saveFileResult);
    }
}


//--------------------------------------------------------------
void ofApp::saveTLPage(){
    if(!timePanel.projectSet){
        //File Dialog
        ofFileDialogResult saveFileResult = ofSystemSaveDialog("new_project.vmm", "Create a project file (.vmm)");
        
        if (saveFileResult.bSuccess){
            //setup where to save the project.
            timePanel.setProjectPathAndFile(saveFileResult);
        } else {
            ofLogNotice("SAVE") << "User hit cancel";
            return;
        }
    }
    
    if(timePanel.projectSet){
        //saves the current selected page ONLY
        timePanel.saveTLProject();
        timePanel.saveTLPage(timePanel.data.getTrack(), timePanel.data.getPage(), timePanel.data.getClip());
        
    } else {
        cout << "No project setup" << endl;
    }

}

//--------------------------------------------------------------
void ofApp::saveTLTrackPages(){
    if(!timePanel.projectSet){
        //File Dialog
        ofFileDialogResult saveFileResult = ofSystemSaveDialog("new_project.vmm", "Create a project file (.vmm)");
        
        if (saveFileResult.bSuccess){
            //setup where to save the project.
            timePanel.setProjectPathAndFile(saveFileResult);
        } else {
            ofLogNotice("SAVE") << "User hit cancel";
            return;
        }
    }
    
    if(timePanel.projectSet){
        //saves ALL the pages in the track
        timePanel.saveTLProject();
        timePanel.saveTLTrackPages();
        
    } else {
        cout << "No project setup..." << endl;
    }

}

//--------------------------------------------------------------
void ofApp::saveTLAllTracks(){
    if(!timePanel.projectSet){
        //File Dialog
        ofFileDialogResult saveFileResult = ofSystemSaveDialog("new_project.vmm", "Create a project file (.vmm)");
        
        if (saveFileResult.bSuccess){
            //setup where to save the project.
            timePanel.setProjectPathAndFile(saveFileResult);
        } else {
            ofLogNotice("SAVE") << "User hit cancel";
            return;
        }
    }
    
    if(timePanel.projectSet){
        //saves ALL the pages in the track
        timePanel.saveTLProject();
        timePanel.saveTLAllTracks();
        
    } else {
        cout << "No project setup..." << endl;
    }

}

//--------------------------------------------------------------
void ofApp::loadTLPage(){
    if(!timePanel.projectSet){
        //setTLProject("Select a project file (.vmm)");
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a project file (.vmm)");
        
        if (openFileResult.bSuccess){
            timePanel.setProjectPathAndFile(openFileResult);
        }else {
            ofLogNotice("SAVE") << "User hit cancel";
            return;
        }
        
    }
    
    if(timePanel.projectSet){
        timePanel.loadTLPage(timePanel.data.getTrack(), timePanel.data.getPage(), timePanel.data.getClip());
        cout << "Loading Page... " << endl;
        
        //TODO - ??? When the dropdown closes where is the best place set the dropdownOpen var to FALSE.
        //TEMP, Bob, Find a better place for this.
        headerPanel.setDropdownOpen(false);
    } else {
        cout << "No project setup..." << endl;
    }

}

//--------------------------------------------------------------
void ofApp::loadTLTrackPages(){
    
    if(!timePanel.projectSet){
        //setTLProject("Select a project file (.vmm)");
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a project file (.vmm)");
        
        if (openFileResult.bSuccess){
            timePanel.setProjectPathAndFile(openFileResult);
        }else {
            ofLogNotice("SAVE") << "User hit cancel";
            return;
        }
        
    }
    
    if(timePanel.projectSet){
        cout << "Loading Page... " << endl;
        timePanel.loadTLTrackPages();
        
        //TODO - ??? When the dropdown closes where is the best place set the dropdownOpen var to FALSE.
        //TEMP, Bob, Find a better place for this.
        headerPanel.setDropdownOpen(false);
        
    } else {
        cout << "No project setup..." << endl;
    }
    
}

//--------------------------------------------------------------
void ofApp::loadTLAllTracks(){
    if(!timePanel.projectSet){
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a project file (.vmm)");
        
        if (openFileResult.bSuccess){
            timePanel.setProjectPathAndFile(openFileResult);
        }else {
            ofLogNotice("SAVE") << "User hit cancel";
            return;
        }
        
    }
    
    if(timePanel.projectSet){
        cout << "Loading All Tracks and Pages... " << endl;
        timePanel.loadTLAllTracks();
        
        //TODO - ??? When the dropdown closes where is the best place set the dropdownOpen var to FALSE.
        //TEMP, Bob, Find a better place for this.
        headerPanel.setDropdownOpen(false);
        
    } else {
        cout << "No project setup..." << endl;
    }    
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
        timePanel.setMeasuresInClip(timePanel.data.getTrack(), _val);
        
    } else if (_field == "BPM") {
        
        //TODO -
        //just set the data.bpm
        timePanel.data.setBPM(_val);
        
        //set the timeline frames.
        //timePanel.tracks.timelines[0]->setDurationInFrames(480);
        timePanel.tracks.timelines[0]->setNewBPM(timePanel.data.getBPM());
        
        //set the ableton link tempo
        AL.setTempo(timePanel.data.getBPM());
    
        
    } else if (_field == "FPS"){
        timePanel.data.setFPS(_val);
        //TODO - 
        timePanel.tracks.timelines[0]->setFrameRate(timePanel.data.getFPS());
        
        
    } else if (_field == "LOOP") {
        //timePanel.data.setLoop(_val);
        
        //set duration
        timePanel.tracks.timelines[0]->setDurationInFrames(ofToInt(_val));
        
        
    } else if (_field == "METER"){
        timePanel.data.setMeter(_val);
       
        
        
    } else if (_field == "BAR|BEAT|FRAME"){
        timePanel.data.setBarsBeatsFrameData(_val);
        
    } else if (_field == "LOW"){
        
        timePanel.setChannelRangeLow(ofToFloat(_val));
        
    } else if (_field == "HIGH"){
        
        timePanel.setChannelRangeHigh(ofToFloat(_val));
        
        
    }


    
}

//--------------------------------------------------------------
void ofApp::setLinkSlider(int _beat){
    
    headerPanel.setBeatUI(_beat);
}

//--------------------------------------------------------------
void ofApp::playTLclip(int _track, int _clip){
    
    timePanel.playTLclip(_track, _clip);
    
    //What Track,Clip is selected on this track
    if(_track == timePanel.data.TL.selected_track){
        
        //only if you are on the selected track, page, clip.
        headerPanel.setClipUI(_clip);
        
    }
}

//--------------------------------------------------------------
void ofApp::stopTLclip(int _clip){
    
    //NOTE: _clip does NOTHING!!! 
    timePanel.stopTLclip(_clip);
    
}
