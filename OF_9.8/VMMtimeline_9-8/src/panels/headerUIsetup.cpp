//
//  headerUIsetup.cpp
//  -- sister file to headerUI.cpp. broke out setup, update, draw()
//  VMM_UI_design
//
//  Created by Robert White III on 6/19/17.
//
//

#include "headerUI.h"
#include "ofApp.h"

//--------------------------------------------------------------
void headerUI::setupGUI() {
    
    //section widths
    ofVec2f S1 = ofVec2f(0,0);
    ofVec2f S2 = ofVec2f(250,0);
    ofVec2f S3 = ofVec2f(450,0);
    ofVec2f S4 = ofVec2f(750,0);
    ofVec2f S5 = ofVec2f(1000,0);
    
    float matrixWidth = 250.0;
    
    // instantiate a matrix with a button for each box in our grid //
    tracks = new ofxDatGuiMatrix("TRACK", 10, true);
    tracks->setTheme(new ofxDatGuiThemeVMM());
    tracks->setRadioMode(true);
    tracks->setOpacity(.75);
    tracks->setWidth(matrixWidth, 60.0);
    tracks->setPosition(S1.x, S1.y);
    tracks->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    tracks->onMatrixEvent(this, &headerUI::onTrackMatrixInputEvent);
    

    
    float rowH = tracks->getHeight();
    
    pages = new ofxDatGuiMatrix("PAGES", 10, true);
    pages->setTheme(new ofxDatGuiThemeVMM());
    pages->setRadioMode(true);
    pages->setOpacity(.75);
    pages->setWidth(matrixWidth, 60.0);
    pages->setPosition(S1.x, rowH*1);
    pages->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    pages->onMatrixEvent(this, &headerUI::onPageMatrixInputEvent);
    
    
    clips = new ofxDatGuiMatrix("CLIP", 10, true);
    clips->setTheme(new ofxDatGuiThemeVMM());
    clips->setRadioMode(true);
    clips->setOpacity(.75);
    clips->setWidth(matrixWidth, 60.0);
    clips->setPosition(S1.x, rowH*2);
    clips->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    clips->onMatrixEvent(this, &headerUI::onClipMatrixInputEvent);
    

    
    
    
    //section S2 - width 200 (250-450)
    
    //ROW 1
    breadcrumb = new ofxDatGuiLabel("CLIP 2 > SETTINGS > MATCAP");
    breadcrumb->setTheme(new ofxDatGuiThemeVMM);
    breadcrumb->setWidth(200);
    breadcrumb->setHeight(rowH);
    breadcrumb->setPosition(S2.x, rowH*0);
    breadcrumb->setLabelMargin(10);
    breadcrumb->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    breadcrumb->setStripe(ofColor::orangeRed, 4);
    breadcrumb->setStripeVisible(TRUE);
    
    //ROW 2
    selKey = new ofxDatGuiLabel("SEL KEY");
    selKey->setTheme(new ofxDatGuiThemeVMM);
    selKey->setWidth(50);
    selKey->setHeight(rowH);
    selKey->setPosition(S2.x, rowH*1);
    selKey->setLabelMargin(10);
    selKey->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    selKey->setStripe(ofColor::orangeRed, 4);
    selKey->setStripeVisible(TRUE);
    
    selPrev = new ofxDatGuiButton("<");
    selPrev->setTheme(new ofxDatGuiThemeVMM);
    selPrev->setWidth(25);
    selPrev->setHeight(rowH);
    selPrev->setPosition(S2.x+selKey->getWidth(), rowH*1);
    selPrev->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    selPrev->setBorderVisible(TRUE);
    selPrev->setBorder(ofColor::darkGrey, 1);
    selPrev->onButtonEvent(this, &headerUI::onButtonEvent);
    
    selNext = new ofxDatGuiButton(">");
    selNext->setTheme(new ofxDatGuiThemeVMM);
    selNext->setWidth(25);
    selNext->setHeight(rowH);
    selNext->setPosition(S2.x+selKey->getWidth()+selPrev->getWidth(), rowH*1);
    selNext->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    selNext->setBorderVisible(TRUE);
    selNext->setBorder(ofColor::darkGrey, 1);
    selNext->onButtonEvent(this, &headerUI::onButtonEvent);
    
    keyVal = new ofxDatGuiTextInput("KEY", "---");
    keyVal->setTheme(new ofxDatGuiThemeVMM);
    keyVal->setWidth(50,0.0);
    keyVal->setHeight(rowH);
    keyVal->setPosition(S2.x+selKey->getWidth()+selPrev->getWidth()+selNext->getWidth(), rowH*1);
    keyVal->setLabelMargin(0);
    keyVal->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    keyVal->setBorderVisible(TRUE);
    keyVal->setBorder(ofColor::darkGrey, 1);
    keyVal->onTextInputEvent(this, &headerUI::onTextInputEvent);
    
    clamp = new ofxDatGuiButton("CLAMP");
    clamp->setTheme(new ofxDatGuiThemeVMM);
    clamp->setWidth(50);
    clamp->setHeight(rowH);
    clamp->setPosition(S2.x+selKey->getWidth()+selPrev->getWidth()+selNext->getWidth()+keyVal->getWidth(), rowH*1);
    clamp->setLabelMargin(0);
    clamp->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    clamp->setBorderVisible(TRUE);
    clamp->setBorder(ofColor::darkGrey, 1);
    
    
    //ROW 3
    saveOptions.push_back("SAVE");
    saveOptions.push_back("SAVE ALL");
    saveOptions.push_back("SAVE AS");
    saveOptions.push_back("SAVE PRESET");
    loadOptions.push_back("LOAD");
    loadOptions.push_back("LOAD ALL");
    loadOptions.push_back("LOAD PRESET");
    
    //save/load dropdowns
    saveDropdown = new ofxDatGuiDropdown("SAVE",saveOptions);
    saveDropdown->setTheme(new ofxDatGuiThemeVMM);
    saveDropdown->setWidth(100.0,60.0);
    saveDropdown->setHeight(rowH);
    saveDropdown->setPosition(S2.x, rowH*2);
    saveDropdown->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    saveDropdown->setBorderVisible(TRUE);
    saveDropdown->setBorder(ofColor::darkGrey, 1);
    
    loadDropdown = new ofxDatGuiDropdown("LOAD",loadOptions);
    loadDropdown->setTheme(new ofxDatGuiThemeVMM);
    loadDropdown->setWidth(100.0);
    loadDropdown->setHeight(rowH);
    loadDropdown->setPosition(S2.x+saveDropdown->getWidth(), rowH*2);
    loadDropdown->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    loadDropdown->setBorderVisible(TRUE);
    loadDropdown->setBorder(ofColor::darkGrey, 1);
    
    //section S3 - width 300 (450-750)
    
    //ROW 1
    measures = new ofxDatGuiTextInput("MEASURES", "8");
    measures->setTheme(new ofxDatGuiThemeVMM);
    measures->setWidth(75,50.0);
    measures->setHeight(rowH);
    measures->setPosition(S3.x, S3.y);
    measures->setLabelMargin(0);
    measures->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    measures->setBorderVisible(TRUE);
    measures->setBorder(ofColor::darkGrey, 1);
    measures->onTextInputEvent(this, &headerUI::onTextInputEvent);
    
    
    bpm = new ofxDatGuiTextInput("BPM", "120");
    bpm->setTheme(new ofxDatGuiThemeVMM);
    bpm->setWidth(75,30.0);
    bpm->setHeight(rowH);
    bpm->setPosition(S3.x+measures->getWidth(), S3.y);
    bpm->setLabelMargin(0);
    bpm->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    bpm->setBorderVisible(TRUE);
    bpm->setBorder(ofColor::darkGrey, 1);
    bpm->onTextInputEvent(this, &headerUI::onTextInputEvent);
    
    fps = new ofxDatGuiTextInput("FPS", "30");
    fps->setTheme(new ofxDatGuiThemeVMM);
    fps->setWidth(75,30.0);
    fps->setHeight(rowH);
    fps->setPosition(S3.x+measures->getWidth()+bpm->getWidth(), S3.y);
    fps->setLabelMargin(0);
    fps->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    fps->setBorderVisible(TRUE);
    fps->setBorder(ofColor::darkGrey, 1);
    fps->onTextInputEvent(this, &headerUI::onTextInputEvent);
    
    loop = new ofxDatGuiTextInput("LOOP", "30");
    loop->setTheme(new ofxDatGuiThemeVMM);
    loop->setWidth(75,30.0);
    loop->setHeight(rowH);
    loop->setPosition(S3.x+measures->getWidth()+bpm->getWidth()+fps->getWidth(), S3.y);
    loop->setLabelMargin(0);
    loop->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    loop->setBorderVisible(TRUE);
    loop->setBorder(ofColor::darkGrey, 1);
    loop->onTextInputEvent(this, &headerUI::onTextInputEvent);
    
    
    //ROW2
    clampL = new ofxDatGuiTextInput("LOW", "8");
    clampL->setTheme(new ofxDatGuiThemeVMM);
    clampL->setWidth(75,30.0);
    clampL->setHeight(rowH);
    clampL->setPosition(S3.x, rowH*1);
    clampL->setLabelMargin(0);
    clampL->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    clampL->setBorderVisible(TRUE);
    clampL->setBorder(ofColor::darkGrey, 1);
    
    clampH = new ofxDatGuiTextInput("HIGH", "120");
    clampH->setTheme(new ofxDatGuiThemeVMM);
    clampH->setWidth(75,30.0);
    clampH->setHeight(rowH);
    clampH->setPosition(S3.x+clampL->getWidth(), rowH*1);
    clampH->setLabelMargin(0);
    clampH->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    clampH->setBorderVisible(TRUE);
    clampH->setBorder(ofColor::darkGrey, 1);
    
    setIn = new ofxDatGuiTextInput("IN", "30");
    setIn->setTheme(new ofxDatGuiThemeVMM);
    setIn->setWidth(75,30.0);
    setIn->setHeight(rowH);
    setIn->setPosition(S3.x+clampL->getWidth()+clampH->getWidth(), rowH*1);
    setIn->setLabelMargin(0);
    setIn->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    setIn->setBorderVisible(TRUE);
    setIn->setBorder(ofColor::darkGrey, 1);
    
    setOut = new ofxDatGuiTextInput("OUT", "30");
    setOut->setTheme(new ofxDatGuiThemeVMM);
    setOut->setWidth(75,30.0);
    setOut->setHeight(rowH);
    setOut->setPosition(S3.x+clampL->getWidth()+clampH->getWidth()+setIn->getWidth(), rowH*1);
    setOut->setLabelMargin(0);
    setOut->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    setOut->setBorderVisible(TRUE);
    setOut->setBorder(ofColor::darkGrey, 1);
    
    //ROW3
    addTr = new ofxDatGuiButton("+");
    addTr->setTheme(new ofxDatGuiThemeVMM);
    addTr->setWidth(25);
    addTr->setHeight(rowH);
    addTr->setPosition(S3.x, rowH*2);
    addTr->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    addTr->setBorderVisible(TRUE);
    addTr->setBorder(ofColor::darkGrey, 1);
    addTr->onButtonEvent(this, &headerUI::onButtonEvent);
    
    remTr = new ofxDatGuiButton("-");
    remTr->setTheme(new ofxDatGuiThemeVMM);
    remTr->setWidth(25);
    remTr->setHeight(rowH);
    remTr->setPosition(S3.x+addTr->getWidth(), rowH*2);
    remTr->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    remTr->setBorderVisible(TRUE);
    remTr->setBorder(ofColor::darkGrey, 1);
    remTr->onButtonEvent(this, &headerUI::onButtonEvent);
    
    trackOptions.push_back("------");
    trackOptions.push_back("curves");
    trackOptions.push_back("bangs");
    trackOptions.push_back("MIDI");
    trackOptions.push_back("flags");
    trackOptions.push_back("colors");
    trackDropdown = new ofxDatGuiDropdown("TIMELINE", trackOptions);
    trackDropdown->setTheme(new ofxDatGuiThemeVMM);
    trackDropdown->setWidth(100.0,60.0);
    trackDropdown->setHeight(rowH);
    trackDropdown->setPosition(S3.x+addTr->getWidth()+remTr->getWidth(), rowH*2);
    trackDropdown->setBorderVisible(TRUE);
    trackDropdown->setBorder(ofColor::darkGrey, 1);
    trackDropdown->onDropdownEvent(this, &headerUI::onDDInputEvent);
    

    
    trackName = new ofxDatGuiTextInput("NAME", "<<ENTER NAME>>");
    trackName->setTheme(new ofxDatGuiThemeVMM);
    trackName->setWidth(150,0.0);
    trackName->setHeight(rowH);
    trackName->setPosition(S3.x+addTr->getWidth()+remTr->getWidth()+trackDropdown->getWidth(), rowH*2);
    trackName->setLabelMargin(0);
    trackName->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    trackName->setBorderVisible(TRUE);
    trackName->setBorder(ofColor::darkGrey, 1);
    trackName->onTextInputEvent(this, &headerUI::onTextInputEvent);
    
    //section S4 - width 250 (750-1000)
    
    //ROW1
    meter = new ofxDatGuiTextInput("METER", "5/4");
    meter->setTheme(new ofxDatGuiThemeVMM);
    meter->setWidth(100,50.0);
    meter->setHeight(rowH);
    meter->setPosition(S4.x, rowH*0);
    meter->setLabelMargin(0);
    meter->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    meter->setBorderVisible(TRUE);
    meter->setBorder(ofColor::darkGrey, 1);
    meter->onTextInputEvent(this, &headerUI::onTextInputEvent);
    
    barBeatFrame= new ofxDatGuiTextInput("BAR|BEAT|FRAME", "8|3|345");
    barBeatFrame->setTheme(new ofxDatGuiThemeVMM);
    barBeatFrame->setWidth(150,80.0);
    barBeatFrame->setHeight(rowH);
    barBeatFrame->setPosition(S4.x+meter->getWidth(), rowH*0);
    barBeatFrame->setLabelMargin(0);
    barBeatFrame->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    barBeatFrame->setBorderVisible(TRUE);
    barBeatFrame->setBorder(ofColor::darkGrey, 1);
    barBeatFrame->onTextInputEvent(this, &headerUI::onTextInputEvent);
    
    //ROW2
    quantize = new ofxDatGuiButton("QUANTIZE");
    quantize->setTheme(new ofxDatGuiThemeVMM);
    quantize->setWidth(50);
    quantize->setHeight(rowH);
    quantize->setPosition(S4.x, rowH*1);
    quantize->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    quantize->setBorderVisible(TRUE);
    quantize->setBorder(ofColor::darkGrey, 1);
    
    snap = new ofxDatGuiButton("SNAP");
    snap->setTheme(new ofxDatGuiThemeVMM);
    snap->setWidth(50);
    snap->setHeight(rowH);
    snap->setPosition(S4.x+quantize->getWidth(), rowH*1);
    snap->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    snap->setBorderVisible(TRUE);
    snap->setBorder(ofColor::darkGrey, 1);
    
    focus = new ofxDatGuiButton("FOCUS");
    focus->setTheme(new ofxDatGuiThemeVMM);
    focus->setWidth(50);
    focus->setHeight(rowH);
    focus->setPosition(S4.x+quantize->getWidth()+snap->getWidth(), rowH*1);
    focus->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    focus->setBorderVisible(TRUE);
    focus->setBorder(ofColor::darkGrey, 1);
    
    showAll = new ofxDatGuiButton("SHOW ALL");
    showAll->setTheme(new ofxDatGuiThemeVMM);
    showAll->setWidth(50);
    showAll->setHeight(rowH);
    showAll->setPosition(S4.x+quantize->getWidth()+snap->getWidth()+focus->getWidth(), rowH*1);
    showAll->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    showAll->setBorderVisible(TRUE);
    showAll->setBorder(ofColor::darkGrey, 1);
    
    drive = new ofxDatGuiButton("DRIVE");
    drive->setTheme(new ofxDatGuiThemeVMM);
    drive->setWidth(50);
    drive->setHeight(rowH);
    drive->setPosition(S4.x+quantize->getWidth()+snap->getWidth()+focus->getWidth()+showAll->getWidth(), rowH*1);
    drive->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    drive->setBorderVisible(TRUE);
    drive->setBorder(ofColor::darkGrey, 1);
    
    //ROW3    
    host = new ofxDatGuiTextInput("HOST","127.0.0.1");
    host->setTheme(new ofxDatGuiThemeVMM);
    host->setWidth(120,30.0);
    host->setHeight(rowH);
    host->setPosition(S4.x, rowH*2);
    host->setLabelMargin(0);
    host->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    host->setBorderVisible(TRUE);
    host->setBorder(ofColor::darkGrey, 1);
    
    
    port = new ofxDatGuiTextInput("PORT","7005");
    port->setTheme(new ofxDatGuiThemeVMM);
    port->setWidth(80,30.0);
    port->setHeight(rowH);
    port->setPosition(S4.x+host->getWidth(), rowH*2);
    port->setLabelMargin(0);
    port->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    port->setBorderVisible(TRUE);
    port->setBorder(ofColor::darkGrey, 1);
    
    osc = new ofxDatGuiButton("OSC");
    osc->setTheme(new ofxDatGuiThemeVMM);
    osc->setWidth(50);
    osc->setHeight(rowH);
    osc->setPosition(S4.x+host->getWidth()+port->getWidth(), rowH*2);
    osc->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    osc->setBorderVisible(TRUE);
    osc->setBorder(ofColor::darkGrey, 1);
    
    //section S5 - width 80 (1000-1080)
    
    linkSlider = new ofxDatGuiSlider("LINK",0.0,1.0,0.65);
    linkSlider->setTheme(new ofxDatGuiThemeVMM);
    linkSlider->setWidth(ofGetWidth()-S5.x, 0);
    linkSlider->setHeight(tracks->getHeight());
    linkSlider->setPosition(S5.x,S5.y);
    
}


