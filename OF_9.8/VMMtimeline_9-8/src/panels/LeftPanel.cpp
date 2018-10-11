//
//  LeftPanel.cpp
//  VMMtimeline_9-8
//
//  Created by Bob White on 10/1/18.
//

#include "LeftPanel.h"
#include "ofApp.h"


ofApp* lMainApp;        //reference to ofApp()

//-------------------------------------------------
void LeftPanel::setup(int x, int y, int width, int height, ofBaseApp *appPtr){
    
    lMainApp = dynamic_cast<ofApp*>(appPtr);
    setPanelName("LEFT");
    
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
    
    small = new ofxDatGuiButton("small");
    small->setTheme(new ofxDatGuiThemeVMM);
    small->setWidth(70);
    small->setHeight(25);
    small->setPosition(x+10, y+10);
    small->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    small->setBorderVisible(TRUE);
    small->setBorder(ofColor::darkGrey, 1);
    small->onButtonEvent(this, &LeftPanel::onButtonEvent);
    
    large = new ofxDatGuiButton("large");
    large->setTheme(new ofxDatGuiThemeVMM);
    large->setWidth(70);
    large->setHeight(25);
    large->setPosition(x+10, y+50);
    large->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    large->setBorderVisible(TRUE);
    large->setBorder(ofColor::darkGrey, 1);
    large->onButtonEvent(this, &LeftPanel::onButtonEvent);
    
    // instantiate a matrix with a button for each box in our grid //
    subButtons = new ofxDatGuiMatrix("", 3, false);
    subButtons->setTheme(new ofxDatGuiThemeVMM());
    subButtons->setRadioMode(false);
    subButtons->setOpacity(.75);
    subButtons->setHeight(10.0);
    subButtons->setWidth(70.0,5.0);
    subButtons->setPosition(x+10, y+10);
    subButtons->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    subButtons->onMatrixEvent(this, &LeftPanel::onMatrixInputEvent);
    
    aText = new ofxDatGuiTextInput("attack", "10");
    aText->setTheme(new ofxDatGuiThemeVMM);
    aText->setWidth(40,0.0);
    aText->setHeight(20);
    aText->setPosition(x+10, y+50);
    aText->setLabelMargin(0);
    aText->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    aText->setBorderVisible(TRUE);
    aText->setBorder(ofColor::darkGrey, 1);
    aText->onTextInputEvent(this, &LeftPanel::onTextInputEvent);
    
    dText = new ofxDatGuiTextInput("decay", "10");
    dText->setTheme(new ofxDatGuiThemeVMM);
    dText->setWidth(40,0.0);
    dText->setHeight(20);
    dText->setPosition(x+10, y+70);
    dText->setLabelMargin(0);
    dText->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    dText->setBorderVisible(TRUE);
    dText->setBorder(ofColor::darkGrey, 1);
    dText->onTextInputEvent(this, &LeftPanel::onTextInputEvent);
    
    sText = new ofxDatGuiTextInput("sustain", "10");
    sText->setTheme(new ofxDatGuiThemeVMM);
    sText->setWidth(40,0.0);
    sText->setHeight(20);
    sText->setPosition(x+10, y+90);
    sText->setLabelMargin(0);
    sText->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    sText->setBorderVisible(TRUE);
    sText->setBorder(ofColor::darkGrey, 1);
    sText->onTextInputEvent(this, &LeftPanel::onTextInputEvent);
    
    rText = new ofxDatGuiTextInput("release", "10");
    rText->setTheme(new ofxDatGuiThemeVMM);
    rText->setWidth(40,0.0);
    rText->setHeight(20);
    rText->setPosition(x+10, y+110);
    rText->setLabelMargin(0);
    rText->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    rText->setBorderVisible(TRUE);
    rText->setBorder(ofColor::darkGrey, 1);
    rText->onTextInputEvent(this, &LeftPanel::onTextInputEvent);
    
    int leftWidth = leftMargin + clip + margin1;
    int currentTrack = lMainApp->timePanel.data.getTrack();
    
}

//-------------------------------------------------
void LeftPanel::update(){
    //small->update(true);
    //large->update(true);
    subButtons->update(true);
    
    //ADSR TEST
    aText->update();
    dText->update();
    sText->update();
    rText->update();
    
}

//-------------------------------------------------
void LeftPanel::draw(){

    drawPanelBgAndBorder(false);                     //draws the borders and background
    //ofDrawBitmapString("dropdown "+ ofToString(dropdownOpen ? "OPEN" : "CLOSED"),_w+10,_y+30);
    
    /*
    ofPushStyle();
    ofSetColor(ofColor::red);
    ofDrawRectangle(getPosition()[0]+10, getPosition()[1]+10, 20, 20);
    
    ofSetColor(ofColor::blue);
    ofDrawRectangle(getPosition()[0]+30, getPosition()[1]+10, 20, 20);
    ofPopStyle();
    */
    
    //small->draw();
    //large->draw();
    subButtons->draw();
    
    
    //ADSR TEST
    aText->draw();
    dText->draw();
    sText->draw();
    rText->draw();
}

