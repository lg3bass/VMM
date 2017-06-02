//
//  TimelinePanel.cpp
//  02_timlineLink_test

#include "TimelinePanel.h"
#include "ofApp.h"

ofApp* tMainApp;

//-------------------------------------------------
void TimelinePanel::setup(int x, int y, int width, int height, ofBaseApp* appPtr){

    tMainApp = dynamic_cast<ofApp*>(appPtr);
    
    _x = x;
    _y = y;
    _w = width;
    _h = height;
    _frameRate = INIT_FPS;
    _bpm = tMainApp->getGlobalTempo();
    _bckgColor = ofColor(40);
    
    //cuedToPlay = false;
    //currentLoaded = 0;
    
    duration = calculateFramesInMeasures(measures, _bpm, _frameRate);
    
    //link
    link.setup(_bpm);
    
    //setup the timelines
    timelines.reserve(NUMBER_OF_TRACKS);
    
    
    //SETUP THE TRACKS
    for(int i=0; i<NUMBER_OF_TRACKS; i++){
        ofxTimeline* t = new ofxTimeline();
        
        t->setupFont("gui_assets/fonts/verdana.ttf", 12);
        
        t->removeCocoaMenusFromGlut("02_timlineLink_testDebug");
        t->setup();
        
        //sets the directory where the default xml
        t->setWorkingFolder(TRACK_DIR "_" + ofToString(i) + "/");
        
        t->setAutosave(false);
        t->setSpacebarTogglePlay(false);
        t->setLockWidthToWindow(false);
        t->setDurationInFrames(duration);
        t->setOffset(ofVec2f((float)_x, (float)_y));
        t->setWidth((float)_w);
        t->setBPM(_bpm);
        t->setFrameRate(_frameRate);
        t->setLoopType(OF_LOOP_NORMAL);
        t->setShowBPMGrid(true);
        t->setFrameBased(true);
        t->setInPointAtFrame(0);
        t->setOutPointAtFrame(duration);
        
        
       
        //test track
        t->setPageName("Global-Rotate");
        t->addCurves("G Rotate X", ofRange(0, 100));
        t->addCurves("G Rotate Y", ofRange(0, 100));
        t->addCurves("G Rotate Z", ofRange(0, 100));
        
        t->addPage("Local-Rotate");
        t->addCurves("L Rotate X", ofRange(0, 360));
        t->addCurves("L Rotate Y", ofRange(0, 360));
        t->addCurves("L Rotate Z", ofRange(0, 360));
        
        t->addPage("Object-Rotate");
        t->addCurves("O Rotate X", ofRange(0, 360));
        t->addCurves("O Rotate Y", ofRange(0, 360));
        t->addCurves("O Rotate Z", ofRange(0, 360));
        
        
        t->addPage("Global-Translate");
        t->addCurves("G Translate X", ofRange(-150,150));
        t->addCurves("G Translate Y", ofRange(-150,150));
        t->addCurves("G Translate Z", ofRange(-150,150));
        
        t->addPage("Local-Translate");
        t->addCurves("L Translate X", ofRange(-150,150));
        t->addCurves("L Translate Y", ofRange(-150,150));
        t->addCurves("L Translate Z", ofRange(-150,150));
        
        
        t->getTrack("L Rotate Z")->disable();//This track is controlled by the slices
        
        t->setCurrentPage(0);
        
        //move all my tracks up here.
        
        timelines.push_back(t);
        
        
        
        
    }
      
    setMeasureLoop();
    
    showSelectedTimelineTrack(0);

}


//-------------------------------------------------
void TimelinePanel::update(){
    
    
    for(int i=0;i<NUMBER_OF_TRACKS;i++){
        if(tMainApp->getIsCuedToPlay(i)){
            if(nbeat == 0){
                timelines[i]->togglePlay();
                ofLogNotice("LINK") << "update() >> measureCount:" << measureCount;
                tMainApp->setCuedToPlay(i, false);
            }
        }
    }
    
    
//    if(cuedToPlay){
//        if(nbeat == 0){
//            for(int i=0; i<timelines.size(); i++){
//                timelines[i]->togglePlay();
//            }
//            
//            cout << "update() >> measureCount:" << ofToString(measureCount) << endl;
//            cuedToPlay = false;
//        }
//    }

}