//--------------------------------------------------------------
void headerUI::updateGUI(){
    
    //S1
    tracks->update();
    pages->update();
    clips->update();
    
    
    
    //S2
    breadcrumb->update();
    selKey->update();
    selPrev->update();
    selNext->update();
    keyVal->update();
    clamp->update();
    saveDropdown->update();
    loadDropdown->update();
    
    //S3
    measures->update();
    bpm->update();
    fps->update();
    loop->update();
    clampH->update();
    clampL->update();
    setIn->update();
    setOut->update();
    addTr->update();
    remTr->update();
    trackDropdown->update();
    trackName->update();
    
    
    
    //S4
    meter->update();
    barBeatFrame->update();
    
    quantize->update();
    snap->update();
    focus->update();
    showAll->update();
    drive->update();
    
    host->update();
    port->update();
    osc->update();
    
    //S5
    linkSlider->update();
    
    
    
}

//--------------------------------------------------------------
void headerUI::drawGUI(){
    
    //S1
    tracks->draw();
    pages->draw();
    clips->draw();
    
    
    
    //S2
    breadcrumb->draw();
    selKey->draw();
    selPrev->draw();
    selNext->draw();
    keyVal->draw();
    clamp->draw();
    saveDropdown->draw();
    loadDropdown->draw();
    
    //S3
    measures->draw();           //row1
    bpm->draw();
    fps->draw();
    loop->draw();
    clampL->draw();             //row2
    clampH->draw();
    setIn->draw();
    setOut->draw();
    addTr->draw();              //row3
    remTr->draw();
    trackDropdown->draw();
    trackName->draw();
    
    //S4
    meter->draw();              //row1
    barBeatFrame->draw();
    quantize->draw();           //row2
    snap->draw();
    focus->draw();
    showAll->draw();
    drive->draw();
    host->draw();               //row3
    port->draw();
    osc->draw();
    
    //S5
    linkSlider->draw();
    
}