//-------------------------------------------------
void LeftPanel::keyPressed(int key){
    
    
    
}

//-------------------------------------------------
void LeftPanel::mousePressed(int x, int y, int button){
    
    if(isWithinBounds(x, y)) {
        ofLogVerbose("LEFT") << "mousePressed() - (" << x << "," << y << ")";
        setPanelFocus(true);                        //focus THIS panel
        
    }
}

void LeftPanel::mouseReleased(int x, int y, int button){
    
    if(isWithinBounds(x, y)) {
        if(lMainApp->timePanel.getPanelFocus()){
            ofLogVerbose("LEFT") << "mouseReleased() - NOTE: mousePressed() originated from LeftPanel";
            lMainApp->timePanel.setPanelFocus(false);       //unfocus TimelinePanel
            setEnableMouseInput(true);
        } else {
            ofLogVerbose("LEFT") << "mouseReleased() - (" << x << "," << y << ")";
            setPanelFocus(false);                           //unfocus THIS panel
        }
    }
}

# pragma mark - ADSR UI //ADSR UI
//--------------------------------------------------------------
void LeftPanel::setADSR(ofVec4f ADSR){
    aText->setText(ofToString(ADSR[0]));
    dText->setText(ofToString(ADSR[1]));
    sText->setText(ofToString(ADSR[2]));
    rText->setText(ofToString(ADSR[3]));
}


//--------------------------------------------------------------
void LeftPanel::onButtonEvent(ofxDatGuiButtonEvent e){
 
    //int currentTrack = lMainApp->timePanel.data.getTrack();
    ofVec2f offset = lMainApp->timePanel.getPosition();
    
    //w = 288 (clip + notes panels in Ableton)
    ofVec2f largeOffset = ofVec2f(offset[0]+152,offset[1]);
    
    if(e.target->getName() == "small"){
        ofLogVerbose("LEFT") << "small button pressed!";
        lMainApp->timePanel.tracks.timelines[currentTrack]->setOffset(offset);
        
        //lMainApp->timePanel.
        
    } else if(e.target->getName() == "large"){
        ofLogVerbose("LEFT") << "large button pressed!";
        lMainApp->timePanel.tracks.timelines[currentTrack]->setOffset(largeOffset);
    }
    
}

//--------------------------------------------------------------
void LeftPanel::onMatrixInputEvent(ofxDatGuiMatrixEvent e){
    
    //TODO: work out the logic better.
    //ofLogVerbose("LEFT") << "matrix event! " << e.child;

    ofVec2f offset = lMainApp->timePanel.getPosition();
    
    int mod = 0;
    
    if(e.child == 0){
        mod = launch + margin1;
        if (e.enabled){
            ofLogVerbose("LEFT") << "matrix launch ON " << e.child;
            leftWidth += midiKeyboard;
            leftWidth += mod;
        } else {
            ofLogVerbose("LEFT") << "matrix launch OFF " << e.child;
            mod += midiKeyboard;
            leftWidth -= mod;
        }
    }

    if(e.child == 1){
        mod = notes + margin1;
        if (e.enabled){
            ofLogVerbose("LEFT") << "matrix notes ON " << e.child;
            leftWidth += midiKeyboard;
            leftWidth += mod;
        } else {
            ofLogVerbose("LEFT") << "matrix notes OFF " << e.child;
            mod += midiKeyboard;
            leftWidth -= mod;
        }
    }
    
    if(e.child == 2){
        mod = envelopes + margin1;
        if (e.enabled){
            ofLogVerbose("LEFT") << "matrix envelopes ON " << e.child;
            leftWidth += midiKeyboard;
            leftWidth += mod;
        } else {
            ofLogVerbose("LEFT") << "matrix envelopes OFF " << e.child;
            mod += midiKeyboard;
            leftWidth -= mod;
        }
    }
    
    lMainApp->timePanel.tracks.timelines[currentTrack]->setOffset(ofVec2f(offset[0]+leftWidth,offset[1]));
    
    int TL_WIDTH = 1080 - (rightMargin + leftWidth + 88);
    lMainApp->timePanel.tracks.timelines[currentTrack]->setWidth(TL_WIDTH);
    
}


void LeftPanel::onTextInputEvent(ofxDatGuiTextInputEvent e){
    if(e.target->getName()== "attack"){
        ofLogVerbose("LEFT") << "attack input: " << e.text;
        lMainApp->routerFrameADSR(ofToInt(e.text), 0);
    } else if(e.target->getName() == "decay"){
        ofLogVerbose("LEFT") << "decay input: " << e.text;
        lMainApp->routerFrameADSR(ofToInt(e.text), 1);
    } else if(e.target->getName() == "sustain"){
        ofLogVerbose("LEFT") << "sustain input: " << e.text;
        lMainApp->routerFrameADSR(ofToInt(e.text), 2);
    } else if(e.target->getName() == "release"){
        ofLogVerbose("LEFT") << "release input: " << e.text;
        lMainApp->routerFrameADSR(ofToInt(e.text), 3);
    }
    
    
    
}
