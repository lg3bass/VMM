//
//  timelinePanel.cpp
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//

#include "TimelinePanel.h"
#include "ofApp.h"

#define TRACK_DIR "TRACK"
#define CLIP_DIR "CLIP"

ofApp* bMainApp;        //reference to ofApp()

//-------------------------------------------------
void TimelinePanel::setup(int x, int y, int width, int height, ofBaseApp* appPtr){
    
    bMainApp = dynamic_cast<ofApp*>(appPtr);
    setPanelName("BODY");
    
    _x = x;
    _y = y;
    _w = width;
    _h = height;
    panelBoundingBox = ofRectangle(x, y, width, height);
    
    tracks.init(x,y,_w,_h);

    //custom border colors
    //setBackgroundColor(ofColor::darkGray);
    //setBorderColor(ofColor::white);
    setBorderColorHighligh(ofColor::green);
    //setBorderWidth(2);
    
    verdana9.load("verdana.ttf", 7, true, true);
    
    showTrackData = false;
    
    //add listener to "ofxTLEvents::trackGainedFocus"
    for(int i=0; i<NUMBER_OF_TRACKS; i++){
        
        //add listeners
        ofAddListener(tracks.timelines[i]->events().trackGainedFocus, this, &TimelinePanel::actOnFocus);
        ofAddListener(tracks.timelines[i]->events().trackLostFocus, this, &TimelinePanel::actOnLossFocus);
        ofAddListener(tracks.timelines[i]->events().bangFired, this, &TimelinePanel::timelineBangFired);
        ofAddListener(tracks.timelines[i]->events().switched, this, &TimelinePanel::timelineSwitched);
        ofAddListener(tracks.timelines[i]->events().playbackStarted, this, &TimelinePanel::timelinePlaybackStarted);
        ofAddListener(tracks.timelines[i]->events().playbackLooped, this, &TimelinePanel::timelinePlaybackLooped);
        
        //reset/setup track metadata.
        resetMeasureLoop(i);
    }
    
    //initially set first track
    setTLTrack(0);
}

//-------------------------------------------------
void TimelinePanel::update(){

    for(int i=0;i<NUMBER_OF_TRACKS;i++){
        
        data.setNBeat(i, bMainApp->AL.nbeat);
        
        if(data.getCuedToPlay(i)){
            
            if(data.isDownbeat(i)){
                tracks.timelines[i]->setPercentComplete(0);
                tracks.timelines[i]->play();
                ofLogNotice("LINK") << "update() >> track " << i << " measureCount:" << data.TL.tracks[i].measureCount;
                data.setCuedToPlay(i, false);
            }
        }
        
        //Do all the Ableton Link Syncing. Keep track of beats,measures,etc.
        runTimelines(i);
         
        //send out all the OSC
        sendOSCfromTimeline(i);
    }
}

//-------------------------------------------------
void TimelinePanel::draw(){
    
    tracks.draw();
    
    //draws a border around the panel.
    drawPanelBgAndBorder(false);
    
    if(showTrackData){
        drawTrackData();
    }
    
}

//-------------------------------------------------
void TimelinePanel::runTimelines(int _track){
    
    if(tracks.timelines[_track]->getIsPlaying()){//TRUE OR FALSE
        
        int currentBeat = data.getNBeat(_track);
        int lastBeat = data.getLBeat(_track);
        
        if(currentBeat != lastBeat){            
            //resets the measure counter
            if(data.isDownbeat(_track)){
                ofLogVerbose("LINK") << "isDownbeat()" << " - track " << _track;
                //if(data.TL.tracks[_track].measureCount == data.TL.tracks[_track].measureLength){
                int c = data.getClip(_track);
                
                //Have we reached the duration (numberOfMeasures) in the clip?
                if(data.TL.tracks[_track].measureCount == data.TL.tracks[_track].tlClips[c].numberOfMeasures){

                    //set the playhead to ZERO
                    tracks.timelines[_track]->setPercentComplete(0);
                    
                    //It's a downbeat, reset the measureCount.
                    data.TL.tracks[_track].measureCount = 1;
                    
                    ofLogNotice("LINKFLIP") << "tick - " << lastBeat << "|" << currentBeat
                                            << " >>>>  measureCount(FLIP): " << data.TL.tracks[_track].measureCount
                                            << "(" << tracks.timelines[_track]->getCurrentFrame() << ")" << " - track " << _track;


                    //RENDER
                    //NOTE: the rendering duration is only determined by the first track.
                    //NOTE: Rendering only runs if the first track is playing.
                    if(isRendering){
                        if(_track == 0){
                            render = false;
                            isRendering = false;
                            bMainApp->OSCsendIntToVMM(0,"/render",0);
                            ofLogNotice("RENDER") << "isRendering: " << isRendering << ", render: " << render;
                        }
                    }
                    
                    if(render){
                        //only do this on the first track
                        if(_track == 0){
                            
                            bMainApp->OSCsendIntToVMM(_track,"/render",data.getClipDuration(_track));
                            ofLogNotice("RENDER") << "/render " << data.getClipDuration(_track);
                            isRendering = true;
                            ofLogNotice("RENDER") << "isRendering:" << isRendering;
                        }
                    }
                    
                    //"CHAN"
                    
                    if(data.TL.tracks[_track].isRenderingChan){
                        data.TL.tracks[_track].renderTrackChan = false;
                        data.TL.tracks[_track].isRenderingChan = false;
                        ofLogNotice("CHAN") << "Track " << _track << " - isRenderingChan:" << data.TL.tracks[_track].isRenderingChan;
                        bMainApp->OSCsendIntToVMM(_track,"/renderChan",0);
                        
                    }
                    
                    //data.TL.tracks[_track].renderTrackChan;
                    
                    if(data.TL.tracks[_track].renderTrackChan){
                        ofLogNotice("CHAN") << "Track " << _track << " - /renderChan " << data.getClipDuration(_track);
                        bMainApp->OSCsendIntToVMM(_track,"/renderChan",data.getClipDuration(_track));
                        data.TL.tracks[_track].isRenderingChan = true;
                        
                        
                        //renderChan = false;
                        //isRenderingChan = false;
                        //ofLogNotice("CHAN") << "renderTrackChan:" << data.TL.tracks[_track].renderTrackChan;
                        //ofLogNotice("CHAN") << "isRenderingChan:" << isRendering;
                    }
                
                } else {
                    
                    //No, we haven't reached numberOfMeasures;
                    data.TL.tracks[_track].measureCount++;
                    
                    ofLogNotice("LINK")     << "tick - " << lastBeat << "|" << currentBeat
                                            << " >>>>  measureCount: " << data.TL.tracks[_track].measureCount
                                            << "(" << tracks.timelines[_track]->getCurrentFrame() << ")";
                }
            } else {
                ofLogNotice("LINK") << "tick - " << lastBeat << "|" << currentBeat << "(" << tracks.timelines[_track]->getCurrentFrame() << ")";
            }
            
            //copy the master beat over to the data.TL.tracks[x].nBeat
            data.setLBeat(_track, currentBeat);
            
            
        } else {
            ofLogNotice("LINK") << "tock - " << currentBeat;
        }
    } // END if getIsPlaying()
}

