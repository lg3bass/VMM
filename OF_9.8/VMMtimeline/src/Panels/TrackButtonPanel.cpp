//
//  TrackButtonPanel.cpp
//  03_timlineLink_test

#include "TrackButtonPanel.h"
#include "ofApp.h"

ofApp* tbMainApp;

//-------------------------------------------------
void TrackButtonPanel::setup(int x, int y, int width, int height, ofBaseApp* appPtr){

    _x = x;
    _y = y;
    _w = width;
    _h = height;

    tbMainApp = dynamic_cast<ofApp*>(appPtr);
    
    //colors
    _bckgColor = ofColor(ofColor::aqua);
    setBackgroundColor(_bckgColor);
    bordCol = ofColor::grey;
    bordWidth = 1;
    
    //set up the GUI
    setupGui();
    
    //fonts for text display
    ofTrueTypeFont::setGlobalDpi(72);
    verdana.load("gui_assets/fonts/verdana.ttf", 12, true, true);
    verdana.setLineHeight(13.0f);
    verdana.setLetterSpacing(1.037);
}

//-------------------------------------------------
void TrackButtonPanel::update(){
    
    for(int i=0; i<clips.size(); i++) clips[i]->update();
    for(int i=0; i<pages.size(); i++) pages[i]->update();
    
}

//-------------------------------------------------
void TrackButtonPanel::draw(){
    
    for(int i=0; i<clips.size(); i++) clips[i]->draw();
    for(int i=0; i<pages.size(); i++) pages[i]->draw();
    
    //draw a bounding box around the panel just to show.
    ofSetColor(ofColor(40));
    ofNoFill();
    ofDrawRectangle(_x, _y, _w, _h);
}

//-------------------------------------------------
void TrackButtonPanel::setupGui(){
    ofxDatGuiComponent* component;
    
    //CLIPS

    clip1 = new ofxDatGuiButton("CLIP1");
    component = clip1;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    clips.push_back(component);

    clip2 = new ofxDatGuiButton("CLIP2");
    component = clip2;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    clips.push_back(component);
    
    clip3 = new ofxDatGuiButton("CLIP3");
    component = clip3;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    clips.push_back(component);
    
    clip4 = new ofxDatGuiButton("CLIP4");
    component = clip4;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    clips.push_back(component);

    clip5 = new ofxDatGuiButton("CLIP5");
    component = clip5;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    clips.push_back(component);
    
    //PAGES
    gRot = new ofxDatGuiButton("GR");
    component = gRot;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    pages.push_back(component);
    
    lRot = new ofxDatGuiButton("LR");
    component = lRot;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    pages.push_back(component);
    
    oRot = new ofxDatGuiButton("OR");
    component = oRot;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    pages.push_back(component);
 
    gTrans = new ofxDatGuiButton("GT");
    component = gTrans;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    pages.push_back(component);
    
    lTrans = new ofxDatGuiButton("LT");
    component = lTrans;
    component->onButtonEvent(this, &TrackButtonPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    pages.push_back(component);
    
    
    //---------
    //-:SET POSITION, WIDTH AND HEIGHT OF COMPONENTS
    adjustGui(_w, _h);

    
}

//-------------------------------------------------
void TrackButtonPanel::adjustGui(int w, int h){

    int guiCompWidth = _w; //single column
    int guiCompHeight = _h / 30; //divide the header into 20 slots Vertically
    
    if(clips.size()==0){
        ofLogError()<<"Cant resize MainPanel, components size = 0";
        return;
    }
    
    if(pages.size()==0){
        ofLogError()<<"Cant resize MainPanel, components size = 0";
        return;
    }
    
    ofxDatGuiComponent* component;
    
    //clip1
    component = clips[0];
    component->setPosition(_x, _y + guiCompHeight * 0);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);
    
    //clip2
    component = clips[1];
    component->setPosition(_x, _y + guiCompHeight * 1);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);
    
    //clip3
    component = clips[2];
    component->setPosition(_x, _y + guiCompHeight * 2);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);
   
    //clip4
    component = clips[3];
    component->setPosition(_x, _y + guiCompHeight * 3);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);
    
    //clip5
    component = clips[4];
    component->setPosition(_x, _y + guiCompHeight * 4);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);

    
    
    //g Rot
    component = pages[0];
    component->setPosition(_x, _y + guiCompHeight * 7);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);
    
    //l Rot
    component = pages[1];
    component->setPosition(_x, _y + guiCompHeight * 8);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);
    
    //o Rot
    component = pages[2];
    component->setPosition(_x, _y + guiCompHeight * 9);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);
    
    //g Trans
    component = pages[3];
    component->setPosition(_x, _y + guiCompHeight * 10);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);
    
    //l Trans
    component = pages[4];
    component->setPosition(_x, _y + guiCompHeight * 11);
    component->setWidth(guiCompWidth, 0.22);
    component->setHeight(guiCompHeight);
}

