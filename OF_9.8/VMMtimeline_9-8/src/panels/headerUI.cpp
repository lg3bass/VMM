//
//  headerUI.cpp
//  VMM_UI_design
//
//  Created by Robert White III on 6/19/17.
//
//

#include "headerUI.h"
#include "ofApp.h"

ofApp* uiMainApp;       //reference to ofApp()

//--------------------------------------------------------------
void headerUI::setup(ofBaseApp* appPtr){

    uiMainApp = dynamic_cast<ofApp*>(appPtr);
    setupGUI();

}

//--------------------------------------------------------------
void headerUI::update(){

    updateGUI();
    
}

//--------------------------------------------------------------
void headerUI::draw(){

    drawGUI();
    
}


//EVENTS
//--------------------------------------------------------------
void headerUI::onTrackMatrixInputEvent(ofxDatGuiMatrixEvent e){
    
    uiMainApp->setControllerData(e.target->getName(), e.child);
    resetTrackDropdown();
    
}

//--------------------------------------------------------------
void headerUI::onPageMatrixInputEvent(ofxDatGuiMatrixEvent e){
    
    uiMainApp->setControllerData(e.target->getName(), e.child);
    cout << "onPageMatrixInputEvent" << endl;
}

//--------------------------------------------------------------
void headerUI::onClipMatrixInputEvent(ofxDatGuiMatrixEvent e){
    
    uiMainApp->setControllerData(e.target->getName(), e.child);
    cout << "onClipMatrixInputEvent" << endl;
}

//--------------------------------------------------------------
void headerUI::onDDInputEvent(ofxDatGuiDropdownEvent e){
    
    cout << "headerUI::onDDInputEvent " << e.target->getName() << endl;
    
    if(e.target->getName() == "TIMELINE"){
        newTrack.type = e.child;
        cout << "TIMELINE dropdown index: " << e.child << endl;
    }
    
    if(e.target->getName() == "SAVE"){
        switch (e.child) {
            case 0:
                //SAVE PAGE
                uiMainApp->saveTLPage();
                break;
            case 1:
                //SAVE TRACK
                uiMainApp->saveTLTrackPages();
                break;
            case 2:
                //SAVE ALL
                uiMainApp->saveTLAllTracks();
                break;
            default:
                break;
        }
    }
    
    if(e.target->getName() == "LOAD") {
        switch (e.child) {
            case 0:
                //LOAD PAGE
                uiMainApp->loadTLPage();
                break;
            case 1:
                //LOAD TRACK
                uiMainApp->loadTLTrackPages();
                break;
            case 2:
                //LOAD ALL
                uiMainApp->loadTLAllTracks();
                break;
            default:
                break;
        }
    }
    
    //allow the timeline to recieve mouse input.
    uiMainApp->setTimePanelEnabled(true);
    
}

//--------------------------------------------------------------
void headerUI::onTextInputEvent(ofxDatGuiTextInputEvent e){
    
    if(e.target->getName()== "NAME"){
        newTrack.name = e.text;
        
    } else if (e.target->getName() == "KEY"){
        //cout << "set the value of the key!" << endl;
        uiMainApp->setKeyVal(ofToInt(e.text));
        
    } else if (e.target->getName() == "MEASURES" || e.target->getName() == "BPM" ||
               e.target->getName() == "FPS" || e.target->getName() == "BPM" ||
               e.target->getName() == "LOOP" || e.target->getName() == "METER" ||
               e.target->getName() == "BAR|BEAT|FRAME" || e.target->getName() == "LOW" ||
               e.target->getName() == "HIGH"){
        uiMainApp->passTextValue(e.target->getName(),e.text);       //pass up to ofApp
        
    } 
    
}

//--------------------------------------------------------------
void headerUI::onButtonEvent(ofxDatGuiButtonEvent e){
    
    if(e.target->getName() == "+"){
        if(newTrack.type > 0){
            if(newTrack.name == "<<ENTER NAME>>") {
                cout << "you must enter a name." << endl;
            } else {
                //add a channel to the current selected track.
                uiMainApp->addChannel(newTrack.name, newTrack.type);
                resetTrackDropdown();
            }
        } else {
            cout << "you must select a track type." << endl;
        }
        
    } else if (e.target->getName() == "-"){
        cout << "remove track pressed" << endl;
        uiMainApp->remChannel();
    
    } else if (e.target->getName() == ">"){
        cout << "increment key" << endl;
        uiMainApp->nextKey();
        
    } else if (e.target->getName() == "<"){
        cout << "decrement key" << endl;
        uiMainApp->prevKey();
        
    } else if (e.target->getName() == "DRIVE"){
        
        uiMainApp->enableOscOut();
    }
    
}

//--------------------------------------------------------------
void headerUI::resetTrackDropdown(){
    
    newTrack.name = "<<ENTER NAME>>";
    newTrack.type = 0;
    trackDropdown->select(newTrack.type);
    trackName->setText(newTrack.name);
    
}

//--------------------------------------------------------------
void headerUI::setButtonToggle(ofxDatGuiButton *_button){
    
    driveBtn = !driveBtn;
    
    if(driveBtn){
        _button->setBackgroundColor(ofColor(255,0,0));
        cout << "drive on" << endl;
    } else {
        _button->setBackgroundColor(ofColor(255,255,255));
        cout << "drive off" << endl;
        
    }
    
}