//-------------------------------------------------
void TimelinePanel::keyPressed(int key){
    
    //cout << "KEY: " << ofToString(key) << endl;
    
    if(key & OF_KEY_MODIFIER){                                  //F modifier keys
        if(key >= OF_KEY_F1 && key <= OF_KEY_F12){
            switch(key){
                case 257:
                    //F1
                    cout << "F1 - play track 1, clip 1" << endl;
                    bMainApp->playTLclip(0, 0);
                    
                    break;
                case 258:
                    //F2
                    //increment
                    cout << "F2 - play track 2, clip 1" << endl;
                    bMainApp->playTLclip(1, 0);
                    
                    break;
                case 259:
                    //F3
                    cout << "F3 - play track 3, clip 1" << endl;
                    bMainApp->playTLclip(2, 0);

                    break;
                case 260:
                    //F4
                    cout << "F4 - play track 4, clip 1" << endl;
                    bMainApp->playTLclip(3, 0);

                    break;
                case 261:
                    //F5
                    cout << "F5 - play track 5, clip 1" << endl;
                    bMainApp->playTLclip(4, 0);
                    
                    break;
                case 262:
                    //F6
                    cout << "F6 - play track 6, clip 1" << endl;
                    bMainApp->playTLclip(5, 0);
                    
                    break;
                case 263:
                    //F7
                    cout << "F7 pressed" << endl;
                    
                    break;
                case 264:
                    //F8
                    cout << "F8 pressed" << endl;
                    
                    break;
                case 265:
                    //F9
                    cout << "F9 pressed" << endl;
                    bMainApp->stopTLclip(0);//argument does nothing! stops all clips for now.
                    
                    break;
                case 266:
                    //F10
                    cout << "F10 pressed" << endl;
                    bMainApp->playTLclip(0, 0);
                    bMainApp->playTLclip(1, 0);
                    
                    break;
            }//end switch
        }else{
            
            switch(key){
                case OF_KEY_LEFT_SUPER:
                    bMainApp->ctrlKeyPressed = true;
                    ofLogNotice("KEYBOARD") << "ctrlKeyPressed = " << bMainApp->ctrlKeyPressed;
                    
                    break;
                case OF_KEY_RIGHT_SUPER:
                    cout << "Right Apple Pressed" << endl;
                   
                    break;
                case OF_KEY_CONTROL:
                    cout << "Control Pressed" << endl;
                    
                    break;
                case OF_KEY_RIGHT_ALT:
                    cout << "Right Alt/Opt Pressed" << endl;
                                    
                    break;
                case OF_KEY_RIGHT_SHIFT:
                    cout << "Right Shift Pressed" << endl;

                    break;
                case OF_KEY_LEFT_ALT:
                    cout << "Left Alt/Opt Pressed" << endl;

                    break;
                    
            }//switch
        }//if-else
    }//if
    
    
    //ACT ON SELECT KEYS
    if(key == 60 || key == 100){                                // 'd' or 'D' Key
        ofLogNotice("KEYBOARD") << "D or d pressed";
        if(bMainApp->ctrlKeyPressed){
            toggleDrawTrackData();
        }
    }
    
    
}//func

//-------------------------------------------------
void TimelinePanel::keyReleased(int key){
    if(key & OF_KEY_MODIFIER){
        if(key >= OF_KEY_F1 && key <= OF_KEY_F12){

            switch(key){
                case 257:
                    //cout << "F1 released" << endl;
                    
                    break;
                case 258:
                    //cout << "F2 released" << endl;
                    
                    break;
                case 259:
                    
                    //cout << "F3 released" << endl;
                    break;
            }//end switch
        }else{
            
            switch(key){
                case OF_KEY_LEFT_SUPER:
                    bMainApp->ctrlKeyPressed = false;
                    ofLogNotice("KEYBOARD") << "ctrlKeyPressed = " << bMainApp->ctrlKeyPressed;
                    break;
                case OF_KEY_RIGHT_SUPER:
                    cout << "Right Apple Released" << endl;
                    
                    break;
                case OF_KEY_CONTROL:
                    cout << "Control Released" << endl;
                    
                    break;
                case OF_KEY_RIGHT_ALT:
                    cout << "Right Alt/Opt Released" << endl;
                
                    break;
                case OF_KEY_RIGHT_SHIFT:
                    cout << "Right Shift Released" << endl;
                    
                    break;
                case OF_KEY_LEFT_ALT:
                    cout << "Left Alt/Opt Released" << endl;

                    break;
                    
            }
        }
    }
}

//-------------------------------------------------
void TimelinePanel::mousePressed(int x, int y, int button){
    
    if(isWithinBounds(x, y)) {
        ofLogVerbose("BODY") << "mousePressed() - (" << x << "," << y << ")";
        setPanelFocus(true);                        //focus THIS panel
    
        //turn off mouse input everytime you click on the timeline Panel.
        bMainApp->headerPanel.setEnableMouseInput(false);
        
        //exception - we don't want to block mouse input if dropdown is open.
        if(bMainApp->headerPanel.getDropdownOpen()){
            ofLogVerbose("BODY") << "a drop down is open!";
            bMainApp->headerPanel.setEnableMouseInput(true);
        } else {
            ofLogVerbose("BODY") << "no dropdowns in sight!";
            
        }
    }
}