//-------------------------------------------------
void TimelinePanel::draw(){
    
    //ableton link
    runAbletonLink(link);
    
    
    for(int i = 0; i < timelines.size(); i++){
        
        /*
        if(i != 0){
            //original code offset all the timelines below the one above it, with a 10 pixel buffer
            timelines[i]->setOffset(timelines[i-1]->getBottomLeft() + ofVec2f(0, 10));
        }
        */
        timelines[i]->draw();
    }
    
    //send out all the OSC
    sendOSCfromTimeline();
    
    //draw a bounding box around the panel just to show.
    ofSetColor(ofColor(100));
    ofSetLineWidth(2.0);
    ofNoFill();
    ofDrawRectangle(_x, _y, _w, _h);

}

//--------------------------------------------------------------
void TimelinePanel::save(int track, int clip){
    
    saveSettings(track, ofToString(clip));
    ofLogNotice("FILE") << "saving clip xml: " << clip;
    
}

//--------------------------------------------------------------
void TimelinePanel::load(int track, int clip){
    
    loadSettings(track,clip);
    
    if(clip != tMainApp->getSelectedClip(track)){
        

        
        //tMainApp->setSelectedClip(track, clip);
        ofLogNotice("FILE") << "TimelinePanel::load("
                            << track << ","
                            << clip << ")";
    } else {
        ofLogNotice("FILE") << "TimelinePanel::load() - no need to load! You are playing the same clip.";
    }
}

//--------------------------------------------------------------
void TimelinePanel::saveCurrent(){

    int t = tMainApp->getSelectedTrack();
    int c = tMainApp->getSelectedClip(t);
    
    ofLogNotice("FILE") << "TimelinePanel::saveCurrent() - "
                        << "track: " << t
                        << "clip: " << c;
    
    saveSettings(t,ofToString(c));
}

//--------------------------------------------------------------
void TimelinePanel::loadCurrent(){
    
    int t = tMainApp->getSelectedTrack();
    int c = tMainApp->getSelectedClip(t);
    
    ofLogNotice("FILE") << "TimelinePanel::loadCurrent() - "
                        << "track: " << t
                        << "clip: " << c;
    
    loadSettings(t,c);                              //all xml folders start at 0.
}

//--------------------------------------------------------------
void TimelinePanel::loadAllTracks(){
    
    for(int i=0;i<NUMBER_OF_TRACKS;i++){
        loadSettings(i,0);                          //load the track and the clip
        
    }
    
    tMainApp->resetAllTrackAndClips();

}

//--------------------------------------------------------------
void TimelinePanel::play(int t, int c){
    ofLogNotice("TRACK")    << "timePanel.play("
                            << t << "," << c
                            << ") -- nbeat:" << nbeat;
    
    setMeasureLoop();                                           //TODO - move this out somewhere else.  each timeline should have it's own
    
    load(t,c);                                                  //TODO - function "load()" redundant.
    
    if(!timelines[t]->getIsPlaying()){
        
        tMainApp->setCuedToPlay(t, true);
    } else {
        //TO-DO: code to deal with quant lead in.
    }
}

//--------------------------------------------------------------
void TimelinePanel::pause(int c){
    
}

//--------------------------------------------------------------
void TimelinePanel::stop(int c){
    for(int i=0; i<timelines.size(); i++){
        if(timelines[i]->getIsPlaying()){
            timelines[i]->stop();
            //cuedToPlay = false;
            tMainApp->setCuedToPlay(i, false);
        }
        
    }
}

