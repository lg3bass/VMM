//
//  headerUI.cpp
//  VMM_UI_design
//
//  Created by Robert White III on 6/19/17.
//
//

#include "headerUI.h"
#include "ofApp.h"

ofApp* uiMainApp;

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
    
    cout << "DD index selected: " << e.child << endl;
    add_type = e.child;
    
}

//--------------------------------------------------------------
void headerUI::onTextInputEvent(ofxDatGuiTextInputEvent e){
    
    //cout << e.target->getName() << " text: " << e.text << endl;
    
    if(e.target->getName()== "NAME"){

        add_name = e.text;
        
    } else if (e.target->getName() == "KEY"){
        
        //cout << "set the value of the key!" << endl;
        uiMainApp->setKeyVal(ofToInt(e.text));
        
    } else if (e.target->getName() == "MEASURES" || e.target->getName() == "BPM" || e.target->getName() == "FPS" || e.target->getName() == "BPM" || e.target->getName() == "LOOP" || e.target->getName() == "METER" || e.target->getName() == "BAR|BEAT|FRAME"){
        
        uiMainApp->passTextValue(e.target->getName(),e.text);       //pass up to ofApp
        
    } 
    
    
    
    
}

//--------------------------------------------------------------
void headerUI::onButtonEvent(ofxDatGuiButtonEvent e){
    
    if(e.target->getName() == "+"){
        if(add_type > 0){
            if(add_name == "<<ENTER NAME>>") {
                cout << "you must enter a name." << endl;
            } else {
                uiMainApp->addTLTrack(add_name, add_type);
                resetTrackDropdown();
            }

        } else {
            cout << "you must select a track type." << endl;
            
        }
    } else if (e.target->getName() == "-"){
        cout << "remove track pressed" << endl;
        
        uiMainApp->remTLTrack();
        
    } else if (e.target->getName() == ">"){
        cout << "increment key" << endl;
        uiMainApp->nextKey();
        
    } else if (e.target->getName() == "<"){
        cout << "decrement key" << endl;
        uiMainApp->prevKey();
        
    }
    
}

//--------------------------------------------------------------
void headerUI::resetTrackDropdown(){
    
    add_name = "<<ENTER NAME>>";
    add_type = 0;
    
    trackDropdown->select(add_type);
    trackName->setText(add_name);
    
    
}