//-------------------------------------------------
void TimelinePanel::mouseReleased(int x, int y, int button){
    
    if(isWithinBounds(x, y)) {
        if(bMainApp->headerPanel.getPanelFocus()){
            ofLogVerbose("BODY") << "mouseReleased() - NOTE: mousePressed() originated from HeaderPanel";
            bMainApp->headerPanel.setPanelFocus(false);         //unfocus HeaderPanel
        } else {
            ofLogVerbose("BODY") << "mouseReleased() - (" << x << "," << y << ")";
            setPanelFocus(false);                               //unfocus THIS panel
            bMainApp->headerPanel.setEnableMouseInput(true);    //enable mouseInput HeaderPanel
        }
    }
}

#pragma mark - DEBUG/STATS
//-------------------------------------------------
void TimelinePanel::drawTrackData(){

    float ml = 60;
    float mt = 10;

    float h_unit = 100;
    float v_unit = 15;

    
    //verdana9.drawString("MM: "+ofToString(data.TL.measures), h_unit*0+ml, _y+mt+v_unit*0);
    verdana9.drawString("BPM: "+ofToString(data.TL.bpm), h_unit*1+ml, _y+mt+v_unit*0);
    verdana9.drawString("FPS: "+ofToString(data.TL.fps), h_unit*2+ml, _y+mt+v_unit*0);
    
    //TODO - I don't think I use the loop param anymore??
    verdana9.drawString("LOOP: "+ofToString(data.TL.loop), h_unit*3+ml, _y+mt+v_unit*0);
    verdana9.drawString("METER: "+data.getMeter(data.getTrack(), data.getClip()), h_unit*4+ml, _y+mt+v_unit*0);
    //verdana9.drawString(" ", h_unit*5+ml, _y+mt+v_unit*0);
    verdana9.drawString("BAR: "+ofToString(data.TL.bar), h_unit*6+ml, _y+mt+v_unit*0);
    verdana9.drawString("BEAT: "+ofToString(data.TL.beat), h_unit*7+ml, _y+mt+v_unit*0);
    verdana9.drawString("FRAME: "+ofToString(data.TL.frame), h_unit*8+ml, _y+mt+v_unit*0);
    
    verdana9.drawString("AbletonLink BEAT: "+ofToString(bMainApp->AL.nbeat),h_unit*0+ml, _y+mt+v_unit+1);
    

    verdana9.drawString("TRACK:", 0, _y+mt+v_unit*3);
    verdana9.drawString("PAGE:", 0, _y+mt+v_unit*4);
    verdana9.drawString("CLIP:", 0, _y+mt+v_unit*5);
    verdana9.drawString("CUED:", 0, _y+mt+v_unit*6);
    verdana9.drawString("OSC", 0, _y+mt+v_unit*7);
    verdana9.drawString("MEASURES", 0, _y+mt+v_unit*8);
    verdana9.drawString("DURATION", 0, _y+mt+v_unit*9);
    
   
    for(int i=0; i<NUMBER_OF_TRACKS;i++){

        verdana9.drawString(ofToString(i+1), i*h_unit+ml, _y+mt+v_unit*3);//track
        verdana9.drawString(ofToString(data.getPage(i)+1), i*h_unit+ml, _y+mt+v_unit*4);//page
        verdana9.drawString(ofToString(data.getClip(i)+1), i*h_unit+ml, _y+mt+v_unit*5);//clip
        verdana9.drawString(data.getCuedToPlay(i) ? "true" : "false", i*h_unit+ml, _y+mt+v_unit*6);//cued
        verdana9.drawString(data.TL.tracks[i].enableOscOut ? "enabled" : "disabled", i*h_unit+ml, _y+mt+v_unit*7);//OSC
        verdana9.drawString(ofToString(data.getClipMeasures(i,data.getClip())),  i*h_unit+ml, _y+mt+v_unit*8);
        verdana9.drawString(ofToString(data.getClipDuration(i)),  i*h_unit+ml, _y+mt+v_unit*9);//duration
    }
    
    //only draw if a channel is selected
    if(data.getSelectedChannel() > -1 ){
        drawPageData(_y+mt+v_unit*10);                   //show the page tracks and keys
    }
}

//-------------------------------------------------
void TimelinePanel::drawPageData(int _mt){
    
    float ml = 60;
    float mt = _mt;
    
    float h_unit = 105;
    float v_unit = 15;
    
    int num_tracks_on_page = data.TL.tracks[data.getTrack()].tlPages[data.getPage()].tlChannels.size();
    string selectedPageChannel = "";
    
    string tlt = "TRACK " + ofToString(data.getTrack()+1) + " > PAGE " + ofToString(data.getPage()+1) + "[" + ofToString(data.getNumOfChannelsOnPage()) + "] - " ;
    
    tlt += "(";
    
    for(int i=0;i<num_tracks_on_page;i++){
        
        tlt += "[" + ofToString(data.TL.tracks[data.getTrack()].tlPages[data.getPage()].tlChannels[i].name) + ",";
        tlt += ofToString(data.TL.tracks[data.getTrack()].tlPages[data.getPage()].tlChannels[i].type) + "]";
        if(i<num_tracks_on_page-1){
            tlt += ", ";
        }
    }
    
    tlt += ")";
    verdana9.drawString(tlt, _x+ml, _y+mt);
    
    string keyframeTxt = "KEYS: ";
    string selKeyTxt = "SELECTED KEY: ";
    
    int kf;
    float kv;
    
    if (data.getNumOfChannelsOnPage() > 0){

        int keysInChannel = data.getNumOfKeysInChannel();
        int selectedKeyIndex = data.getSelectedKeyIndex();
        
        for(int j=0; j< keysInChannel;j++){
            
            keyframeTxt += "(" + ofToString(data.getSelectedKeyValue(j).x) + ":" + ofToString(data.getSelectedKeyValue(j).y) + ")";
            
            if(j<keysInChannel-1){
                keyframeTxt += ", ";
            }
        }

        selKeyTxt += ofToString(data.getSelectedKeyIndex()) + " - (" + ofToString(data.getSelectedKeyValue(selectedKeyIndex).x) + ":" + ofToString(data.getSelectedKeyValue(selectedKeyIndex).y) + ")";
        
        
    } else {
        keyframeTxt += " NONE";
        selKeyTxt += " NONE";
        
    }
    verdana9.drawString(keyframeTxt, _x+ml, _y+mt+v_unit*1);
    verdana9.drawString(selKeyTxt, _x+ml, _y+mt+v_unit*2);
}

