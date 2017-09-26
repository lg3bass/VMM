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

    //colors
    setBackgroundColor(ofColor::darkGray);
    setBorderColor(ofColor::red);
    setBorderWidth(2);
    
    mainUI.setup(appPtr);
    
    //initially select the buttons.
    setTrack(0);
    setPage(0);
    setClip(0);
}

//-------------------------------------------------
void HeaderPanel::update(){
   
    mainUI.update();
    
}

//-------------------------------------------------
void HeaderPanel::draw(){
    
    drawPanel();
    
    mainUI.draw();
    
}

//-------------------------------------------------
void HeaderPanel::keyPressed(int key){
    

    
}

//-------------------------------------------------
void HeaderPanel::mousePressed(int x, int y, int button){
    
    if(x < _w && x > _x){
        if(y < _h && y > _y){
            
            cout << "within header" << endl;
        }
        
    }

    
}

//-------------------------------------------------
void HeaderPanel::mouseReleased(int x, int y, int button){
    
    //cout << "getMouseDown(): " << mainUI.trackDropdown->getMouseDown() << endl;
    
    if(mainUI.trackDropdown->getMouseDown() || mainUI.saveDropdown->getMouseDown() || mainUI.loadDropdown->getMouseDown()){
        
        if(mainUI.trackDropdown->getIsExpanded() || mainUI.saveDropdown->getIsExpanded() || mainUI.loadDropdown->getIsExpanded()){
            
            cout << "dropdown is CLOSED" << endl;
            
            hMainApp->setTimePanelEnabled(true);
            
        } else {
            
            cout << "dropdown is OPEN" << endl;
            
            hMainApp->setTimePanelEnabled(false);
        }
        
        
        
    }
    

    
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
