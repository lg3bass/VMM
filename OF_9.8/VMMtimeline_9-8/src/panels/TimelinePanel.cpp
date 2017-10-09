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
        
        //reset/setup track metadata.
        setMeasureLoop(i);
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
        //ofLogNotice("LINKFLIP") << "getIsPlaying()" << " - track " << _track;
        
        int currentBeat = data.getNBeat(_track);
        int lastBeat = data.getLBeat(_track);
        
        if(currentBeat != lastBeat){
            //ofLogVerbose("LINK") << "New Measure" << " - track " << _track;
            
            //resets the measure counter
            if(data.isDownbeat(_track)){
                ofLogVerbose("LINK") << "isDownbeat()" << " - track " << _track;
                if(data.TL.tracks[_track].measureCount == data.TL.tracks[_track].measureLength){
                    
                    tracks.timelines[_track]->setPercentComplete(0);
                    data.TL.tracks[_track].measureCount = 1;
                    
                    ofLogNotice("LINKFLIP") << "tick - " << lastBeat << "|" << currentBeat
                                            << " >>>>  measureCount(FLIP): " << data.TL.tracks[_track].measureCount
                                            << "(" << tracks.timelines[_track]->getCurrentFrame() << ")" << " - track " << _track;
                } else {
                    
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
                    //decrement
                    if(data.getNumOfChannelsOnPage() > 1){
                        
                        int selected_page = data.getSelectedChannel();                  //calculates the selected_page if using keyboard
                        
                        if(selected_page > 0){
                            selected_page--;
                        } else {
                            selected_page = data.getNumOfChannelsOnPage()-1;
                        }
                        bMainApp->selectChannel(selected_page);                         //set the selected channel and gui
                        
                        cout << "F1 pressed - decrement track selection" << endl;
                        
                    } else {
                        
                        cout << "F1 pressed - not enough timelines on page" << endl;
                    }
                    
                    break;
                case 258:
                    //F2
                    //increment
                    if(data.getNumOfChannelsOnPage() > 1){
                        
                        int selected_page = data.getSelectedChannel();                  //calculates the selected_page if using keyboard
                        
                        if(selected_page < data.getNumOfChannelsOnPage()-1){
                            selected_page++;
                        } else {
                            selected_page = 0;
                        }
                        
                        bMainApp->selectChannel(selected_page);                         //set the selected channel and gui
                        
                        cout << "F2 pressed - increment track selection" << endl;
                    } else {
                        
                        cout << "F2 pressed - not enough timelines on page" << endl;
                    }
                    
                    break;
                case 259:
                    //F3
                    cout << "F3 - play track 1, clip 1" << endl;
                    bMainApp->playTLclip(0, 0);

                    
                    break;
                case 260:
                    //F4
                    cout << "F4 - play track 1, clip 2" << endl;
                    bMainApp->playTLclip(0, 1);
                    
                    break;
                case 261:
                    //F5
                    cout << "F5 - play track 2, clip 1" << endl;
                    bMainApp->playTLclip(1, 0);
                    
                    break;
                case 262:
                    //F6
                    cout << "F6 pressed" << endl;
                    bMainApp->stopTLclip(0);//argument does nothing! stops all clips for now.
                    
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
    verdana9.drawString("LOOP: "+ofToString(data.TL.loop), h_unit*3+ml, _y+mt+v_unit*0);
    verdana9.drawString("sigBeat: "+ofToString(data.TL.mBeats), h_unit*4+ml, _y+mt+v_unit*0);
    verdana9.drawString("sigUnit: "+ofToString(data.TL.mUnits), h_unit*5+ml, _y+mt+v_unit*0);
    verdana9.drawString("BAR: "+ofToString(data.TL.bar), h_unit*6+ml, _y+mt+v_unit*0);
    verdana9.drawString("BEAT: "+ofToString(data.TL.beat), h_unit*7+ml, _y+mt+v_unit*0);
    verdana9.drawString("FRAME: "+ofToString(data.TL.frame), h_unit*8+ml, _y+mt+v_unit*0);
    
    verdana9.drawString("AbletonLink BEAT: "+ofToString(bMainApp->AL.nbeat),h_unit*0+ml, _y+mt+v_unit+1);
    

    verdana9.drawString("TRACK:", 0, _y+mt+v_unit*3);
    verdana9.drawString("PAGE:", 0, _y+mt+v_unit*4);
    verdana9.drawString("CLIP:", 0, _y+mt+v_unit*5);
    verdana9.drawString("CUED:", 0, _y+mt+v_unit*6);
    verdana9.drawString("OSC", 0, _y+mt+v_unit*7);
    
   
    for(int i=0; i<NUMBER_OF_TRACKS;i++){

        verdana9.drawString(ofToString(i+1), i*h_unit+ml, _y+mt+v_unit*3);//track
        verdana9.drawString(ofToString(data.getPage(i)+1), i*h_unit+ml, _y+mt+v_unit*4);//page
        verdana9.drawString(ofToString(data.getClip(i)+1), i*h_unit+ml, _y+mt+v_unit*5);//clip
        verdana9.drawString(data.getCuedToPlay(i) ? "true" : "false", i*h_unit+ml, _y+mt+v_unit*6);//cued
        
        verdana9.drawString(data.TL.tracks[i].enableOscOut ? "enabled" : "disabled", i*h_unit+ml, _y+mt+v_unit*7);
    }
    
    //only draw if a channel is selected
    if(data.getSelectedChannel() > -1 ){
        drawPageData(_y+mt+v_unit*5);                   //show the page tracks and keys
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

#pragma mark - SELECT CHANNELS
//-------------------------------------------------
void TimelinePanel::actOnFocus(ofxTLTrackEventArgs & args){
    
    cout << "timelinePanel::actOnFocus: " << args.name << endl;
    data.setSelectedChannel(args.name);
    
    
    //test code to display track range.
    ofxTLKeyframes* mytrack = (ofxTLKeyframes*)tracks.timelines[data.getTrack()]->getTrack(args.name);
    ofRange r = mytrack->getValueRange();
    
    
    cout << "timelinePanel::actOnFocus: range(" << ofToString(r.min) << "," << ofToString(r.max) << ")" << endl;
    
    bMainApp->headerPanel.mainUI.clampH->setText(ofToString(r.max));
    bMainApp->headerPanel.mainUI.clampL->setText(ofToString(r.min));
    
    
    
}

//-------------------------------------------------
void TimelinePanel::actOnLossFocus(ofxTLTrackEventArgs & args){
    
    cout << "timelinePanel::Loss Focus: " << args.name << endl;
    //data.setSelectedChannel(-1);
    
    //NO, keep the data persistent in the UI
    bMainApp->headerPanel.mainUI.clampH->setText("---");
    bMainApp->headerPanel.mainUI.clampL->setText("---");

}

#pragma mark - ADD/REMOVE
//-------------------------------------------------
void TimelinePanel::addTLChannelToSelected(string _name, int _type, float low, float high){
    //adds the track in the data
    data.addtlTrack(data.getTrack(),data.getPage(), _name, _type);
    //adds the track to timeline
    tracks.addTLTrack(data.getTrack(),data.getPageName(),_name, _type, low, high);      //pate = string

}

//-------------------------------------------------
void TimelinePanel::addTLChannelToPage(int _track, int _page, string _name, int _type, float low, float high){
    string pageName = data.getPageName(_page);
    //adds the track in the data
    data.addtlTrack(_track,_page, _name, _type, low, high);
    //adds the track to timeline
    tracks.addTLTrack(_track,pageName,_name, _type, low, high);
    
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
string TimelinePanel::getFilePath(int _track, int _clip){
    return TRACK_DIR "_" + ofToString(_track) + "/" CLIP_DIR "_" + ofToString(_clip) + "/";
}

//-------------------------------------------------
void TimelinePanel::saveTLPage(int _track, int _page, int _clip){
    //save the keyframe data from each track
    //NOTE: In order to specifically target a single page
    //      You will need to add an additional function
    //      e.g. ofxTimeline::savePageTracksToFolder(int page, string folderPath)
    
    
    
    if(data.getNumOfChannelsOnPage(_page)>0){
        cout << "Saving channel on page " << ofToString(_page) << endl;
        
        string filePath = getFilePath(_track,_clip);
        tracks.timelines[_track]->saveTracksToFolder(filePath);
        
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
        cout << "There are not enough channels on the page " << ofToString(_page) << " to save anything." << endl;
        
    }

}

//-------------------------------------------------
void TimelinePanel::saveTLTrackPages(){
    //how many pages?
    
    //loop through the pages and save all the channels on each page.
    for (int i=0; i<NUMBER_OF_TRACKS; i++){
        saveTLPage(data.getTrack(), i, data.getClip());
    }

}

//-------------------------------------------------
void TimelinePanel::saveTLAllTracks(){
    
}

//-------------------------------------------------
void TimelinePanel::loadTLPage(int _track, int _page, int _clip){
    //Loop through all the pages(_page) and add channels.
    
    //----------------------------------
    //-:Load Xml file
    string filePath = getFilePath(_track,_clip);
    
    //string pageName = data.getPageName();
    string pageName = data.getPageName(_page);
    
    string filenamePanel = filePath + pageName + "_settings.xml";
    ofxXmlSettings xml;
    
    if( xml.loadFile(filenamePanel) ){
        ofLogVerbose("LOAD") <<"timelinePanel::loadTLPage - "<< filenamePanel <<" loaded.";
    }else{
        ofLogError("LOAD") <<  "timelinePanel::loadTLPage - unable to load " << filenamePanel ;
        return;
    }
    
    //----------------------------------
    //-:Create tracks from loaded settings.
    int numOfChannels = xml.getValue("page:tlChannels:tlChannels-num", 0);
    
    //string pageNameFromXML = xml.getValue("page:name","");
    
    for (int i=0; i<numOfChannels; i++){
        string trackName = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":name", "");
        string trackType = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":type", "");
        string rangeH = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":rangeH", "");
        string rangeL = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":rangeL", "");
        
        auto tracksPage = tracks.timelines[_track]->getPage(pageName);
        
        //If track doesnt exist and its not default -> create it.
        if(trackName != "DEFAULT" && tracksPage->getTrack(trackName)==NULL){
            
            if(trackType=="Curves"){
                //add the track
                addTLChannelToPage(_track, _page, trackName, 1, ofToFloat(rangeL), ofToFloat(rangeH));
                
            }else if(trackType=="Bangs"){
                //addTrack(trackName, BANGS);
            }else if(trackType=="Switches"){
                //addTrack(trackName, SWITCHES);
            }
        }
    }
    
    //load the tracks into the created tracks
    tracks.timelines[_track]->loadTracksFromFolder(filePath);
    

}

//-------------------------------------------------
void TimelinePanel::loadTLTrackPages(){
    for(int i=0; i< NUMBER_OF_TRACKS; i++){
        //load all the tracks
        loadTLPage(data.getTrack(), i, data.getPage());        
    }
    setPage(data.getPage());
}

//-------------------------------------------------
void TimelinePanel::loadTLAllTracks(){
    
}

#pragma mark - PLAY FUNCTIONS
//-------------------------------------------------
void TimelinePanel::setTLTrack(int _track){
    
    data.setTrack(_track);
    tracks.showSelectedTimelineTrack(_track);
    
}

//-------------------------------------------------
void TimelinePanel::setPage(int _page){
    data.setPage(_page);
    tracks.setPage(data.getTrack(), _page);
    if(data.getSelectedChannel() > -1){
        tracks.highlightFocuedTrack(data.getTrack(), data.getSelectedChannelName());
    }
    
}


//-------------------------------------------------
void TimelinePanel::setClip(int _track, int _clip){
    
    //set Clip at a specific track
    data.setClip(_clip, _track);
    
    string filePath = getFilePath(_track, _clip);
    tracks.timelines[_track]->loadTracksFromFolder(filePath);
    
}

//-------------------------------------------------
void TimelinePanel::setClip(int _clip){
    
    //set Clip on the current selected track
    data.setClip(data.getTrack(), _clip);
    
    string filePath = getFilePath(data.getTrack(), _clip);
    tracks.timelines[data.getTrack()]->loadTracksFromFolder(filePath);
}

//-------------------------------------------------
void TimelinePanel::playTLclip(int _track, int _clip){
    ofLogNotice("TRACK")    << "timePanel.play("
    << _track << "," << _clip
    << ") -- nbeat:" << data.getNBeat(_track);
    
    setMeasureLoop(_track);

    //set the data, load the file
    setClip(_track, _clip);
    
    //START IT UP
    data.setCuedToPlay(_track, true);
    
    //enable OSC OUT
    data.TL.tracks[_track].enableOscOut = true;
    
}

//-------------------------------------------------
void TimelinePanel::stopTLclip(int _clip){
    
    for(int i=0; i<NUMBER_OF_TRACKS; i++){
        if(tracks.timelines[i]->getIsPlaying()){
            tracks.timelines[i]->stop();
            data.setCuedToPlay(i, false);
        }

    //disable OSC OUT
    data.TL.tracks[i].enableOscOut = false;
        
    tracks.timelines[i]->setPercentComplete(0);
        
    setMeasureLoop(i);//resets them all.
        
    }
    
    ofLogNotice("OSC_OUT") << "DRIVE OFF";
    
}



//--------------------------------------------------------------
void TimelinePanel::setMeasureLoop(int _track){
    
    if(tracks.timelines[_track]->getIsPlaying()){
        
        cout << "setMeasureLoop(" << ofToString(_track) << ") -- isPlaying()" << endl;
        
    }
        //tracks.timelines[_track]->setPercentComplete(0);
        
        data.setNBeat(_track, -1);
        data.setLBeat(_track, -2);
        
        data.TL.tracks[_track].measureCount = 0;

}

//--------------------------------------------------------------
void TimelinePanel::setTrackMeasures(int _track, string _measures){
    
    //check if measures is int-able
    
    //set the data portion
    data.setTrackMeasures(_track, ofToInt(_measures));
    
    int d = data.getTrackDuration(_track);
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
                    //cout << "CH: " << data.TL.tracks[_track].tlPages[p].tlChannels[j].name << endl;
                    
                    int outTrack = _track+1;
                    string param = data.TL.tracks[_track].tlPages[p].tlChannels[j].name;
                    string outParam = "/"+data.TL.tracks[_track].tlPages[p].tlChannels[j].name;
                    
                    bMainApp->OSCsendToVMM(outTrack,outParam,tracks.timelines[_track]->getValue(param));
                }
            }
        }
    }
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