//-------------------------------------------------
void TimelinePanel::toggleDrawTrackData(){
    
    
    showTrackData = !showTrackData;
    
    if(showTrackData){
        tracks.timelines[data.getTrack()]->hide();
    } else {
        tracks.timelines[data.getTrack()]->show();
    }
}

#pragma mark - EVENTS
//-------------------------------------------------
void TimelinePanel::actOnFocus(ofxTLTrackEventArgs & args){
    
//    cout << "timelinePanel::actOnFocus: " << args.name << endl;
    data.setSelectedChannel(args.name);
    
    if(args.name == "VMM"){
        
        bMainApp->headerPanel.mainUI.clampH->setText("--");
        bMainApp->headerPanel.mainUI.clampL->setText("--");
        
    } else {
        //test code to display track range.  Only if the track has keyframes
        ofxTLKeyframes* mytrack = (ofxTLKeyframes*)tracks.timelines[data.getTrack()]->getTrack(args.name);
        ofRange r = mytrack->getValueRange();
        
        
        //    cout << "timelinePanel::actOnFocus: range(" << ofToString(r.min) << "," << ofToString(r.max) << ")" << endl;
        
        bMainApp->headerPanel.mainUI.clampH->setText(ofToString(r.max));
        bMainApp->headerPanel.mainUI.clampL->setText(ofToString(r.min));
        
        
    }

    
    
}

//-------------------------------------------------
void TimelinePanel::actOnLossFocus(ofxTLTrackEventArgs & args){
    
//    cout << "timelinePanel::Loss Focus: " << args.name << endl;
    //data.setSelectedChannel(-1);
    
    //NO, keep the data persistent in the UI
    bMainApp->headerPanel.mainUI.clampH->setText("---");
    bMainApp->headerPanel.mainUI.clampL->setText("---");

}

//-------------------------------------------------
void TimelinePanel::timelineBangFired(ofxTLBangEventArgs & args){
    
//    cout << "timelinePanel::timelineBangFired: -- " << args.sender->getName() << "/" << args.track->getName()
//                                                    << " [" << ofToString(args.currentFrame) << "]"
//                                                    << " [" << ofToString(args.flag) << "]" << endl;

    //where is this coming from.
    string trackName = args.sender->getName();                          //e.g. "timeline0"
    string channelName = args.track->getName();                         //e.g. "noteOnAnPlay" or "localTransX"
    string outParam = "/"+channelName;
    
    //Identify the track number based on the name. convert char to int.
    //string track = trackName;
    char t = trackName[trackName.size()-1];
    int outTrack = (t-48);
    //cout << "BANG/FLAG TRACK NO: [" << outTrack << "]" << endl;
    
    
    
    if(channelName == "noteOnAndPlay"){
        bMainApp->OSCnoteOnAndPlay(outTrack, outParam, args.flag);
        
    } else {
        //cout << args.flag << endl;
        bMainApp->OSCsendToVMM(outTrack,outParam,ofToFloat(args.flag));
        
    }
    
    
}

//-------------------------------------------------
void TimelinePanel::timelineSwitched(ofxTLSwitchEventArgs & args){
    
//    cout << "timelinePanel::timelineBangFired: -- " << args.sender->getName() << "/" << args.track->getName()
//                                                    << " [" << (args.on ? "ON" : "OFF") << "]"
//                                                    << " [" << ofToString(args.switchName) << "]" << endl;
}

//-------------------------------------------------
void TimelinePanel::timelinePlaybackStarted(ofxTLPlaybackEventArgs &args){
    
    cout << "timelinePanel::timelinePlaybackStarted: -- " << args.sender->getName() << "/ frame:" << ofToString(args.currentFrame) << endl;
}

//-------------------------------------------------
void TimelinePanel::timelinePlaybackLooped(ofxTLPlaybackEventArgs &args){
    
    cout << "timelinePanel::timelinePlaybackLooped: -- frame:" << ofToString(args.currentFrame) << endl;
}

#pragma mark - ADD/REMOVE
//-------------------------------------------------
//Adds a channel to the current page
//call from when you create a track
void TimelinePanel::addTLChannelToSelected(string _name, int _type, float low, float high){
    //adds the track in the data
    data.addtlTrack(data.getTrack(),data.getPage(), _name, _type);
    //adds the track to timeline
    tracks.addTLTrack(data.getTrack(),data.getPageName(),_name, _type, low, high);      //pate = string
    
    //20180607 - needed to re-set the page after you create the track
    setPage(data.getPage());
    //cout << "TimelinePanel::addTLChannelToSelected - Page set to " << data.getPage() << endl;
    
}

//-------------------------------------------------
//Adds a channel to a specific page.
//called when the xml loads.
void TimelinePanel::addTLChannelToPage(int _track, int _page, string _name, int _type, float low, float high){
    string pageName = data.getPageName(_page);
    //adds the track in the data
    data.addtlTrack(_track,_page, _name, _type, low, high);
    //adds the track to timeline
    tracks.addTLTrack(_track,pageName,_name, _type, low, high);
    
    //20180607 - dont re-set the page if you are loading from XML.
    //setPage(_page);
    //cout << "TimelinePanel::addTLChannelToPage - Page set" << endl;
}

//-------------------------------------------------
void TimelinePanel::remTLChannel(){
    if(data.getNumOfChannelsOnPage() > 0){
        cout << "trying to remove: " << data.getSelectedChannelName() << endl;
        
        string track2remove = data.getSelectedChannelName();
        data.remtlTrack(track2remove);
        tracks.remTLTrack(data.getTrack(),data.getPage(),track2remove);
        
        //clear the selection when you remove a track
        data.setSelectedChannel(-1);
        
    } else {
        cout << "not enough tracks to do remove" << endl;
    }
}

#pragma mark - SAVE/LOAD
//-------------------------------------------------
string TimelinePanel::getProjectPath(){
    return projectSavePath + "/";
}

//-------------------------------------------------
string TimelinePanel::getProjectFile(){
    return projectSaveFile;
}

