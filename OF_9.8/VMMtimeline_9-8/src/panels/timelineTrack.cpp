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
    duration = 120;
    _x = _x;
    _y = _y;
    _w = _w;
    _h = _h;
    int _bpm = 120;
    int _frameRate = 30;
    
    //SETUP THE TRACKS
    for(int i=0; i<NUMBER_OF_TRACKS; i++){
        ofxTimeline* t = new ofxTimeline();
        
        t->setupFont("verdana.ttf", 10);
        
        //t->removeCocoaMenusFromGlut("02_timlineLink_testDebug");
        t->setup();
        
        //sets the directory where the default xml
        t->setWorkingFolder(TRACK_DIR "_" + ofToString(i) + "/");
        
        t->setAutosave(false);
        t->setSpacebarTogglePlay(false);
        t->setLockWidthToWindow(false);
        t->setDurationInFrames(duration);
        t->setOffset(ofVec2f((float)_x, (float)_y));
        //t->setMinimalHeaders(true);
        t->setWidth((float)_w);
        t->setBPM(_bpm);
        t->setFrameRate(_frameRate);
        t->setLoopType(OF_LOOP_NORMAL);
        t->setShowBPMGrid(true);
        t->setFrameBased(true);
        t->setInPointAtFrame(0);
        t->setOutPointAtFrame(duration);
        t->setShowZoomer(false);
        t->setShowInoutControl(false);
        
        //set the initial page name
        t->setPageName("P1", 0);
        
        for(int j=2;j<11;j++){
            t->addPage("P"+ofToString(j));
        }

        t->setShowPageTabs(false);
        
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
void timelineTrack::mousePressed(int x, int y, int button){
    
}

//-------------------------------------------------
void timelineTrack::saveTLChannel(int _track, string _page, string _filePath){
    
    //save the keyframe data from each track
    //NOTE: In order to specifically target a single page
    //      You will need to add an additional function
    //      e.g. ofxTimeline::savePageTracksToFolder(int page, string folderPath)
    
    //timelines[_track]->savePageTracksToFolder(1,_filePath);
    timelines[_track]->saveTracksToFolder(_filePath);
    
    //save the page settings.
    string pageName = _page;
    
    auto tracksPage = timelines[_track]->getPage(pageName);
    
    string filenamePanel = _filePath + pageName + "_settings.xml";
    ofxXmlSettings savedSettings;
    
    int tracksNum = tracksPage->getTracks().size();
    
    savedSettings.addTag("page");
    savedSettings.pushTag("page");
    savedSettings.addValue("name",pageName);
    savedSettings.addTag("tlChannels");
    savedSettings.pushTag("tlChannels");
    savedSettings.addValue("tlChannels-num", tracksNum);
    
    for (int i=0; i<tracksNum; i++){
        savedSettings.addTag("channel-"+ofToString(i));
        savedSettings.pushTag("channel-"+ofToString(i));
        savedSettings.addValue("name", tracksPage->getTracks()[i]->getName());
        savedSettings.addValue("type", tracksPage->getTracks()[i]->getTrackType());
        savedSettings.popTag();
    }
    savedSettings.popTag();
    
    savedSettings.saveFile(filenamePanel);

}

//-------------------------------------------------
void timelineTrack::loadTLChannel(int _track, string _page, string _filePath){
    
    //----------------------------------
    //-:Load Xml file
    
    string pageName = _page;
    
    string filenamePanel = _filePath + pageName + "_settings.xml";
    ofxXmlSettings xml;
    
    if( xml.loadFile(filenamePanel) ){
        ofLogVerbose()<<"TimePanel: "<< filenamePanel <<" loaded.";
    }else{
        ofLogError()<< "TimePanel: unable to load " << filenamePanel ;
        return;
    }
    
    
    //----------------------------------
    //-:Create tracks from loaded settings.
    int tracksNum = xml.getValue("page:tlChannels:tlChannels-num", 0);
    string pageNameFromXML = xml.getValue("page:name","");
    for (int i=0; i<tracksNum; i++){
        string trackName = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":name", "");
        string trackType = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":type", "");
        
        auto tracksPage = timelines[_track]->getPage(pageName);
        
        
        //If track doesnt exist and its not default -> create it.
        if(trackName != "DEFAULT" &&
           tracksPage->getTrack(trackName)==NULL){
            
            if(trackType=="Curves"){
                addTLTrack(_track, pageName, trackName, 1);
                //addTrack(trackName, CURVES);
            }else if(trackType=="Bangs"){
                //addTrack(trackName, BANGS);
            }else if(trackType=="Switches"){
                //addTrack(trackName, SWITCHES);
            }
        }
    }
    
    //load the tracks into the created tracks
    timelines[_track]->loadTracksFromFolder(_filePath);
    
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
        } else {
            timelines[i]->hide();
        }
    }
    
}

//-------------------------------------------------
void timelineTrack::addTLTrack(int _track, int _page, string _name, int _type){

    timelines[_track]->setCurrentPage(_page);
    timelines[_track]->addCurves(_name, ofRange(0, 100));
    
}

//-------------------------------------------------
void timelineTrack::addTLTrack(int _track, string _page, string _name, int _type){

    timelines[_track]->setCurrentPage(_page);
    timelines[_track]->addCurves(_name, ofRange(0, 100));
    
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
