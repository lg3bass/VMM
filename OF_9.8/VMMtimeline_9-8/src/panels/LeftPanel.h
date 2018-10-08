//
//  LeftPanel.hpp
//  VMMtimeline_9-8
//
//  Created by Bob White on 10/1/18.
//
#pragma once

#ifndef LeftPanel_h
#define LeftPanel_h

#include "ofMain.h"
#include "Panel.h"

#include "ofxDatGui.h"
#include "ofxDatGuiThemesVMM.h"

#endif /* LeftPanel_h */

class LeftPanel : public Panel{
    
public:
    
    bool drumRack = false;
    
    int leftMargin = 15;
    int margin1 = 6;
    int rightMargin = 6;
    
    int clip = 68;
    int launch = 69;
    int notes = 145;
    int envelopes = 137;
    int midiKeyboard = 47;
    int drumKeyboard = 102;
    int sample = 231;
    
    int leftWidth;
    int currentTrack;
    ofVec2f offset;

    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void exit(){};
    
    void keyPressed(int key);
    
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    //UI test
    ofxDatGuiButton* small;
    ofxDatGuiButton* large;
    
    # pragma mark - ADSR UI //ADSR UI
    ofxDatGuiMatrix* subButtons;
    ofxDatGuiTextInput* aText;
    ofxDatGuiTextInput* dText;
    ofxDatGuiTextInput* sText;
    ofxDatGuiTextInput* rText;
    
    void setADSR(ofVec4f ADSR);
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onMatrixInputEvent(ofxDatGuiMatrixEvent e);
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    

private:
    
    
};