//-------------------------------------------------
string TimelinePanel::getTrackAndClipPath(int _track, int _clip){
    return TRACK_DIR "_" + ofToString(_track) + "/" CLIP_DIR "_" + ofToString(_clip) + "/";
}

//-------------------------------------------------
void TimelinePanel::setProjectPathAndFile(ofFileDialogResult fileResult){
    
    
    //TODO - Switch ofFile
    
    
    string path = fileResult.filePath;
    
    char sep = '/';
    //do a reverse find
    size_t i = path.rfind(sep, path.length());
    if (i != string::npos) {
        projectSavePath = path.substr(0, i);
        projectSaveFile = path.substr(i+1, path.length() - i);
        
        projectSet = true;
    } else {
        
        projectSet = false;
    }

    cout << "projectSavePath:  " << projectSavePath << endl;
    cout << "projectSaveFile:  " << projectSaveFile << endl;
}



//-------------------------------------------------
void TimelinePanel::saveTLProject(){
    ofLogNotice("SAVE") << "...Saving Project: ";
    
    ofxXmlSettings savedTrackSettings;
    savedTrackSettings.addTag("project");
    savedTrackSettings.pushTag("project");
    savedTrackSettings.addValue("bpm", data.TL.bpm);
    //TODO - ADD MORE
    
    savedTrackSettings.popTag();
    
    cout << "vmm file path: " << getProjectPath() + getProjectFile() << endl;
    savedTrackSettings.saveFile(getProjectPath() + getProjectFile());
}

//-------------------------------------------------
void TimelinePanel::saveTLPage(int _track, int _page, int _clip){
    //save the keyframe data from each track
    //NOTE: In order to specifically target a single page
    //      You will need to add an additional function
    //      e.g. ofxTimeline::savePageTracksToFolder(int page, string folderPath)
    
    if(data.getNumOfChannelsOnPage(_page)>0){
        ofLogNotice("SAVE") << "Saving channels from tr: " << ofToString(_track) << " pg: " << ofToString(_page);
        
        //set where to save the file (project)
        //TODO - I don't like the way the getProjectPath() is referenced here.
        string filePath = getProjectPath() + getTrackAndClipPath(_track,_clip);
        ofLogNotice("SAVE") << "TimelinePanel::saveTLPage " << filePath;
        
        //CALL TO SAVE ALL TRACKS (assuming the track is ofxTLKeyframes)
        //headerUI->timelinePanel->
        //ofxTimeline::saveTracksToFolder->
        //ofxTLPage::saveTracksToFolder->
        //VIRTUAL<ofxTLTrack>->ofxTLKeyframes::save()->getXMLStringForKeyframes()
        tracks.timelines[_track]->saveTracksToFolder(filePath);
        
        //save the clip settings
        string clipName = "clip_" + ofToString(_clip);
        string savedClipSettingsPath = filePath + clipName + ".xml";
        ofxXmlSettings savedClipSettings;
        savedClipSettings.addTag(clipName);
        savedClipSettings.pushTag(clipName);
        savedClipSettings.addValue("numberOfMeasures", data.TL.tracks[_track].tlClips[_clip].numberOfMeasures);//TODO - get data
        savedClipSettings.addValue("loop", 1);
        savedClipSettings.addValue("mute", 0);
        savedClipSettings.addValue("solo", 0);
        savedClipSettings.addValue("mBeats", data.TL.tracks[_track].tlClips[_clip].mBeats);
        savedClipSettings.addValue("mUnits", data.TL.tracks[_track].tlClips[_clip].mUnits);
        savedClipSettings.saveFile(savedClipSettingsPath);
        
        //save the page settings.
        string pageName = data.getPageName(_page);
        
        auto tracksPage = tracks.timelines[_track]->getPage(pageName);
        
        string filenamePanel = filePath + pageName + "_settings.xml";
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
            savedSettings.addValue("rangeH", data.TL.tracks[_track].tlPages[_page].tlChannels[i].channelRange.max);
            savedSettings.addValue("rangeL", data.TL.tracks[_track].tlPages[_page].tlChannels[i].channelRange.min);
            savedSettings.popTag();
            
            //what is being saved
            
            ofLogNotice("SAVE") << "TR" << _track << ", " << pageName << ", " << tracksPage->getTracks()[i]->getName() << "["
            << data.TL.tracks[_track].tlPages[_page].tlChannels[i].channelRange.min << ","
            << data.TL.tracks[_track].tlPages[_page].tlChannels[i].channelRange.max << "]";
            
        }
        savedSettings.popTag();
        
        savedSettings.saveFile(filenamePanel);
        
        
    } else {
        ofLogNotice("SAVE") << "There are not enough channels on the page " << ofToString(_page) << " to save anything.";
        
    }

}

//-------------------------------------------------
void TimelinePanel::saveTLTrackPages(){
    
    //loop through the pages and save all the channels on each page.
    for (int i=0; i<NUMBER_OF_TRACKS; i++){
        saveTLPage(data.getTrack(), i, data.getClip());
    }

}

//-------------------------------------------------
void TimelinePanel::saveTLAllTracks(){
    //loop through the TRACKS and save all the channels on each page.
    for (int t=0; t<NUMBER_OF_TRACKS; t++){
        for (int p=0; p<NUMBER_OF_TRACKS; p++){
            saveTLPage(t, p, data.getClip());
        }
    }
}

//-------------------------------------------------
void TimelinePanel::loadTLProject(ofFileDialogResult _openFileResult){
    ofLogNotice("LOAD") << "...Loading Project: ";
    
    string filePath = _openFileResult.filePath;
    
    ofxXmlSettings xml;
    if( xml.loadFile(filePath) ){
        ofLogVerbose("LOAD") <<"TimelinePanel::loadTLProject - "<< _openFileResult.fileName <<" loaded.";
    }else{
        ofLogError("LOAD") <<  "TimelinePanel::loadTLProject - unable to load ";
        return;
    }
    
    int bpm = xml.getValue("project:bpm", 0);
    
    data.setBPM(ofToString(bpm));
    
    
    //Loop through all the tracks and load in the xml from the project file.
    //this data is the same on all tracks.
    for(int i=0;i<NUMBER_OF_TRACKS;i++){
        tracks.timelines[i]->setNewBPM(data.getBPM());
    }
    
    //set the ableton link tempo   
    bMainApp->AL.setTempo(data.getBPM());
    
    //set ableton link
    ofLogNotice("LOAD") << "BPM: " << ofToString(bpm);
    
    //set UI - bpm
    bMainApp->headerPanel.setBpmUI(bpm);
    
    //set UI - frames
    bMainApp->setFramesUI();
    
    //set UI - fps
    
}


