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
    setPanelName("HEADER");
    
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
    
    mainUI.setup(appPtr);
    
    //initially select the buttons.
    setTrackUI(0);
    setPageUI(0);
    setClipUI(0);
    
    
}

//-------------------------------------------------
void HeaderPanel::update(){
    
    mainUI.update(true);
    
}

//-------------------------------------------------
void HeaderPanel::draw(){
    
    mainUI.acceptMouseEvents = getEnableMouseInput();
    
    drawPanelBgAndBorder(false);                     //draws the borders and background
    //ofDrawBitmapString("dropdown "+ ofToString(dropdownOpen ? "OPEN" : "CLOSED"),_w+10,_y+30);
    
    mainUI.draw();
    
}

//-------------------------------------------------
void HeaderPanel::keyPressed(int key){
    

    
}

//-------------------------------------------------
void HeaderPanel::mousePressed(int x, int y, int button){
    
    if(isWithinBounds(x, y)) {
        ofLogVerbose("HEADER") << "mousePressed() - (" << x << "," << y << ")";
        setPanelFocus(true);                        //focus THIS panel
    }
}

//-------------------------------------------------
void HeaderPanel::mouseReleased(int x, int y, int button){
        
    //check if a dropdown is open. If yes, disable events on TimelinePanel.
    checkDropdownOpen();
    
    
    if(isWithinBounds(x, y)) {
        
        if(hMainApp->timePanel.getPanelFocus()){
            ofLogVerbose("HEADER") << "mouseReleased() - NOTE: mousePressed() originated from TimelinePanel";
            hMainApp->timePanel.setPanelFocus(false);       //unfocus TimelinePanel
            setEnableMouseInput(true);
        } else {
            ofLogVerbose("HEADER") << "mouseReleased() - (" << x << "," << y << ")";
            setPanelFocus(false);                           //unfocus THIS panel
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
void HeaderPanel::checkDropdownOpen(){
    
    if(mainUI.trackDropdown->getMouseDown() || mainUI.saveDropdown->getMouseDown() || mainUI.loadDropdown->getMouseDown()){
        
        if(mainUI.trackDropdown->getIsExpanded() || mainUI.saveDropdown->getIsExpanded() || mainUI.loadDropdown->getIsExpanded()){
            ofLogNotice("HEADER") << "dropdown is CLOSED";
            
            hMainApp->setTimePanelEnabled(true);                //re-enable events on the timePanel
            //dropdownOpen = false;
            setDropdownOpen(false);
            
        } else {
            ofLogNotice("HEADER") << "dropdown is OPEN";
            hMainApp->setTimePanelEnabled(false);               //disable events on the timePanel
            //dropdownOpen = true;
            setDropdownOpen(true);
        }
    }
    
}


#pragma mark - SET UI
//--------------------------------------------------------------
void HeaderPanel::setTrackUI(int _track){
    
    vector<int> pass2track;
    pass2track.push_back(_track);
    mainUI.tracks->setSelected(pass2track);
}


//--------------------------------------------------------------
void HeaderPanel::setClipUI(int _clip){
    
    vector<int> pass2clip;
    pass2clip.push_back(_clip);
    mainUI.clips->setSelected(pass2clip);
}

//--------------------------------------------------------------
void HeaderPanel::setPageUI(int _page){
    
    vector<int> pass2page;
    pass2page.push_back(_page);
    mainUI.pages->setSelected(pass2page);
}

//--------------------------------------------------------------
void HeaderPanel::setBeatUI(int _beat){
    mainUI.linkSlider->setValue(_beat);
}

//--------------------------------------------------------------
void HeaderPanel::setMeasuresUI(int _measure){

    string measure = ofToString(_measure);
    mainUI.measures->setText(measure);
}

//--------------------------------------------------------------
void HeaderPanel::setMeterUI(string _meter){    
    mainUI.meter->setText(_meter);
}

//--------------------------------------------------------------
void HeaderPanel::toggleDrive(){
    mainUI.setButtonToggle(mainUI.drive);
}
