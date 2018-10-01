//
//  LeftPanel.cpp
//  VMMtimeline_9-8
//
//  Created by Bob White on 10/1/18.
//

#include "LeftPanel.h"
#include "ofApp.h"


ofApp* lMainApp;        //reference to ofApp()

//-------------------------------------------------
void LeftPanel::setup(int x, int y, int width, int height, ofBaseApp *appPtr){
    
    lMainApp = dynamic_cast<ofApp*>(appPtr);
    setPanelName("LEFT");
    
    _x = x;
    _y = y;
    _w = width;
    _h = height;
    panelBoundingBox = ofRectangle(x, y, width, height);
    
    //custom border colors
    //setBackgroundColor(ofColor::darkGray);
    //setBorderColor(ofColor::white);
    //setBorderColorHighligh(ofColor::orangeRed);
    //setBorderWidth(2);
    
    small = new ofxDatGuiButton("small");
    small->setTheme(new ofxDatGuiThemeVMM);
    small->setWidth(70);
    small->setHeight(25);
    small->setPosition(x+10, y+10);
    small->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    small->setBorderVisible(TRUE);
    small->setBorder(ofColor::darkGrey, 1);
    small->onButtonEvent(this, &LeftPanel::onButtonEvent);
    
    large = new ofxDatGuiButton("large");
    large->setTheme(new ofxDatGuiThemeVMM);
    large->setWidth(70);
    large->setHeight(25);
    large->setPosition(x+10, y+50);
    large->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    large->setBorderVisible(TRUE);
    large->setBorder(ofColor::darkGrey, 1);
    large->onButtonEvent(this, &LeftPanel::onButtonEvent);
    
}

//-------------------------------------------------
void LeftPanel::update(){
    small->update(true);
    large->update(true);
    
}

//-------------------------------------------------
void LeftPanel::draw(){

    drawPanelBgAndBorder(false);                     //draws the borders and background
    //ofDrawBitmapString("dropdown "+ ofToString(dropdownOpen ? "OPEN" : "CLOSED"),_w+10,_y+30);
    
    /*
    ofPushStyle();
    ofSetColor(ofColor::red);
    ofDrawRectangle(getPosition()[0]+10, getPosition()[1]+10, 20, 20);
    
    ofSetColor(ofColor::blue);
    ofDrawRectangle(getPosition()[0]+30, getPosition()[1]+10, 20, 20);
    ofPopStyle();
    */
    
    small->draw();
    large->draw();
}

//-------------------------------------------------
void LeftPanel::keyPressed(int key){
    
    
    
}

//-------------------------------------------------
void LeftPanel::mousePressed(int x, int y, int button){
    
    if(isWithinBounds(x, y)) {
        ofLogVerbose("LEFT") << "mousePressed() - (" << x << "," << y << ")";
        setPanelFocus(true);                        //focus THIS panel
        
        
        
    }
}

//-------------------------------------------------
void LeftPanel::mouseReleased(int x, int y, int button){
    
    if(isWithinBounds(x, y)) {
        
        if(lMainApp->timePanel.getPanelFocus()){
            ofLogVerbose("LEFT") << "mouseReleased() - NOTE: mousePressed() originated from LeftPanel";
            lMainApp->timePanel.setPanelFocus(false);       //unfocus TimelinePanel
            setEnableMouseInput(true);
        } else {
            ofLogVerbose("LEFT") << "mouseReleased() - (" << x << "," << y << ")";
            setPanelFocus(false);                           //unfocus THIS panel
        }
    }
}



//--------------------------------------------------------------
void LeftPanel::onButtonEvent(ofxDatGuiButtonEvent e){
 
    int currentTrack = lMainApp->timePanel.data.getTrack();
    ofVec2f offset = lMainApp->timePanel.getPosition();
    ofVec2f largeOffset = ofVec2f(offset[0]+150,offset[1]);
    
    
    if(e.target->getName() == "small"){
        ofLogVerbose("LEFT") << "small button pressed!";
        lMainApp->timePanel.tracks.timelines[currentTrack]->setOffset(offset);
        
    } else if(e.target->getName() == "large"){
        ofLogVerbose("LEFT") << "large button pressed!";
        lMainApp->timePanel.tracks.timelines[currentTrack]->setOffset(largeOffset);
    }
    
}