//-------------------------------------------------
void TimelinePanel::loadTLPage(int _track, int _page, int _clip){
    //Loop through all the pages(_page) and add channels.
    
    //----------------------------------
    //-:Load Xml file
    //TODO: I don't like the way the getProjectPath() is referenced here.
    string filePath = getProjectPath() + getTrackAndClipPath(_track,_clip);
    //ofLogNotice("LOAD") << "TimelinePanel::loadTLPage " << filePath;
    
    string pageName = data.getPageName(_page);
    
    string filenamePanel = filePath + pageName + "_settings.xml";
    ofxXmlSettings xml;
    
    
    if( xml.loadFile(filenamePanel) ){
        ofLogVerbose("LOAD") <<"timelinePanel::loadTLPage - "<< filenamePanel <<" loaded.";
    }else{
        ofLogVerbose("LOAD") <<  "timelinePanel::loadTLPage - unable to load " << filenamePanel ;
        return;
    }
    
    //----------------------------------
    //-:Create tracks from loaded P<page no>_setting.xml.
    int numOfChannels = xml.getValue("page:tlChannels:tlChannels-num", 0);
    
    for (int i=0; i<numOfChannels; i++){
        string trackName = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":name", "");
        string trackType = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":type", "");
        string rangeH = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":rangeH", "");
        string rangeL = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":rangeL", "");
        
        auto tracksPage = tracks.timelines[_track]->getPage(pageName);
        
        //If track doesnt exist and its not default -> create it.
        if(trackName != "DEFAULT" && tracksPage->getTrack(trackName)==NULL){
            
            //ADD CHANNELS BY TYPE
            if(trackType=="Curves"){
                //add the track and data.
                addTLChannelToPage(_track, _page, trackName, 1, ofToFloat(rangeL), ofToFloat(rangeH));
                
            }else if(trackType=="Bangs"){
                addTLChannelToPage(_track, _page, trackName, 2);
            
            }else if(trackType=="Switches"){
                addTLChannelToPage(_track, _page, trackName, 3);
                
            }else if(trackType=="Flags"){
                addTLChannelToPage(_track, _page, trackName, 4);
                
            }else if(trackType=="Buttons"){
                //1. read the VMM.xml
                
                //TODO: delete (Why is this here)
                //string vmmXMLfile = filePath + trackName + "_" + ofToString(_track) + ".xml";
                
                /*
                string vmmXMLfile = filePath + trackName + ".xml";
                ofxXmlSettings vmmxml;
                if( vmmxml.loadFile(vmmXMLfile) ){
                    ofLogVerbose("LOAD") <<"timelinePanel::loadTLPage - ofxTLVMMControl - "<< vmmXMLfile <<" loaded.";
                }else{
                    ofLogError("LOAD") <<  "timelinePanel::loadTLPage - ofxTLVMMControl - unable to load " << vmmXMLfile ;
                    return;
                }
                */
                 
                //2. add a ofxTLVMMControl track
                addTLChannelToPage(_track, _page, trackName, 6);
                
            }else if(trackType=="Notes"){
                
                addTLChannelToPage(_track, _page, trackName, 7);
            }
            
            
        }
    }
}

//-------------------------------------------------
void TimelinePanel::loadTLTrackPages(){

    //Load the current selected track.
    int t = data.getTrack();
    int p = data.getPage();
    int c = data.getClip();
    
    //Create channels(tracks) as listed for each Page (P<page no>_setting.xml)
    for(int p2=0; p2< NUMBER_OF_PAGES; p2++){
            loadTLPage(t, p2, c);
    }

    
    setPage(p);
    
    //TODO: If track contain VMMControl, function in params from file
    if(tracks.timelines[t]->hasTrack("VMM")){
        auto vmmTrack = (ofxTLVMMControl*)tracks.timelines[t]->getTrack("VMM");
        //loop through clips and load VMM.xml
        for(int i=0;i<10;i++){
            string fp = getProjectPath() + getTrackAndClipPath(t, i);
            vmmTrack->loadClipXML(fp, i);
        }
    }
        
    //1.load track XML
    //2.switch VMMControl params
    //3.load the clip.xml
    //4.set [number of measures,duration] in clip
    loadTLClip(t, c);
    
    //4. set the clip in the curren track
    //5. set the duration in the timeline on the track.
    setClip(c);
    
    //set UI - frames UI
    int d = data.getClipDuration(c);
    bMainApp->headerPanel.setFramesUI(d);
    
    //set UI - measures UI
    int m = data.getClipMeasures(t, c);
    bMainApp->headerPanel.setMeasuresUI(m);
}

//-------------------------------------------------
void TimelinePanel::loadTLAllTracks(){
    //Load all the channels on from ALL tracks if they have content.
    //Load up track 0, clip 0
    
    //For each track create the channels.
    for(int t=0;t < NUMBER_OF_TRACKS; t++){
        //Create channels(tracks) as listed for each Page (P<page no>_setting.xml)
        for(int p=0;p < NUMBER_OF_PAGES; p++){
            
                //TODO - LOAD is loading too much
                loadTLPage(t, p, 0);

        }
        
        if(tracks.timelines[t]->hasTrack("VMM")){
            auto vmmTrack = (ofxTLVMMControl*)tracks.timelines[t]->getTrack("VMM");
            //loop through clips and load VMM.xml
            for(int i=0;i<10;i++){
                string fp = getProjectPath() + getTrackAndClipPath(t, i);
                vmmTrack->loadClipXML(fp, i);
            }
        }
        
    }
    //set the display track
    setTLTrack(0);
    
    //set the display page.
    setPage(0);
    
    //1.load track XML
    //2.switch VMMControl params
    //3.load the clip.xml
    //4.set [number of measures,duration] in clip
    loadTLClip(0, 0);
    
    //load all the track.xml for the clip.
    setClip(0);
    
    //set UI - frames UI
    int d = data.getClipDuration(0);
    bMainApp->headerPanel.setFramesUI(d);
    
    //set UI - measures UI
    int m = data.getClipMeasures(0, 0);
    bMainApp->headerPanel.setMeasuresUI(m);
    
}


