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
        ofAddListener(tracks.timelines[i]->events().trackGainedFocus, this, &timelinePanel::actOnFocus);
        ofAddListener(tracks.timelines[i]->events().trackLostFocus, this, &timelinePanel::actOnLossFocus);
    }

}

//-------------------------------------------------
void timelinePanel::update(){
    
}

//-------------------------------------------------
void timelinePanel::draw(){
    
    tracks.draw();
    
    drawPanel();
    
    if(showTrackData){
        drawTrackData();
    }
    
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
                    
                    cout << "F3 pressed" << endl;
                    testFunction(data.getTrack(), data.getSelectedChannelName());
                    

                    
                    break;
                case 260:
                    
                    cout << "F4 pressed" << endl;
                    
                    break;
                case 261:
                    
                    cout << "F5 pressed" << endl;
                    
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

//-------------------------------------------------
void timelinePanel::drawTrackData(){

    float ml = 60;
    float mt = 10;

    float h_unit = 80;
    float v_unit = 15;

    
    verdana9.drawString("MM: "+ofToString(data.TL.measures), h_unit*0+ml, _y+mt+v_unit*0);
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

//-------------------------------------------------
void timelinePanel::addTLChannel(string _name, int _type){
    //adds the track in the data
    data.addtlTrack(data.getTrack(),data.getPage(), _name, _type);
    
    //add the track on the timeline
    tracks.addTLTrack(data.getTrack(),data.getPage(),_name, _type);

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

//-------------------------------------------------
void timelinePanel::saveTLPage(int _track, int _page, int _clip){
    //save the keyframe data from each track
    //NOTE: In order to specifically target a single page
    //      You will need to add an additional function
    //      e.g. ofxTimeline::savePageTracksToFolder(int page, string folderPath)
    
    if(data.getNumOfChannelsOnPage(_page)>0){
        cout << "Saving channel on page " << ofToString(_page) << endl;
        
        string filePath = TRACK_DIR "_" + ofToString(_track) + "/" CLIP_DIR "_" + ofToString(_clip) + "/";
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
    string filePath = TRACK_DIR "_" + ofToString(_track) + "/" CLIP_DIR "_" + ofToString(_clip) + "/";
    
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
            
            if(trackType=="Curves"){
                //add the track
                tracks.addTLTrack(_track, pageName, trackName, 1);
                //update the data node
                data.addtlTrack(_track, pageName, trackName, 1);
                
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



void timelinePanel::testFunction(int _track, string _channelName){
    
    //auto mytrack = tracks.timelines[data.getTrack()]->getTrack("GLOBAL ROTATE X");
    ofxTLKeyframes* mytrack = (ofxTLKeyframes*)tracks.timelines[_track]->getTrack(_channelName);
    
    cout << "How many keys are selected: " << mytrack->getSelectedItemCount() << endl;
    
    cout << "The value of the second keyframe is: " << ofToString(mytrack->getKeyframes()[1]->value) << endl;
    
    mytrack->getKeyframes()[0]->value = 0.5;
    
}
