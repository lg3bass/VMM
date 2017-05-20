//
//  HeaderPanel.h
//  02_timlineLink_test

#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "Panel.h"

class HeaderPanel : public Panel{
    
public:
    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void exit(){};
    
    
    //ofxGUI
    void setupGui();
    void adjustGui(int w, int h);
    
    vector<ofxDatGuiComponent*> components;
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onMatrixInputEvent(ofxDatGuiMatrixEvent e);
    
private:
    
    ofTrueTypeFont	verdana;
    ofColor bordCol;
    int bordWidth;
    
    int _frameRate;//not really used
    
    ofxDatGuiFRM* gFpsMonitor;
    ofxDatGuiTextInput* gFps;
    ofxDatGuiTextInput* gBpm;
    ofxDatGuiTextInput* gMeasures;
    
    ofxDatGuiToggle* gShowBpm;
    ofxDatGuiToggle* gSnapBpm;
    
    ofxDatGuiToggle* gSendOsc;
    ofxDatGuiTextInput* gHost;
    ofxDatGuiTextInput* gPort;
    
    ofxDatGuiMatrix* gTrack;
    
    ofxDatGuiButton* gLoad;
    ofxDatGuiButton* gSave;
    ofxDatGuiButton* gLoadAll;
    
    //move to TrackButtonPanel.
    ofxDatGuiButton* range1;
    ofxDatGuiButton* range2;
    ofxDatGuiButton* range3;
    
    //move to TrackButtonPanel.
    void setButtonClipToggle(int comp);
    

    
    
};