//-------------------------------------------------
void TimelinePanel::loadTLClip(int _track, int _clip) {
    
    //1.load track XML
    //  -create the path to xml
    string filePath = getProjectPath() + getTrackAndClipPath(_track,_clip);
    
    //  -load the tracks from xml.
    ofLogVerbose("LOAD") <<"1. load track XML from: " << filePath;
    tracks.timelines[_track]->loadTracksFromFolder(filePath);
    
    //2.switch VMMControl params
    if(tracks.timelines[_track]->hasTrack("VMM")){
        //switch to the correct data clips[]
        auto vmmTrack = (ofxTLVMMControl*)tracks.timelines[_track]->getTrack("VMM");

        //TODO: do params exist for clip?
        vmmTrack->setClipParams(_clip);
    }
    
    //3.load the clip_<CLIP_NO>.xml
    //  -load the clip settings.
    string clipName = "clip_" + ofToString(_clip);
    string savedClipSettingsPath = filePath + clipName + ".xml";
    ofxXmlSettings savedClipSettings;
    
    if( savedClipSettings.loadFile(savedClipSettingsPath) ){
        ofLogVerbose("LOAD") <<"2. load the clip.xml -- " << savedClipSettingsPath <<" loaded.";
    }else{
        ofLogError("LOAD") <<  "timelinePanel::loadTLClip - unable to load " << savedClipSettingsPath ;
        return;
    }
    
    //4.set [number of measures,duration] in clip
    //  -number of measures
    string param1 = "clip_" + ofToString(_clip) + ":numberOfMeasures";
    int numOfMeasures = savedClipSettings.getValue(param1, 0);
    
    //  -duration
    data.TL.tracks[_track].tlClips[_clip].numberOfMeasures = numOfMeasures;
    data.TL.tracks[_track].tlClips[_clip].duration = data.calculateFramesInMeasures(numOfMeasures, data.TL.bpm, data.TL.fps);
    
    ofLogVerbose("LOAD") << "3. set [number of measures,duration] in clip ["
                        << data.getClipMeasures(_track, _clip) << "," << data.getClipDuration(_track)
                        << "]";
    
}


#pragma mark - PLAY FUNCTIONS
//-------------------------------------------------
void TimelinePanel::playTLclip(int _track, int _clip){
    ofLogNotice("TRACK")    << "TimelinePanel::playTLclip("
    << _track << "," << _clip
    << ") -- nbeat:" << data.getNBeat(_track);
    
    resetMeasureLoop(_track);

    //1.load track XML
    //2.switch VMMControl params
    //3.load the clip.xml
    //4.set [number of measures,duration] in clip
    loadTLClip(_track, _clip);
    
    //4. set which clip is playing in the current track
    //5. set the duration in the timeline on the track.
    setClip(_track, _clip);
    
    //START IT UP
    data.setCuedToPlay(_track, true);
    
    //enable OSC OUT
    data.TL.tracks[_track].enableOscOut = true;
    
    //TODO: not needed
    ofLogNotice("TRACK") << "TimelinePanel::playTLclip() > " << "TODO - THIS IS WHERE I SEND ALL MY TRACK DATA TO VMM";
    
    /*
    //TODO: not needed
    if(tracks.timelines[_track]->hasTrack("VMM")){
        auto vmmTrack = (ofxTLVMMControl*)tracks.timelines[_track]->getTrack("VMM");
        bMainApp->OSCsendToVMM(_track, "/localCopies", vmmTrack->test_localCopies);   //TODO:  confusion track 0 is track 1 in VMM
    }
     */
}

//-------------------------------------------------
void TimelinePanel::stopTLclip(int _clip){
    
    for(int i=0; i<NUMBER_OF_TRACKS; i++){
        if(tracks.timelines[i]->getIsPlaying()){
            tracks.timelines[i]->stop();
            data.setCuedToPlay(i, false);
            
            
        }
        
        //clear all the tracks
        bMainApp->OSCsendToVMM(i, "/clear", 1);

        
        //disable OSC OUT
        data.TL.tracks[i].enableOscOut = false;
        tracks.timelines[i]->setPercentComplete(0);
        resetMeasureLoop(i);//resets them all.
        

    }
    
    ofLogNotice("OSC_OUT") << "DRIVE OFF";
    
}


#pragma mark - PANEL
//-------------------------------------------------
void TimelinePanel::setTLTrack(int _track){
    
    data.setTrack(_track);
    tracks.showSelectedTimelineTrack(_track);
    
    //tracks.enableVMMControlTrack(_track);
    
    for(int i=0; i<tracks.timelines.size();i++){
        if(tracks.timelines[i]->hasTrack("VMM")){
            if(i == _track){
                
                //only enable if the track is showing
                if(data.isChannelOnPage("VMM", data.getPage(_track))){
                    tracks.timelines[i]->getTrack("VMM")->enable();
                    cout << "track " << i << " - VMM enabled()" << endl;
                }
                
            } else {
                
                tracks.timelines[i]->getTrack("VMM")->disable();
                cout << "track " << i << " - VMM disabled()" << endl;
            }
        }
    }
    
    //data.getSelectedChannelOnTrackPage(_track, data.getPage(_track));
    
}

//-------------------------------------------------
void TimelinePanel::setPage(int _page){

    data.setPage(_page);
    tracks.setPage(data.getTrack(), _page);
    if(data.getSelectedChannel() > -1){
        tracks.highlightFocuedTrack(data.getTrack(), data.getSelectedChannelName());
    }
    
    //Checks if the VMM track is on the page.
    if(tracks.timelines[data.getTrack()]->hasTrack("VMM")){
        if(data.isChannelOnPage("VMM", _page)){
            
            //accept events.
            tracks.timelines[data.getTrack()]->getTrack("VMM")->enable();
            
        } else {
            
            //turn off accept events on VMM track
            ofLog() << "not on page " << _page;
            tracks.timelines[data.getTrack()]->getTrack("VMM")->disable();
        }
    }

}

