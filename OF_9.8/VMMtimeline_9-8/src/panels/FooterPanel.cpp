//
//  FooterPanel.cpp
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//

#include "FooterPanel.h"
#include "ofApp.h"

ofApp* fMainApp;

//-------------------------------------------------
void FooterPanel::setup(int x, int y, int width, int height, ofBaseApp* appPtr){
    
    fMainApp = dynamic_cast<ofApp*>(appPtr);
    
    _x = x;
    _y = y;
    _w = width;
    _h = height;
    
    //colors
    setBackgroundColor(ofColor::darkGray);
    setBorderColor(ofColor::teal);
    setBorderWidth(2);

    
}

//-------------------------------------------------
void FooterPanel::update(){
    
    
}

//-------------------------------------------------
void FooterPanel::draw(){
    
    drawPanel();
    
}

//-------------------------------------------------
void FooterPanel::keyPressed(int key){
    

    
}

//-------------------------------------------------
void FooterPanel::mousePressed(int x, int y, int button){
    if(y > _y && y < ofGetHeight()){

        
        fMainApp->myAppData.selected_panel_name = "FOOTER";
        fMainApp->myAppData.txt_color = ofColor::green;
    }
    
    
}

//-------------------------------------------------
void FooterPanel::mouseReleased(int x, int y, int button){
   
    //ofLog() << "footer released";
    //setBackgroundColor(ofColor::darkGray);

    
}

//-------------------------------------------------
