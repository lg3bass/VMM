//
//  TrackButtonPanel.h
//  03_timlineLink_test

#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "Panel.h"

class TrackButtonPanel : public Panel{

    public:
        void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
        void update();
        void draw();
        void exit(){};
    
        //ofxGUI
        void setupGui();
        void adjustGui(int w, int h);
    
        vector<ofxDatGuiComponent*> clips;
        vector<ofxDatGuiComponent*> pages;
        void onButtonEvent(ofxDatGuiButtonEvent e);

        void setClip();
    
    
        //move to TrackButtonPanel.
        void setButtonClipToggle(int comp);
        void setButtonPageToggle(int comp);
    
    private:
    
        ofTrueTypeFont	verdana;
        ofColor bordCol;
        int bordWidth;

        //move to TrackButtonPanel.
        ofxDatGuiButton* clip1;
        ofxDatGuiButton* clip2;
        ofxDatGuiButton* clip3;
        ofxDatGuiButton* clip4;
        ofxDatGuiButton* clip5;
    
        ofxDatGuiButton* gRot;
        ofxDatGuiButton* lRot;
        ofxDatGuiButton* oRot;
        ofxDatGuiButton* gTrans;
        ofxDatGuiButton* lTrans;
    

};