//-------------------------------------------------
void TimelinePanel::setClip(int _track, int _clip){
    
    //set Clip on SPECIFIED TRACK
    data.setClip(_clip, _track);
    ofLogVerbose("LOAD") << "4. set the clip in track -- " << data.getClip(_track);
    
    //201280202 - commented out cause it's duplicate - [notice ] LOAD: 1. load track XML
//    string filePath = getProjectPath() + getTrackAndClipPath(_track, _clip);
//    tracks.timelines[_track]->loadTracksFromFolder(filePath);
//    ofLogNotice("LOAD") << "5. load the track keyframes --  " << filePath;
    
    setTrackDuration(_track);
    ofLogVerbose("LOAD") << "5. set the duration in the timeline on the track.";
}

//-------------------------------------------------
void TimelinePanel::setClip(int _clip){
    
    //set Clip on the CURRENT SELECTED TRACK
    data.setClip(_clip, data.getTrack());
    ofLogVerbose("LOAD") << "4. set the clip in the curren track";
    
    //201280202 - commented out cause it's duplicate - [notice ] LOAD: 1. load track XML
//    string filePath = getProjectPath() + getTrackAndClipPath(data.getTrack(), _clip);
//    tracks.timelines[data.getTrack()]->loadTracksFromFolder(filePath);
//    ofLogNotice("LOAD") << "5. load the track keyframes --  " << filePath;
    
    setTrackDuration(data.getTrack());
    ofLogVerbose("LOAD") << "5. set the duration in the timeline on the track.";
}

//--------------------------------------------------------------
void TimelinePanel::resetMeasureLoop(int _track){
    
    if(tracks.timelines[_track]->getIsPlaying()){
        
        ofLogNotice("LINKFLIP") << "TimelinePanel::setMeasureLoop(" << ofToString(_track) << ") -- isPlaying()";
        
    }
        
        data.setNBeat(_track, -1);
        data.setLBeat(_track, -2);
        
        data.TL.tracks[_track].measureCount = 0;
}

//--------------------------------------------------------------
void TimelinePanel::setMeasuresInClip(int _track, string _measures){
    
    //1. calculate the number of frames based on BPM
    //2. set clip.numberOfMeasures and clip.duration in each tracks.tlClips. END
    data.setClipMeasures(_track, ofToInt(_measures));
    
    //1. look up the clip duration in frames. END
    //2. set the frames in the timelines. END
    setTrackDuration(_track);
    
}

//--------------------------------------------------------------
void TimelinePanel::setTrackDuration(int _track){

    //look up the clip duration in frames.
    int d = data.getClipDuration(_track);

    //set the frames in the timelines.
    tracks.timelines[_track]->setOutPointAtFrame(d);
    tracks.timelines[_track]->setDurationInFrames(d);
   
}

#pragma mark - OSC
//--------------------------------------------------------------
void TimelinePanel::sendOSCfromTimeline(int _track){

    if(data.TL.tracks[_track].enableOscOut){
        //get all the channels on a track
        //loop through all the pages.
        for (int p=0;p<10;p++){
            if(data.TL.tracks[_track].tlPages[p].tlChannels.size()>0){

                for (int j=0;j<data.TL.tracks[_track].tlPages[p].tlChannels.size();j++){
                    
                    //output only if it's a curve.
                    if(data.TL.tracks[_track].tlPages[p].tlChannels[j].type == 1){
                        int outTrack = _track;
                        string param = data.TL.tracks[_track].tlPages[p].tlChannels[j].name;
                        string outParam = "/"+data.TL.tracks[_track].tlPages[p].tlChannels[j].name;
                        
                        bMainApp->OSCsendToVMM(outTrack,outParam,tracks.timelines[_track]->getValue(param));
                        
                    }
                    
                    //output only if it's a ofxTLNotes track
                    if(data.TL.tracks[_track].tlPages[p].tlChannels[j].type == 7){
                        int outTrack = _track;
                        string param = data.TL.tracks[_track].tlPages[p].tlChannels[j].name;
                        //string outParam = "/notes";
                        
                        //we can cast becasue ofxTLVMMNotes is subclass of ofxTLTrack
                        ofxTLVMMNotes* notesTrack  = (ofxTLVMMNotes*)tracks.timelines[_track]->getTrack(param);

                        // #11 - pass in the time in ms to the track.
                        notesTrack->playTLVMMnotesTrack(tracks.timelines[_track]->getCurrentTimeMillis());
                    }
                }//for
            }//if
        }//for
    }//if
}

#pragma mark - CHANNEL MODIFICATIONS
//--------------------------------------------------------------
void TimelinePanel::setChannelRangeHigh(float _val){
    //set the ofRange of the data track
    data.TL.tracks[data.getTrack()].tlPages[data.getPage()].tlChannels[data.getSelectedChannel()].channelRange.setMax(_val);
    
    //now set the range in timeline track
    auto selTrack = (ofxTLKeyframes*)tracks.timelines[data.getTrack()]->getTrack(data.getSelectedChannelName());
    selTrack->setValueRangeMax(_val);
}

//--------------------------------------------------------------
void TimelinePanel::setChannelRangeLow(float _val){
    //set the ofRange of the data track
    data.TL.tracks[data.getTrack()].tlPages[data.getPage()].tlChannels[data.getSelectedChannel()].channelRange.setMin(_val);
    
    //now set the range in timeline track
    auto selTrack = (ofxTLKeyframes*)tracks.timelines[data.getTrack()]->getTrack(data.getSelectedChannelName());
    selTrack->setValueRangeMin(_val);
}


//-------------------------------------------------
//TESTS
#pragma mark - TESTS
//=================================================
void TimelinePanel::testKeyframeFunction(int _track, string _channelName){
    //test on how to get at keyframe data in a track
    
    //auto mytrack = tracks.timelines[data.getTrack()]->getTrack("GLOBAL ROTATE X");
    ofxTLKeyframes* mytrack = (ofxTLKeyframes*)tracks.timelines[_track]->getTrack(_channelName);
    
    cout << "How many keys are selected: " << mytrack->getSelectedItemCount() << endl;
    
    //mytrack->setValueRangeMax(100);
    //mytrack->quantizeKeys(10);
    
    cout << "The value of the second keyframe is: " << ofToString(mytrack->getKeyframes()[1]->value) << endl;
    
    mytrack->getKeyframes()[0]->value = 0.5;
}
