//
//  HeaderPanel.h
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//
#pragma once

#ifndef HeaderPanel_h
#define HeaderPanel_h

#include "ofMain.h"
#include "Panel.h"
#include "headerUI.h"

#endif /* HeaderPanel_h */




class HeaderPanel : public Panel{
    
public:

    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void exit(){};
    
    void keyPressed(int key);
    
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    
    
    bool getDropdownOpen();
    void setDropdownOpen(bool dd);
    void checkDropdownOpen();

#pragma mark - SET UI
    void setTrackUI(int _track);
    void setClipUI(int _clip);
    void setPageUI(int _page);
    
    void setBeatUI(int _beat);
    
    void setMeasuresUI(int _measure);
    void setBpmUI(int _bpm);
    void setFpsUI(int _fps);
    void setFramesUI(int _frames);
    void setMeterUI(string _meter);
    void setBarsBeatFrame(int bars, int beat, int frame);
    

    void toggleDrive();
    
#pragma mark - OBJ & VAR
    headerUI mainUI;
    
private:
    
    bool dropdownOpen = false;
    ofTrueTypeFont	verdana;

    
    
    
    
};
