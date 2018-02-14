//
//  timelineTrack.cpp
//  VMMtimeline_9-8
//
//  Created by Robert White III on 7/18/17.
//
//

#include "timelineTrack.h"

#define NUMBER_OF_TRACKS 10
#define TRACK_DIR "TRACK"
#define CLIP_DIR "CLIP"

//-------------------------------------------------
timelineTrack::timelineTrack(){
    
    //setup the timelines
    timelines.reserve(NUMBER_OF_TRACKS);
    
    showHideFlag = true;
    
}

//-------------------------------------------------
void timelineTrack::init(int _x, int _y, int _w, int _h){
    duration = 250;
    _x = _x;
    _y = _y;
    _w = _w;
    _h = _h;
    int _bpm = 120;
    int _frameRate = 30;
    
    //SETUP THE TRACKS
    for(int i=0; i<NUMBER_OF_TRACKS; i++){
        ofxTimeline* t = new ofxTimeline();
        
        t->setupFont("gui_assets/timeline_GUI/NewMedia Fett.ttf", 8);
        
        //t->removeCocoaMenusFromGlut("02_timlineLink_testDebug");
        t->setup();
        
        //sets the directory where the default xml
        t->setWorkingFolder(TRACK_DIR "_" + ofToString(i) + "/");
        
        t->setAutosave(false);
        t->setSpacebarTogglePlay(false);
        t->setLockWidthToWindow(false);
        t->setDurationInFrames(duration);
        t->setOffset(ofVec2f((float)_x+88, (float)_y));
        t->setMinimalHeaders(true);
        t->setWidth((float)_w-104);
        t->setBPM(_bpm);
        t->setFrameRate(_frameRate);
        t->setLoopType(OF_LOOP_NORMAL);
        t->setShowBPMGrid(true);
        t->setFrameBased(true);
        t->setInPointAtFrame(0);
        t->setOutPointAtFrame(duration);
        t->setShowZoomer(true);
        t->setShowInoutControl(false);
        
        //set the initial page name
        t->setPageName("P1", 0);
        
        for(int j=2;j<11;j++){
            t->addPage("P"+ofToString(j));
        }

        t->setShowPageTabs(false);
        
        string timelineName = "VMM_"+ofToString(i);
        t->setName(timelineName);
        
        timelines.push_back(t);
        

        
    }
    
}

//-------------------------------------------------
void timelineTrack::draw(){
    
    //loop through and draw all the timelines
    for(int i = 0; i < timelines.size(); i++){
        timelines[i]->draw();

    }
}

//-------------------------------------------------
void timelineTrack::update(){
    
    
}


//-------------------------------------------------
void timelineTrack::displayTimelines(bool _showTimeline){
    
    showHideFlag = _showTimeline;
    for(int i = 0; i < timelines.size(); i++){
        
        if(showHideFlag){
            timelines[i]->show();
        } else {
            timelines[i]->hide();
        }
    }
    
}

//-------------------------------------------------
void timelineTrack::enableTimelines(bool _enable){

    //turns off mouse events while a dropdown is active.
    for(int i = 0; i < timelines.size(); i++){
        if(_enable){
            timelines[i]->enableEvents();
        }
        if(!_enable){
            timelines[i]->disableEvents();
        }
    }
    
}

//--------------------------------------------------------------
void timelineTrack::showSelectedTimelineTrack(int _track){
    
    for(int i=0; i<timelines.size();i++){
        if(i == _track){
            timelines[i]->show();
            //timelines[i]->getIsShowing();   //boolean - is show() or hide()
        } else {
            timelines[i]->hide();
        }
    }
    
}

//--------------------------------------------------------------
void timelineTrack::enableVMMControlTrack(int _track){
    for(int i=0; i<timelines.size();i++){
        if(timelines[i]->hasTrack("VMM")){
            if(i == _track){
                cout << "track " << i << " - VMM enabled()" << endl;
                
                timelines[i]->getTrack("VMM")->enable();
                
                
            } else {
                cout << "track " << i << " - VMM disabled()" << endl;
                timelines[i]->getTrack("VMM")->disable();
            }
        }
    }
    
}

//-------------------------------------------------
void timelineTrack::addTLTrack(int _track, string _page, string _name, int _type, float _low, float _high){
    
    timelines[_track]->setCurrentPage(_page);
    
    switch (_type) {
        case 1:
            //curves
            timelines[_track]->addCurves(_name, ofRange(_low, _high));
            break;

        case 2:
            //bangs
            timelines[_track]->addBangs(_name);
            break;
            
        case 3:
            //switches
            timelines[_track]->addSwitches(_name);
            break;
            
        case 4:
            //flags
            timelines[_track]->addFlags(_name);
            break;
            
        case 5:
            //colors
            timelines[_track]->addColors(_name);
            break;
            
        case 6:
            //ofxTLVMMControl* buttonsTrack = new ofxTLVMMControl("127.0.0.1" ,7005);
            ofxTLVMMControl* buttonsTrack = new ofxTLVMMControl();

            string buttonsTrackName = _name;
            buttonsTrack->setXMLFileName(buttonsTrackName+".xml");
            buttonsTrack->track = _track;
            timelines[_track]->addTrack(_name, buttonsTrack);
            break;
    }
    
    //SAMPLE CODE TO ACCESS PAGE PROPERTIES.
    //ofxTLPage* test = timelines[_track]->getPage(_page);
    //test->setMinimalHeaders(true);
    //test->hideFooters(true);
    //timelines[_track]->setHeight(121.0);
    //test->setTrackHeight(100);
    
}


//-------------------------------------------------
void timelineTrack::remTLTrack(int _track, int _page, string _name){
    
    cout << "remove track" << endl;
    // use the data from "event-a-rific"
    timelines[_track]->setCurrentPage(_page);
    timelines[_track]->removeTrack(_name);
    
}

//-------------------------------------------------
void timelineTrack::setPage(int _track, int _page){
    
    timelines[_track]->setCurrentPage(_page);
    
}

//-------------------------------------------------
void timelineTrack::highlightFocuedTrack(int _track, string _name){

    ofxTLTrack* newFocus = NULL;
    newFocus = timelines[_track]->getTrack(_name);
    timelines[_track]->setFocusedTrack(newFocus);
    
}