//--------------------------------------------------------------
void TimelinePanel::keyPressed(int key){

    if(key & OF_KEY_MODIFIER){
        if(key >= OF_KEY_F1 && key <= OF_KEY_F12){
            
        }else{
            switch(key){
                case OF_KEY_LEFT_SUPER:
                    ofLogNotice("KEY") << "Left Apple Pressed";
                    modkey = true;
                    break;
                case OF_KEY_RIGHT_SUPER:
                    ofLogNotice("KEY") << "Right Apple Pressed";
                    modkey = true;
                    break;
                case OF_KEY_CONTROL:
                    ofLogNotice("KEY") << "Control Pressed";
                    ctrlKey = true;
                    break;
                case OF_KEY_RIGHT_ALT:
                    ofLogNotice("KEY") << "Right Alt/Opt Pressed";
                    rAltKey = true;                    
                    break;
                case OF_KEY_LEFT_SHIFT:
                    ofLogNotice("KEY") << "Left Shift Pressed";
                    lShiftKey = true;
                    break;
                case OF_KEY_RIGHT_SHIFT:
                    ofLogNotice("KEY") << "Right Shift Pressed";
                    rShiftKey = true;
                    break;
                case OF_KEY_LEFT_ALT:
                    ofLogNotice("KEY") << "Left Alt/Opt Pressed";
                    lAltKey = true;
                    break;
            }//end switch
        }//if(key >= OF_KEY_F1 && key <= OF_KEY_F12){
        
    } else {
        switch (key) {
                
            case 'r':
                //ROTATE PAGE
                timelines[0]->setCurrentPage(0);
                tMainApp->myAppData.tracks[0].current_page = 0;
                break;
            case 't':
                //TRANSLATE PAGE
                 timelines[0]->setCurrentPage(1);
                tMainApp->myAppData.tracks[0].current_page = 1;
                break;
            case 'l':
                //turn on and off link.
                link.enable(!link.isEnabled());
                break;
            case 'p':
                play(0,1);
                break;
            case 'g':
                for(int i=0; i<NUMBER_OF_TRACKS; i++){
                   timelines[i]->toggleSnapToBPM();
                    if(timelines[i]->getSnapToBPM()){
                        ofLogNotice("TRACK") << ofToString(i) << ": snap to BPM: -- ON";
                    } else {
                        ofLogNotice("TRACK") << ofToString(i) << ": snap to BPM: -- OFF";
                    }
                }
                break;
            case 'd':
                for(int i=0; i<NUMBER_OF_TRACKS; i++){
                    tMainApp->myAppData.tracks[i].directDrive = !tMainApp->myAppData.tracks[i].directDrive;
                    cout << "directDrive: " << tMainApp->myAppData.tracks[i].directDrive << endl;
                }
                break;
            case 'i':
                timelines[0]->setInPointAtPlayhead();
                break;
            case 'o':
                timelines[0]->setOutPointAtPlayhead();
                break;
            case 's':
                stop(1);
                break;
            case '1':
                if(ctrlKey){
                    //save(tMainApp->myAppData.selected_track,1);
                    play(0,1);
                }
                if (modkey) {
                    load(tMainApp->myAppData.selected_track,1);
                }
                break;
            case '2':
                if(ctrlKey){
                    //save(tMainApp->myAppData.selected_track,2);
                    play(1,1);
                }
                if(modkey) {
                    load(tMainApp->myAppData.selected_track,2);
                }
                break;
            case '3':
                if(ctrlKey){
                    //save(tMainApp->myAppData.selected_track,2);
                    play(2,1);
                }
                if(modkey) {
                    load(tMainApp->myAppData.selected_track,3);
                }
                break;
                
            default:
                
                break;
                
                
        }//end switch
    }//end if(key & OF_KEY_MODIFIER)
}

