//
//  timelinePanel.cpp
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//

#include "timelinePanel.h"
#include "ofApp.h"

#define TRACK_DIR "TRACK"
#define CLIP_DIR "CLIP"

ofApp* bMainApp;        //reference to ofApp()

//-------------------------------------------------
void timelinePanel::setup(int x, int y, int width, int height, ofBaseApp* appPtr){
    
    bMainApp = dynamic_cast<ofApp*>(appPtr);
    
    _x = x;
    _y = y;
    _w = width;
    _h = height;
    
    tracks.init(x,y,width,height);
    

    //colors
    setBackgroundColor(ofColor::darkGray);
    setBorderColor(ofColor::mediumOrchid);
    setBorderWidth(2);
    
    verdana9.load("verdana.ttf", 7, true, true);
    
    showTrackData = false;
    
    //add listener to "ofxTLEvents::trackGainedFocus"
    for(int i=0; i<NUMBER_OF_TRACKS; i++){
        
        //add listeners
        ofAddListener(tracks.timelines[i]->events().trackGainedFocus, this, &timelinePanel::actOnFocus);
        ofAddListener(tracks.timelines[i]->events().trackLostFocus, this, &timelinePanel::actOnLossFocus);
        
        //reset/setup track metadata.
        setMeasureLoop(i);
    }
}