//-------------------------------------------------
#pragma mark - Listeners
//-------------------------------------------------
void TrackButtonPanel::onButtonEvent(ofxDatGuiButtonEvent e) {
    
    //get the selected track
    int t = tbMainApp->getSelectedTrack();
    int c = tbMainApp->getSelectedClip(t);
    int p = tbMainApp->getCurrentPage(t);
    
    
    //cout << "buttonPanel.onButtonEvent() [" << ofToString(t) << "," << ofToString(t) << "," << ofToString(p) << "]" << endl;
    
    //clips
    if (e.target->getLabel()=="CLIP1"){
        
        //component 0
        setButtonClipToggle(0);
        tbMainApp->setSelectedClip(t,0);
        //tbMainApp->timePanel.loadCurrent();
        
    } else if(e.target->getLabel()=="CLIP2"){
        
        //component 1
        setButtonClipToggle(1);
        tbMainApp->setSelectedClip(t,1);
        //tbMainApp->timePanel.loadCurrent();
        
        
    } else if(e.target->getLabel()=="CLIP3"){
        
        //component 2
        setButtonClipToggle(2);
        tbMainApp->setSelectedClip(t,2);
        //tbMainApp->timePanel.loadCurrent();
        
    } else if(e.target->getLabel()=="CLIP4"){
        
        //component 3
        setButtonClipToggle(3);
        tbMainApp->setSelectedClip(t,3);
        //tbMainApp->timePanel.loadCurrent();
        
        
    } else if(e.target->getLabel()=="CLIP5"){
        
        //component 4
        setButtonClipToggle(4);
        tbMainApp->setSelectedClip(t,4);
        //tbMainApp->timePanel.loadCurrent();
        
    }

    //pages
    if (e.target->getLabel()=="GR"){
        
        //component 0
        setButtonPageToggle(0);
        tbMainApp->setCurrentPage(t,0);
        
    } else if(e.target->getLabel()=="LR"){
        
        //component 1
        setButtonPageToggle(1);
        tbMainApp->setCurrentPage(t,1);
        
    } else if(e.target->getLabel()=="OR"){
        
        //component 2
        setButtonPageToggle(2);
        tbMainApp->setCurrentPage(t,2);
        
    } else if(e.target->getLabel()=="GT"){
        
        //component 2
        setButtonPageToggle(3);
        tbMainApp->setCurrentPage(t,3);
        
    } else if(e.target->getLabel()=="LT"){
        
        //component 2
        setButtonPageToggle(4);
        tbMainApp->setCurrentPage(t,4);
        
    }

    
}

//--------------------------------------------------------------
void TrackButtonPanel::setButtonClipToggle(int comp){
    
    for(int i=0; i<clips.size();i++){
        if(i==comp){
            //set to gray
            clips[i]->setBackgroundColor(ofColor(100,100,100));
        } else {
            //set back to black
            clips[i]->setBackgroundColor(ofColor(0,0,0));
        }
    }
    

}

//--------------------------------------------------------------
void TrackButtonPanel::setButtonPageToggle(int comp){

    for(int i=0; i<pages.size();i++){
        if(i==comp){
            //set to gray
            pages[i]->setBackgroundColor(ofColor(100,100,100));
        } else {
            //set back to black
            pages[i]->setBackgroundColor(ofColor(0,0,0));
        }
    }
    
    
}