//--------------------------------------------------------------
void TimelinePanel::keyReleased(int key){

    if(key & OF_KEY_MODIFIER){
        if(key >= OF_KEY_F1 && key <= OF_KEY_F12){
            
        }else{
            
            switch(key){
                case OF_KEY_LEFT_SUPER:
                    ofLogNotice("KEY") << "Left Apple Released";
                    modkey = false;
                    break;
                case OF_KEY_RIGHT_SUPER:
                    ofLogNotice("KEY") << "Right Apple Released";
                    modkey = false;
                    break;
                case OF_KEY_CONTROL:
                    ofLogNotice("KEY") << "Control Released";
                    ctrlKey = false;
                    break;
                case OF_KEY_RIGHT_ALT:
                    ofLogNotice("KEY") << "Right Alt/Opt Released";
                    rAltKey = false;
                    break;
                case OF_KEY_LEFT_SHIFT:
                    ofLogNotice("KEY") << "Left Shift Released";
                    lShiftKey = false;
                    break;
                case OF_KEY_RIGHT_SHIFT:
                    ofLogNotice("KEY") << "Right Shift Released";
                    rShiftKey = false;
                    break;
                case OF_KEY_LEFT_ALT:
                    ofLogNotice("KEY") << "Left Alt/Opt Released";
                    lAltKey = false;
                    break;
                    
            }
        }
    }

    
    
}

//--------------------------------------------------------------
void TimelinePanel::showSelectedTimelineTrack(int track){
    
    for(int i=0; i<timelines.size();i++){
        if(i == track){
            timelines[i]->show();
        } else {
            timelines[i]->hide();
        }
        
    }
    
}


//--------------------------------------------------------------
int TimelinePanel::calculateFramesInMeasures(int m, float bpm, int fps){

    int frames;
    
    //(4beats per measure) * (1800f in a second at 30fps).
    float f = (m*4)*1800.0;

    //calulate how many frames in n measures and round up to the next frame.
    frames = int(ceil(f/bpm));
    
    //raw output
    ofLogNotice("TRACK") << m << " m @ " << fps << "fps = frames(float|int): " << ofToString(f/bpm) << "|" << frames;
    
    return frames;
}

//--------------------------------------------------------------
void TimelinePanel::runAbletonLink(ofxAbletonLink &linkObj){

    //link
    ofxAbletonLink::Status status = link.update();
    
    // visualize the current status
    int quantum = (int)ceil(link.quantum());
    
    //what beat is playing in link?
    float dw;
    if(quantum < 1){
        dw = (float)ofGetWidth();
        nbeat = 0;
    }else{
        dw = (float)ofGetWidth() / (float)quantum;
        nbeat = (int)floor(status.beat) % quantum;
    }
    
    //encapsulate this in a vector loop.
    
    for(int i=0; i<timelines.size(); i++){
        if(timelines[i]->getIsPlaying()){
            //slim data to just beats
            if(nbeat != lbeat){
                
                //resets the measure counter
                if(nbeat == 0){
                    if(measureCount == measures){
                        timelines[i]->setCurrentFrame(0);
                        measureCount = 1;
                        ofLogNotice("LINK") << "tick - " << lbeat << "|" << nbeat << " >>>>  measureCount(FLIP): " << measureCount << "(" << timelines[i]->getCurrentFrame() << ")";
                    } else {
                        
                        measureCount++;
                        ofLogNotice("LINK") << "tick - " << lbeat << "|" << nbeat << " >>>>  measureCount: " << measureCount << "(" << timelines[i]->getCurrentFrame() << ")";
                    }
                } else {
                    ofLogNotice("LINK") << "tick - " << lbeat << "|" << nbeat << "(" << timelines[i]->getCurrentFrame() << ")";
                }
                lbeat = nbeat;
                

            } else {
                ofLogNotice("LINK") << "tock - " << ofToString(nbeat);
            }
        }
        
    }
    
    
    
    
    
    //BELOW is all for the bars at the bottom. ableton link.
    
    int top = (int)(ofGetHeight() * 0.95);
    int bottom = (int)(ofGetHeight() * 1);
    int h = bottom - top + 1;
    
    //draw the blinking beats
    for (int i = 0; i < quantum; i++){
        ofFill();
        ofSetColor((i <= nbeat) ? 255 : 128);
        ofDrawRectangle(i * dw, top, dw, h);
        ofNoFill();
        ofSetColor(0);
        ofDrawRectangle(i * dw, top, dw, h);
    }
    
    //report status at the bottom
    ofSetColor(0);
    //link info
    ofDrawBitmapString("Tempo: " + ofToString(link.tempo()) +
                       " Beats: " + ofToString(status.beat) +
                       " Phase: " + ofToString(status.phase)
                       , 20, ofGetHeight()-25);
    ofDrawBitmapString("Number of peers: " + ofToString(link.numPeers()), 20, ofGetHeight()-15);
    ofDrawBitmapString("Measure: " + ofToString(measureCount) +
                       " Beat: " + ofToString(nbeat)
                       , 20, ofGetHeight()-5);
    
    
    //tracks, clips, and pages
    ofDrawBitmapString("Tr: 0 1 2", ofGetWidth()/2+20, ofGetHeight()-25);
    ofDrawBitmapString("Cl: " + ofToString(tMainApp->myAppData.tracks[0].selected_clip) + " " +
                       ofToString(tMainApp->myAppData.tracks[1].selected_clip) + " " +
                       ofToString(tMainApp->myAppData.tracks[2].selected_clip), ofGetWidth()/2+20, ofGetHeight()-15);
    ofDrawBitmapString("Pg: " + ofToString(tMainApp->myAppData.tracks[0].current_page) + " " +
                       ofToString(tMainApp->myAppData.tracks[1].current_page) + " " +
                       ofToString(tMainApp->myAppData.tracks[2].current_page), ofGetWidth()/2+20, ofGetHeight()-5);
    
    
    
    
}



