//
//  HeaderPanel.cpp
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//

#include "HeaderPanel.h"
#include "ofApp.h"

ofApp* hMainApp;        //reference to ofApp()

//-------------------------------------------------
void HeaderPanel::setup(int x, int y, int width, int height, ofBaseApp *appPtr){
    
    hMainApp = dynamic_cast<ofApp*>(appPtr);
    
    _x = x;
    _y = y;
    _w = width;
    _h = height;

    //bounding box to check if mouse is within
    bounds.set(x, y, width, height);
    
    //colors
    setBackgroundColor(ofColor::darkGray);
    setBorderColor(ofColor::white);
    setBorderWidth(2);
    
    mainUI.setup(appPtr);
    
    //initially select the buttons.
    setTrack(0);
    setPage(0);
    setClip(0);
    
    
}

//-------------------------------------------------
void HeaderPanel::update(){
    
    
    mainUI.update(true);
    
}

//-------------------------------------------------
void HeaderPanel::draw(){
    
    mainUI.acceptMouseEvents = getEnableMouseInput();
    
    drawPanel();
    
    mainUI.draw();
    
    ofDrawBitmapString("headerPanel - enableMouseInput: " + ofToString(getEnableMouseInput() ? "TRUE" : "FALSE"), 1090, _y+10);
    
    //check if mouse is within.  can move this to panel.
    if(bounds.inside(ofGetMouseX(), ofGetMouseY())) {
        ofDrawBitmapString("Inside HEADER", 1090, _y+20);
    }
    
    
    if(dropdownOpen){
        ofDrawBitmapString("dropdown OPEN", 1090, _y+30);
    } else {
        ofDrawBitmapString("dropdown CLOSED", 1090, _y+30);
    }
    
    
    
}

//-------------------------------------------------
void HeaderPanel::keyPressed(int key){
    

    
}

//-------------------------------------------------
void HeaderPanel::mousePressed(int x, int y, int button){
    
    //TODO - move to Panel.h as virtual
    if(x > 0 && x < 1080 && y > 0 && y < 380 * HEADER_PANEL_HEIGHT ){
        
        ofLogNotice("HEADER") << "mousePressed() - (" << x << "," << y << ")";
        setBorderColor(ofColor::red);
        setBorderWidth(4);
        setPanelFocus(true);

    }
    
}

//-------------------------------------------------
void HeaderPanel::mouseReleased(int x, int y, int button){
    
    //TODO - Move to functions
    //dropdown exceptions
    if(mainUI.trackDropdown->getMouseDown() || mainUI.saveDropdown->getMouseDown() || mainUI.loadDropdown->getMouseDown()){
        
        if(mainUI.trackDropdown->getIsExpanded() || mainUI.saveDropdown->getIsExpanded() || mainUI.loadDropdown->getIsExpanded()){
            ofLogNotice("HEADER") << "dropdown is CLOSED";
            hMainApp->setTimePanelEnabled(true);
            dropdownOpen = false;
            
        } else {
            ofLogNotice("HEADER") << "dropdown is OPEN";
            hMainApp->setTimePanelEnabled(false);
            dropdownOpen = true;
        }
    }
    
    //TODO - move to Panel.h as virtual
    if(x > 0 && x < 1080 && y > 0 && y < 380*0.16){
            if(hMainApp->timePanel.getPanelFocus()){
                ofLogNotice("HEADER") << "mouseReleased() - STARTING FROM TIMEPANEL";
                hMainApp->timePanel.setBorderColor(ofColor::white);
                hMainApp->timePanel.setBorderWidth(2);
                hMainApp->timePanel.setPanelFocus(false);
                setEnableMouseInput(true);
            } else {
                ofLogNotice("HEADER") << "mouseReleased() - (" << x << "," << y << ")";
                setBorderColor(ofColor::white);
                setBorderWidth(2);
                setPanelFocus(false);
            }
    }
    
}

//--------------------------------------------------------------
bool HeaderPanel::getDropdownOpen(){
    return dropdownOpen;
}

//--------------------------------------------------------------
void HeaderPanel::setDropdownOpen(bool dd){
    dropdownOpen = dd;
}

//--------------------------------------------------------------
void HeaderPanel::setTrack(int _track){
    
    vector<int> pass2track;
    pass2track.push_back(_track);
    mainUI.tracks->setSelected(pass2track);
}


//--------------------------------------------------------------
void HeaderPanel::setClip(int _clip){
    
    vector<int> pass2clip;
    pass2clip.push_back(_clip);
    mainUI.clips->setSelected(pass2clip);
}

//--------------------------------------------------------------
void HeaderPanel::setPage(int _page){
    
    vector<int> pass2page;
    pass2page.push_back(_page);
    mainUI.pages->setSelected(pass2page);
}

//--------------------------------------------------------------
void HeaderPanel::setBeat(int _beat){
    mainUI.linkSlider->setValue(_beat);
}

//--------------------------------------------------------------
void HeaderPanel::setUImeasures(int _measure){
    
    string measure = ofToString(_measure);
    
    mainUI.measures->setText(measure);
}

//--------------------------------------------------------------
void HeaderPanel::toggleDrive(){
    
    mainUI.setButtonToggle(mainUI.drive);
    
}
