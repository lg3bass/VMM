//
//  HeaderPanel.cpp
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//

#include "HeaderPanel.h"
#include "ofApp.h"

ofApp* hMainApp;

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
    if(y < _h){

        
        hMainApp->myAppData.selected_panel_name = "HEADER";
        hMainApp->myAppData.txt_color = ofColor::purple;
    }

}

//-------------------------------------------------
void HeaderPanel::mouseReleased(int x, int y, int button){
    
    
    
    //ofLog() << "header released";
    //setBackgroundColor(ofColor::darkGray);

    
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