//--------------------------------------------------------------
void TimelinePanel::sendOSCfromTimeline(){
    
    for(int i=0; i< NUMBER_OF_TRACKS; i++){
        
        if(tMainApp->myAppData.tracks[i].directDrive){
        
            //if(timelines[i]->getIsPlaying()){
            
            tMainApp->OSCsendToVMM(i+1,"/setGlobalRotX",timelines[i]->getValue("G Rotate X"));
            tMainApp->OSCsendToVMM(i+1,"/setGlobalRotY",timelines[i]->getValue("G Rotate Y"));
            tMainApp->OSCsendToVMM(i+1,"/setGlobalRotZ",timelines[i]->getValue("G Rotate Z"));
            
            tMainApp->OSCsendToVMM(i+1,"/setLocalRotX",timelines[i]->getValue("L Rotate X"));
            tMainApp->OSCsendToVMM(i+1,"/setLocalRotY",timelines[i]->getValue("L Rotate Y"));
            //tMainApp->OSCsendToVMM(i,"/setLocalRotZ",timelines[i]->getValue("L Rotate Z"));
            
            tMainApp->OSCsendToVMM(i+1,"/setObjRotX",timelines[i]->getValue("O Rotate X"));
            tMainApp->OSCsendToVMM(i+1,"/setObjRotY",timelines[i]->getValue("O Rotate Y"));
            tMainApp->OSCsendToVMM(i+1,"/setObjlRotZ",timelines[i]->getValue("O Rotate Z"));
            
            tMainApp->OSCsendToVMM(i+1,"/setGlobalTransX",timelines[i]->getValue("G Translate X"));
            tMainApp->OSCsendToVMM(i+1,"/setGlobalTransY",timelines[i]->getValue("G Translate Y"));
            tMainApp->OSCsendToVMM(i+1,"/setGlobalTransZ",timelines[i]->getValue("G Translate Z"));
            
            tMainApp->OSCsendToVMM(i+1,"/setLocalTransX",timelines[i]->getValue("L Translate X"));
            tMainApp->OSCsendToVMM(i+1,"/setLocalTransY",timelines[i]->getValue("L Translate Y"));
            tMainApp->OSCsendToVMM(i+1,"/setLocalTransZ",timelines[i]->getValue("L Translate Z"));
        }
        
    }

}

