//
//  timelinePanel.h
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//
#pragma once

#ifndef timelinePanel_h
#define timelinePanel_h

#include "ofMain.h"
#include "Panel.h"
#include "timelineData.h"
//#include "linkModule.h"

#endif /* timelinePanel_h */

class timelinePanel : public Panel{

public:

    
    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void exit(){};
    
    void keyPressed(int key);
    void keyReleased(int key);
   
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    void drawTrackData();
    void drawPageData(int _mt);
    
    timelineData data;
    //linkModule link;
    
private:
    
    ofTrueTypeFont	verdana9;
    
    
    ofColor bordCol;
    int bordWidth;


};
