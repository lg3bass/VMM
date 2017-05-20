//
//  HeaderPanel.cpp
//  02_timlineLink_test

#include "HeaderPanel.h"
#include "ofApp.h"

ofApp* hMainApp;

//-------------------------------------------------
void HeaderPanel::setup(int x, int y, int width, int height, ofBaseApp* appPtr){
    
    _x = x;
    _y = y;
    _w = width;
    _h = height;
    
    _frameRate = INIT_FPS;
    
    hMainApp = dynamic_cast<ofApp*>(appPtr);
    
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
void HeaderPanel::update(){
    
    for(int i=0; i<components.size(); i++) components[i]->update();
    
}

//-------------------------------------------------
void HeaderPanel::draw(){
    
    for(int i=0; i<components.size(); i++) components[i]->draw();
    
    //Draw a rect around the panel .  dont really need this.
    ofSetColor(_bckgColor);
    //ofNoFill();
    ofDrawRectangle(_x, _y, _w, _h);
    
}

//-------------------------------------------------
void HeaderPanel::setupGui(){
    ofxDatGuiComponent* component;
    
    //COL 1
    //FRAMERATE MONITOR
    gFpsMonitor = new ofxDatGuiFRM(0.5f);//updates ever 0.5 secs.
    component = gFpsMonitor;
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    components.push_back(component);
    
    //SET FPS
    gFps = new ofxDatGuiTextInput("SET FPS", ofToString(INIT_FPS));
    component = gFps;
    component->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    component->onTextInputEvent(this, &HeaderPanel::onTextInputEvent);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    component->setLabelMargin(20.0);
    components.push_back(component);
    
    //MEASURES
    gMeasures = new ofxDatGuiTextInput("MEASURES", "8");
    component = gMeasures;
    component->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    component->onTextInputEvent(this, &HeaderPanel::onTextInputEvent);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    component->setLabelMargin(20.0);
    components.push_back(component);

    //BPM
    gBpm = new ofxDatGuiTextInput("BPM", "120");
    component = gBpm;
    component->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    component->onTextInputEvent(this, &HeaderPanel::onTextInputEvent);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    component->setLabelMargin(20.0);
    components.push_back(component);
    
    
    //TRACK BUTTON
    gTrack = new ofxDatGuiMatrix("tracks",5,true);
    gTrack->setRadioMode(true);
    component = gTrack;
    component->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    component->onMatrixEvent(this, &HeaderPanel::onMatrixInputEvent);
    component->setLabelMargin(10.0);
    components.push_back(component);

    gLoad = new ofxDatGuiButton("LOAD");
    component = gLoad;
    component->onButtonEvent(this, &HeaderPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    components.push_back(component);
    
    gSave = new ofxDatGuiButton("SAVE");
    component = gSave;
    component->onButtonEvent(this, &HeaderPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    components.push_back(component);
    
    gLoadAll = new ofxDatGuiButton("LOAD ALL");
    component = gLoadAll;
    component->onButtonEvent(this, &HeaderPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    components.push_back(component);

    //set range test
    range1 = new ofxDatGuiButton("range1");
    component = range1;
    component->onButtonEvent(this, &HeaderPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    components.push_back(component);
    
    range2 = new ofxDatGuiButton("range2");
    component = range2;
    component->onButtonEvent(this, &HeaderPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    components.push_back(component);
    
    range3 = new ofxDatGuiButton("range3");
    component = range3;
    component->onButtonEvent(this, &HeaderPanel::onButtonEvent);
    component->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    component->setBorder(bordCol, bordWidth);
    component->setBorderVisible(TRUE);
    component->setStripeVisible(false);
    components.push_back(component);
    
    //---------
    //-:SET POSITION, WIDTH AND HEIGHT OF COMPONENTS
    adjustGui(_w, _h);
    
}

//-------------------------------------------------
void HeaderPanel::adjustGui(int w, int h){
    
    int guiCompWidth = _w / 6; //divide the header into 6 sections W
    int guiCompHeight = _h / 4; //divide the header into 4 section H
    
    if(components.size()==0){
        ofLogError()<<"Cant resize MainPanel, components size = 0";
        return;
    }
    
    ofxDatGuiComponent* component;
    
    //FRAMERATE MONITOR
    component = components[0];
    component->setPosition(_x, _y+ guiCompHeight*0);
    component->setWidth(guiCompWidth/2, 0.65);
    component->setHeight(guiCompHeight);
    
    //SET FPS
    component = components[1];
    component->setPosition(_x+guiCompWidth*0.5, _y+ guiCompHeight*0);
    component->setWidth(guiCompWidth/2, 0.7);
    component->setHeight(guiCompHeight);
    
    //MEASURES
    component = components[2];
    component->setPosition(_x, _y + guiCompHeight * 1);
    component->setWidth(guiCompWidth, 0.9);
    component->setHeight(guiCompHeight);
    
    //BPM
    component = components[3];
    component->setPosition(_x, _y + guiCompHeight * 2);
    component->setWidth(guiCompWidth, 0.9);
    component->setHeight(guiCompHeight);
    
    //Matrix
    component = components[4];
    component->setPosition(_x + guiCompWidth, _y + guiCompHeight * 0);
    component->setWidth(guiCompWidth*1.5, 0.22);
    component->setHeight(guiCompHeight);
    component->setIndex(0);
    
    //LOAD
    component = components[5];
    component->setPosition(_x + guiCompWidth, _y + guiCompHeight * 1);
    component->setWidth(guiCompWidth*0.5, 0.22);
    component->setHeight(guiCompHeight);
    
    
    //SAVE
    component = components[6];
    component->setPosition(_x + guiCompWidth + guiCompWidth*0.5, _y + guiCompHeight * 1);
    component->setWidth(guiCompWidth*0.5, 0.22);
    component->setHeight(guiCompHeight);
    
    //SAVE
    component = components[7];
    component->setPosition(_x + guiCompWidth + guiCompWidth*1.0, _y + guiCompHeight * 1);
    component->setWidth(guiCompWidth*0.5, 0.22);
    component->setHeight(guiCompHeight);
    
    //RANGE BUTTONS FOR TESTING
    //range1
    component = components[8];
    component->setPosition(_x + guiCompWidth, _y + guiCompHeight * 2);
    component->setWidth(guiCompWidth*0.5, 0.22);
    component->setHeight(guiCompHeight);
    
    
    //SAVE
    component = components[9];
    component->setPosition(_x + guiCompWidth + guiCompWidth*0.5, _y + guiCompHeight * 2);
    component->setWidth(guiCompWidth*0.5, 0.22);
    component->setHeight(guiCompHeight);
    
    //SAVE
    component = components[10];
    component->setPosition(_x + guiCompWidth + guiCompWidth*1.0, _y + guiCompHeight * 2);
    component->setWidth(guiCompWidth*0.5, 0.22);
    component->setHeight(guiCompHeight);
    

    
}

//-------------------------------------------------
#pragma mark - Listeners
//-------------------------------------------------
void HeaderPanel::onButtonEvent(ofxDatGuiButtonEvent e)
{
    ofLogNotice("GUI") << "MainPanel-onButtonEvent: " << e.target->getLabel() << "::" << e.enabled;
    
    //get the selected track
    int t = hMainApp->getSelectedTrack();
    
    ofxDatGuiMatrix* component;
    
    
    if(e.target->getLabel()=="LOAD"){
        hMainApp->timePanel.loadCurrent();
        
    } else if(e.target->getLabel()=="SAVE"){
        hMainApp->timePanel.saveCurrent();
        
    } else if(e.target->getLabel()=="LOAD ALL"){
        
        hMainApp->timePanel.loadAllTracks();
        
        //set gui toggles
        hMainApp->buttonPanel.setButtonClipToggle(0);
        hMainApp->buttonPanel.setButtonPageToggle(0);
        
        component = (ofxDatGuiMatrix *)components[4];
        
        for (int i=0;i<5;i++){
            component->getChildAt(i)->setSelected(false);
        }
        
        component->getChildAt(0)->setSelected(true);
    } else if(e.target->getLabel()=="RANGE1"){
        
        hMainApp->timePanel.alterTimeline(1);
        
        
        cout << "range 1" << endl;
    } else if(e.target->getLabel()=="RANGE2"){
        
        cout << "range 2" << endl;
    } else if(e.target->getLabel()=="RANGE3"){
        
        cout << "range 3" << endl;
    }
    
    
    
}


//--------------------------------------------------------------
void HeaderPanel::onTextInputEvent(ofxDatGuiTextInputEvent e){

    if (e.target->getLabel()=="MEASURES"){
        try{
            hMainApp->timePanel.setMeasuresAtTempo(std::stoi (e.text), hMainApp->getGlobalTempo());
        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument: " << ia.what() << '\n';
        }
    } else if (e.target->getLabel()=="BPM"){
        try{
            hMainApp->setGlobalTempo(std::stof (e.text));
        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument: " << ia.what() << '\n';
        }
    }
}

//--------------------------------------------------------------
void HeaderPanel::onSliderEvent(ofxDatGuiSliderEvent e){

/*
    
    ofLogNotice("KEY") << "onSliderEvent: " << e.value << "::" << e.scale;
    if (e.target->getLabel()=="VOLUME"){
        if (mMainAppPtr->timePanel.audioTrack != NULL)
            mMainAppPtr->timePanel.audioTrack->setVolume(e.value);
    }
 
*/
}

//--------------------------------------------------------------
void HeaderPanel::onMatrixInputEvent(ofxDatGuiMatrixEvent e){
    
    hMainApp->setSelectedTrack(e.child);
    
    hMainApp->displayTrack(e.child);
    
    //hMainApp->showMeCurrentTrackClipPage(e.child);
    
    hMainApp->setClipAndPageButtons(e.child);
    
}


//--------------------------------------------------------------
void HeaderPanel::setButtonClipToggle(int comp){
    
    for(int i=7; i<10;i++){
        if(i==comp){
            //set to gray
            components[i]->setBackgroundColor(ofColor(100,100,100));
        } else {
            //set back to black
            components[i]->setBackgroundColor(ofColor(0,0,0));
        }
    }
}