//--------------------------------------------------------------
void TimelinePanel::alterTimeline(int _val){
    
    cout << timelines[0]->getTrack("G Rotate X")->getName() << endl;
    
    //This is how I can add a keyframe
    ofxTLKeyframes* mytrack = (ofxTLKeyframes*)timelines[0]->getTrack("G Rotate X");
    mytrack->addKeyframeAtMillis(50.0, 2000.0);
    
    //ofxTLKeyframes::addKeyframeAtMillis(50.0, 2000.0);
    
    
    
    
}

//--------------------------------------------------------------
void TimelinePanel::addKeyFrameToCurrentTrack(float _val, float _timeInMiliseconds){
    

    
    ofxTLKeyframes* selTrack = (ofxTLKeyframes*)timelines[0]->getTrack("G Rotate X");
    selTrack->addKeyframeAtMillis(_val,_timeInMiliseconds);
}

//--------------------------------------------------------------
void TimelinePanel::setRange(ofRange newrange) {
    ofxTLKeyframes* selTrack = (ofxTLKeyframes*)timelines[0]->getTrack("G Rotate X");
    selTrack->setValueRange(newrange, 0.0);
}


//--------------------------------------------------------------
#pragma mark - Settings
//--------------------------------------------------------------
void TimelinePanel::loadSettings(int track, int clipSlot){
    

/*    
    
    
    //----------------------------------
    //-:Load Xml file
    
    string filenamePanel = clipSlot + "_" + TIMELINE_SETTINGS_DIR "/timePanel_settings.xml";
    ofxXmlSettings xml;
    
    if( xml.loadFile(filenamePanel) ){
        ofLogVerbose()<<"TimePanel: "<< filenamePanel <<" loaded.";
    }else{
        ofLogError()<< "TimePanel: unable to load " << filenamePanel ;
        return;
    }


    
    //----------------------------------
    //-:Add markers from loaded settings.
    
    clearMarkers();
    
    int markersNum = xml.getValue("PANEL:MARKERS:MARKERS-NUM", 0);
    for (int i=0; i<markersNum; i++){
        float markerTimeMillis = xml.getValue("PANEL:MARKERS:MARKER-" + ofToString(i), 0.0);
        addMarker(markerTimeMillis);
    }
    
    
    
    //----------------------------------
    //-:Create tracks from loaded settings.
    int tracksNum= xml.getValue("PANEL:TRACKS:TRACKS-NUM", 0);
    for (int i=0; i<tracksNum; i++){
        string trackName = xml.getValue("PANEL:TRACKS:TRACK-" + ofToString(i) +":NAME", "");
        string trackType = xml.getValue("PANEL:TRACKS:TRACK-" + ofToString(i) +":TYPE", "");
        
        auto tracksPage = timeline.getPage(PAGE_TRACKS_NAME);
        
        //If track doesnt exist and its not default -> create it.
        if(trackName != "DEFAULT" &&
           tracksPage->getTrack(trackName)==NULL){
            
            if(trackType=="Curves"){
                addTrack(trackName, CURVES);
            }else if(trackType=="Bangs"){
                addTrack(trackName, BANGS);
            }else if(trackType=="Switches"){
                addTrack(trackName, SWITCHES);
            }
            
        }
    }

*/
 
    
    //----------------------------------
    //-:Load ALL
//    for (int i=0;i<timelines.size();i++){
//        timelines[i]->loadTracksFromFolder(TRACK_DIR "_" + ofToString(i) + "/" CLIP_DIR "_" + clipSlot + "/");
//    }

    //----------------------------------
    //-:Load specific track
    timelines[track]->loadTracksFromFolder(TRACK_DIR "_" + ofToString(track) + "/" CLIP_DIR "_" + ofToString(clipSlot) + "/");


    
    //----------------------------------
    //-:Log
    
    ofLogNotice("FILE") << "TimePanel: settings LOADED";
    
}