//-------------------------------------------------
void timelinePanel::update(){
    //tracks.update();
    
    for(int i=0;i<NUMBER_OF_TRACKS;i++){
        
        data.setNBeat(i, bMainApp->AL.nbeat);
        
        if(data.getCuedToPlay(i)){
            
            //copy over nbeat to tracks so each track has it own.
            //data.TL.tracks[i].nbeat = bMainApp->AL.nbeat;
            //data.setNBeat(i, bMainApp->AL.nbeat);
            
            
            //OLD bMainApp->AL.isDownbeat()  -- moving checks to individual tracks
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
        sendOSCfromTimeline(i, "setGlobalRotX");
    }
}

//-------------------------------------------------
void timelinePanel::draw(){
    
    tracks.draw();
    
    //draws a border around the panel.
    drawPanel();
    
    if(showTrackData){
        drawTrackData();
    }
}

//-------------------------------------------------
void timelinePanel::runTimelines(int _track){
    
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
void timelinePanel::keyPressed(int key){
    
    //cout << "KEY: " << ofToString(key) << endl;
    
    if(key == 60 || key == 100){                                // D Key
        
        toggleDrawTrackData();
        
    }
    
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
                    
                    cout << "Left Apple Pressed" << endl;
                    
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
}//func

//-------------------------------------------------
void timelinePanel::keyReleased(int key){
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
                    cout << "Left Apple Released" << endl;
//                    if(key == 60 || key == 100){                               //D key
//                        showTrackData = false;
//                    }
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
void timelinePanel::mousePressed(int x, int y, int button){
    if(y > _y && y < _y+_h){

        
        bMainApp->myAppData.selected_panel_name = "BODY";
        bMainApp->myAppData.txt_color = ofColor::darkKhaki;
    }
    
    tracks.mousePressed(x, y, button);
}

//-------------------------------------------------
void timelinePanel::mouseReleased(int x, int y, int button){

    //ofLog() << "body released";
    //setBackgroundColor(ofColor::darkGray);
}

#pragma mark - DEBUG/STATS
//-------------------------------------------------
void timelinePanel::drawTrackData(){

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
    verdana9.drawString("CHANNEL", 0, _y+mt+v_unit*7);
   
    for(int i=0; i<NUMBER_OF_TRACKS;i++){

        verdana9.drawString(ofToString(i+1), i*h_unit+ml, _y+mt+v_unit*3);
        verdana9.drawString(ofToString(data.getPage(i)+1), i*h_unit+ml, _y+mt+v_unit*4);
        verdana9.drawString(ofToString(data.getClip(i)+1), i*h_unit+ml, _y+mt+v_unit*5);
        verdana9.drawString(data.getCuedToPlay(i) ? "true" : "false", i*h_unit+ml, _y+mt+v_unit*6);
        
    }
    
    //only draw if a channel is selected
    if(data.getSelectedChannel() > -1 ){
        drawPageData(_y+mt+v_unit*3);                   //show the page tracks and keys
    }
}

//-------------------------------------------------
void timelinePanel::drawPageData(int _mt){
    
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
void timelinePanel::toggleDrawTrackData(){
    
    showTrackData = !showTrackData;
    //tracks.displayTimelines(!showTrackData);
    
    //showHideFlag = _showTimeline;
    
    if(showTrackData){
        tracks.timelines[data.getTrack()]->hide();
    } else {
        tracks.timelines[data.getTrack()]->show();
    }
}

#pragma mark - SELECT CHANNELS
//-------------------------------------------------
void timelinePanel::actOnFocus(ofxTLTrackEventArgs & args){
    
    cout << "timelinePanel::Gained Focus: " << args.name << endl;
    data.setSelectedChannel(args.name);
}

//-------------------------------------------------
void timelinePanel::actOnLossFocus(ofxTLTrackEventArgs & args){
    
    cout << "timelinePanel::Loss Focus: " << args.name << endl;
    //data.setSelectedChannel(-1);
}

#pragma mark - ADD/REMOVE
//-------------------------------------------------
void timelinePanel::addTLChannel(string _name, int _type){
    //adds the track in the data
    data.addtlTrack(data.getTrack(),data.getPage(), _name, _type);
    
    //add the track on the timeline
    //tracks.addTLTrack(data.getTrack(),data.getPage(),_name, _type);
    tracks.addTLTrack(data.getTrack(),data.getPageName(),_name, _type);

}

//-------------------------------------------------
void timelinePanel::remTLChannel(){
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
string timelinePanel::getFilePath(int _track, int _clip){
    return TRACK_DIR "_" + ofToString(_track) + "/" CLIP_DIR "_" + ofToString(_clip) + "/";
}

//-------------------------------------------------
void timelinePanel::saveTLPage(int _track, int _page, int _clip){
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
            savedSettings.popTag();
        }
        savedSettings.popTag();
        
        savedSettings.saveFile(filenamePanel);
        
        
    } else {
        cout << "There are not enough channels on the page " << ofToString(_page) << " to save anything." << endl;
        
    }

}

//-------------------------------------------------
void timelinePanel::saveTLTrackPages(){
    //how many pages?
    
    //loop through the pages and save all the channels on each page.
    for (int i=0; i<NUMBER_OF_TRACKS; i++){
        saveTLPage(data.getTrack(), i, data.getClip());
    }

}

//-------------------------------------------------
void timelinePanel::saveTLAllTracks(){
    
}

//-------------------------------------------------
void timelinePanel::loadTLPage(int _track, int _page, int _clip){

    //----------------------------------
    //-:Load Xml file
    string filePath = getFilePath(_track,_clip);
    
    //string pageName = data.getPageName();
    string pageName = data.getPageName(_page);
    
    string filenamePanel = filePath + pageName + "_settings.xml";
    ofxXmlSettings xml;
    
    if( xml.loadFile(filenamePanel) ){
        ofLogVerbose()<<"timelinePanel::loadTLPage - "<< filenamePanel <<" loaded.";
    }else{
        ofLogError()<<  "timelinePanel::loadTLPage - unable to load " << filenamePanel ;
        return;
    }
    
    //----------------------------------
    //-:Create tracks from loaded settings.
    int tracksNum = xml.getValue("page:tlChannels:tlChannels-num", 0);
    string pageNameFromXML = xml.getValue("page:name","");
    for (int i=0; i<tracksNum; i++){
        string trackName = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":name", "");
        string trackType = xml.getValue("page:tlChannels:channel-" + ofToString(i) +":type", "");
        
        auto tracksPage = tracks.timelines[_track]->getPage(pageName);
        
        //If track doesnt exist and its not default -> create it.
        if(trackName != "DEFAULT" &&
           tracksPage->getTrack(trackName)==NULL){
            
            //auto t = tracksPage->getTracks();
            
            if(trackType=="Curves"){
                //add the track
                tracks.addTLTrack(_track, _page, trackName, 1);
                //update the data node
                data.addtlTrack(_track, _page, trackName, 1);
                
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
void timelinePanel::loadTLTrackPages(){
    for(int i=0; i< NUMBER_OF_TRACKS; i++){
        //load all the tracks
        loadTLPage(data.getTrack(), i, data.getPage());        
    }
}

//-------------------------------------------------
void timelinePanel::loadTLAllTracks(){
    
}

#pragma mark - PLAY FUNCTIONS

//-------------------------------------------------
void timelinePanel::setClip(int _clip, int _track){
    
    //set Clip at a specific track
    data.setClip(_clip, _track);
    
    string filePath = getFilePath(_track, _clip);
    tracks.timelines[_track]->loadTracksFromFolder(filePath);
    
}

//-------------------------------------------------
void timelinePanel::setClip(int _clip){
    
    //set Clip at a specific track
    data.setClip(_clip, data.getTrack());
    
    string filePath = getFilePath(data.getTrack(), _clip);
    tracks.timelines[data.getTrack()]->loadTracksFromFolder(filePath);
}

//-------------------------------------------------
void timelinePanel::playTLclip(int _track, int _clip){
    ofLogNotice("TRACK")    << "timePanel.play("
    << _track << "," << _clip
    << ") -- nbeat:" << data.getNBeat(_track);
    
    setMeasureLoop(_track);

    //set the data, load the file
    setClip(_clip,_track);
    
    //START IT UP
    data.setCuedToPlay(_track, true);
    
    //enable OSC OUT
    data.TL.tracks[_track].enableOscOut = true;
    
}

//-------------------------------------------------
void timelinePanel::stopTLclip(int _clip){
    
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
void timelinePanel::setMeasureLoop(int _track){
    
    if(tracks.timelines[_track]->getIsPlaying()){
        
        cout << "setMeasureLoop(" << ofToString(_track) << ") -- isPlaying()" << endl;
        
    }
        //tracks.timelines[_track]->setPercentComplete(0);
        
        data.setNBeat(_track, -1);
        data.setLBeat(_track, -2);
        
        data.TL.tracks[_track].measureCount = 0;

}

//--------------------------------------------------------------
void timelinePanel::setTrackMeasures(int _track, string _measures){
    
    //check if measures is int-able
    
    //set the data portion
    data.setTrackMeasures(_track, ofToInt(_measures));
    
    int d = data.getTrackDuration(_track);
    tracks.timelines[_track]->setOutPointAtFrame(d);
    tracks.timelines[_track]->setDurationInFrames(d);
    
    
}


#pragma mark - OSC
//--------------------------------------------------------------
void timelinePanel::sendOSCfromTimeline(int _track, string _param){

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
    
    
    //VMM SPECIFIC DATA OUT
    //            bMainApp->OSCsendToVMM(i+1,"/setGlobalRotX",tracks.timelines[i]->getValue("GLOBAL ROTATE X"));
    //            bMainApp->OSCsendToVMM(i+1,"/setGlobalTransX",tracks.timelines[i]->getValue("GLOBAL TRANSLATE X"));
    //            bMainApp->OSCsendToVMM(i+1,"/setGlobalTransY",tracks.timelines[i]->getValue("GLOBAL TRANSLATE Y"));
    
    //            bMainApp->OSCsendToVMM(i+1,"/setLocalRotX",tracks.timelines[i]->getValue("L Rotate X"));
    //            bMainApp->OSCsendToVMM(i+1,"/setLocalRotY",tracks.timelines[i]->getValue("L Rotate Y"));
    //            //bMainApp->OSCsendToVMM(i,"/setLocalRotZ",tracks.timelines[i]->getValue("L Rotate Z"));
    //
    //            bMainApp->OSCsendToVMM(i+1,"/setObjRotX",tracks.timelines[i]->getValue("O Rotate X"));
    //            bMainApp->OSCsendToVMM(i+1,"/setObjRotY",tracks.timelines[i]->getValue("O Rotate Y"));
    //            bMainApp->OSCsendToVMM(i+1,"/setObjlRotZ",tracks.timelines[i]->getValue("O Rotate Z"));
    //
    //            bMainApp->OSCsendToVMM(i+1,"/setGlobalTransX",tracks.timelines[i]->getValue("G Translate X"));
    //            bMainApp->OSCsendToVMM(i+1,"/setGlobalTransY",tracks.timelines[i]->getValue("G Translate Y"));
    //            bMainApp->OSCsendToVMM(i+1,"/setGlobalTransZ",tracks.timelines[i]->getValue("G Translate Z"));
    //
    //            bMainApp->OSCsendToVMM(i+1,"/setLocalTransX",tracks.timelines[i]->getValue("L Translate X"));
    //            bMainApp->OSCsendToVMM(i+1,"/setLocalTransY",tracks.timelines[i]->getValue("L Translate Y"));
    //            bMainApp->OSCsendToVMM(i+1,"/setLocalTransZ",tracks.timelines[i]->getValue("L Translate Z"));
    
}

//-------------------------------------------------
//TESTS
#pragma mark - TESTS
//=================================================
void timelinePanel::testKeyframeFunction(int _track, string _channelName){
    //test on how to get at keyframe data in a track
    
    //auto mytrack = tracks.timelines[data.getTrack()]->getTrack("GLOBAL ROTATE X");
    ofxTLKeyframes* mytrack = (ofxTLKeyframes*)tracks.timelines[_track]->getTrack(_channelName);
    
    cout << "How many keys are selected: " << mytrack->getSelectedItemCount() << endl;
    
    cout << "The value of the second keyframe is: " << ofToString(mytrack->getKeyframes()[1]->value) << endl;
    
    mytrack->getKeyframes()[0]->value = 0.5;
    
}