//--------------------------------------------------------------
void TimelinePanel::saveSettings(int track, string clipSlot){
    
    //----------------------------------
    //-:Save ALL
//    for (int i=0;i<timelines.size();i++){
//        timelines[i]->saveTracksToFolder(TRACK_DIR "_" + ofToString(i) + "/" CLIP_DIR "_" + clipSlot + "/");
//    }
  
    //----------------------------------
    //-:Save Specific Track
    timelines[track]->saveTracksToFolder(TRACK_DIR "_" + ofToString(track) + "/" CLIP_DIR "_" + clipSlot + "/");
    
    
    savePageSettings(clipSlot, "Global-Rotate");
    savePageSettings(clipSlot, "Global-Translate");
    

    
    
    
}

//--------------------------------------------------------------
void TimelinePanel::savePageSettings(string clipSlot, string pageName){
    //----------------------------------
    //-:Save Tracks Names and Types
    
    for (int i=0;i<timelines.size();i++){
        auto tracksPage = timelines[i]->getPage(pageName);
        
        
        //string filenamePanel = clipSlot + "_" + TIMELINE_SETTINGS_DIR + "/" + pageName + "_settings.xml";
        string filenamePanel = TRACK_DIR "_" + ofToString(i) + "/" CLIP_DIR "_" + clipSlot + "/" + pageName + "_settings.xml";
        
        ofxXmlSettings savedSettings;
        
        int tracksNum = tracksPage->getTracks().size();
        
        savedSettings.addTag("PANEL");
        savedSettings.pushTag("PANEL");
        savedSettings.addTag("TRACKS");
        savedSettings.pushTag("TRACKS");
        savedSettings.addValue("TRACKS-NUM", tracksNum);
        
        for (int i=0; i<tracksNum; i++){
            savedSettings.addTag("TRACK-"+ofToString(i));
            savedSettings.pushTag("TRACK-"+ofToString(i));
            savedSettings.addValue("NAME", tracksPage->getTracks()[i]->getName());
            savedSettings.addValue("TYPE", tracksPage->getTracks()[i]->getTrackType());
            savedSettings.popTag();
        }
        savedSettings.popTag();
        
        //----------------------------------
        //-:Save Markers
        
        savedSettings.addTag("MARKERS");
        savedSettings.pushTag("MARKERS");
        
        savedSettings.addValue("MARKERS-NUM", (int)_markers.size());
        for (int i=0; i<_markers.size(); i++){
            savedSettings.addValue("MARKER-"+ofToString(i), _markers[i]);
        }
        
        savedSettings.saveFile(filenamePanel);
        
        //----------------------------------
        //-:Log
        
        ofLogVerbose()<<"TimePanel: settings SAVED";
        ofLogVerbose()<<"-Tracks Saved: "<< tracksNum;
        for (auto track : tracksPage->getTracks()){
            ofLogVerbose()<<"--Name: "<<track->getName() << "- Type: "<< track->getTrackType();
        }
        ofLogVerbose()<<"-Markers Saved: "<< _markers.size();
    }
    

}

//--------------------------------------------------------------
void TimelinePanel::setMeasureLoop(){

    nbeat = -1;
    lbeat = -2;
    measureCount = 0;
    measures = 8;
    
    for (int i=0;i<timelines.size();i++){
        timelines[i]->setCurrentFrame(0);
    }
    
    
}


//--------------------------------------------------------------
void TimelinePanel::setMeasuresAtTempo(int _measures, float _tempo){
    
    
    duration = calculateFramesInMeasures(_measures, _tempo, _frameRate);
    
    for (int i=0;i<timelines.size();i++){
        timelines[i]->setOutPointAtFrame(duration);
        timelines[i]->setDurationInFrames(duration);
        timelines[i]->setBPM(_tempo);
    }
    
    measures = _measures;
    
    link.setTempo(_tempo);
    
    
}
