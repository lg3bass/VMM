#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofSetFrameRate(60);//experiment
    
    //LOGGING
    //http://openframeworks.cc/documentation/utils/ofLog.html
    ofSetLogLevel("jsonData", OF_LOG_ERROR);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("OSC",OF_LOG_SILENT);//DEFAULT: OF_LOG_VERBOSE
    ofSetLogLevel("matcap",OF_LOG_SILENT);//DEFAULT: OF_LOG_ERROR
    ofSetLogLevel("ofxUI",OF_LOG_SILENT);//DEFAULT: OF_LOG_SILENT
    ofSetLogLevel("objloader", OF_LOG_SILENT);//DEFAULT: OF_LOG_NOTICE
    
    
    //SYPHON
    //----------------------------------------------------------
    ofSetWindowTitle("VMM 10");
    mainOutputSyphonServer.setName("Screen Output");
    mClient.setup();
    
    mClient.setApplicationName("Simple Server");
    mClient.setServerName("");
    //----------------------------------------------------------
    //END SYPHON
    
    //OSC
    //----------------------------------------------------------
    // listen on the given port
    ofLogNotice("OSC") << "listening for osc messages on port " << PORT;
	receiver.setup(PORT);
    
    
    ofSetVerticalSync(true);
    ofDisableArbTex();
    
    guiTabBar = new ofxUITabBar();
    guiTabBar->setColorBack(ofColor(128,100));
    
    ofAddListener(guiTabBar->newGUIEvent,this,&ofApp::guiTabEvent);
    
    //1. Find out how many obj sequences there are in the data/obj folder
    appFileLoader.setup();
    
    //2. Setup empty tracks
    tracks.reserve(50);//TIP: http://arturocastro.net/blog/2011/10/28/stl::vector/
    for(int t=0; t<NUM_TRACKS;t++){
        tracks.push_back(vboMeshObj());
    }
    
    //3. setup the tracks
    for(int t=1; t<NUM_TRACKS;t++){
        tracks[t].setup(t);
        //tracks[t].setup(appFileLoader.externalObjFiles[t]);  //OLD METHOD - TBD
    
    }
    
    
    //Setup GLOBAL ofGui
    parameters.setName("settings");
    parameters.add(tracks[1].parameters);
    parameters.add(tracks[2].parameters);
    parameters.add(tracks[3].parameters);
    parameters.add(tracks[4].parameters);
    parameters.add(tracks[5].parameters);
    parameters.add(tracks[6].parameters);
    parameters.add(tracks[7].parameters);
    parameters.add(tracks[8].parameters);
    parameters.add(tracks[9].parameters);
    parameters.add(tracks[10].parameters);
    
    
    
    //for some reason. the gui.setup command is throwing warning in ofMath.cpp:89
    //uncomment if you need to debug.
    //gui.setup(parameters);
    gui.minimizeAll();
    minimized = true;
    gui.setPosition(900.0, 100.0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(modkey){
        cam.disableMouseInput();
    } else if (!modkey){
        cam.enableMouseInput();
    }
    
    for(int t=1; t<NUM_TRACKS;t++){
        //update all the tracks
        tracks[t].update();
        
    }
    
    //process ALL incoming OSC
    OSChandler();
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle("fps: "+ofToString(ofGetFrameRate())+" - "+ofToString(ofGetWidth())+","+ofToString(ofGetHeight())+"easyCam:"+ofToString(modkey));

    ofDrawBitmapString("SELECTED TRACK: "+ofToString(selectedTrack), 1200,10);
    
    
    
    
    //SYPHON
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //=================================================
    
    //NO SYPHON (turned off to test Syphon)
    //ofBackgroundGradient(ofColor::white, ofColor::gray);
    ofEnableDepthTest();
    
    cam.begin();
    
    for(int t=1; t<NUM_TRACKS;t++){
        //draw all the tracks
        tracks[t].draw();
        
    }
    
    cam.end();

    
    //SYPHON
    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();
    //=======================================
    

    
    //drawLights();// <-- NOT SURE I NEED THIS WITH MATCAP, disabled 10/22/15
    
    //Need this.
    ofDisableDepthTest();
    
    //draw the native ofGui (floating menu)
    //----------------------------------------
    //gui.draw();
    
    ofSetColor(255,255,255);
    ofDrawBitmapString("SELECTED: "+ofToString(selectedTrack), 1100,10);
}

//--------------------------------------------------------------
void ofApp::exit()
{
    //will load an xml per gui
    //guiTabBar->saveSettings("settings/", "tab-");
    
    for(vector<ofxUICanvas *>::iterator it = guis.begin(); it != guis.end(); ++it)
    {
        ofxUICanvas *g = *it;
        delete g;
    }
    delete guiTabBar;

    for(int t=1; t<NUM_TRACKS;t++){
        //clean up at the end
        tracks[t].exit();
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key & OF_KEY_MODIFIER){
        if(key >= OF_KEY_F1 && key <= OF_KEY_F12){
            
        }else{
            
            switch(key){
                case OF_KEY_LEFT_SUPER:
                    cout << "Left Apple Pressed" << endl;
                    modkey = true;
                    break;
                case OF_KEY_RIGHT_SUPER:
                    cout << "Right Apple Pressed" << endl;
                    modkey = true;
                    break;
                case OF_KEY_CONTROL:
                    cout << "Control Pressed" << endl;
                    ctrlKey = true;
                    break;
                case OF_KEY_RIGHT_ALT:
                    cout << "Right Alt/Opt Pressed" << endl;
                    cout << "track:" << ofToString(selectedTrack) << endl;
                    rAltKey = true;
                    tracks[selectedTrack].KeyboardLaunch(1, 60, 11, tracks[selectedTrack].params.instancePlayingId, true);

                    break;
                case OF_KEY_RIGHT_SHIFT:
                    cout << "Right Shift Pressed" << endl;
                    cout << "track:" << ofToString(selectedTrack) << endl;
                    rShiftKey = true;
                    tracks[selectedTrack].KeyboardLaunch(2, 62, 11, tracks[selectedTrack].params.instancePlayingId, true);
                    break;
                case OF_KEY_LEFT_ALT:
                    cout << "Left Alt/Opt Pressed" << endl;
                    lAltKey = true;
                    break;
                    
            }
        }
    } else {
        
        //keyboard launch to test
        
        int keyIndex = 0;
        //formatted like this so I don have to write over and over again.
        if(key == '1'){keyIndex = 1;}
        if(key == '2'){keyIndex = 2;}
        if(key == '3'){keyIndex = 3;}
        if(key == '4'){keyIndex = 4;}
        if(key == '5'){keyIndex = 5;}
        if(key == '6'){keyIndex = 6;}
        if(key == '7'){keyIndex = 7;}
        if(key == '8'){keyIndex = 8;}
        if(key == '9'){keyIndex = 9;}
        if(key == '0'){keyIndex = 10;}
        
        
        if(keyIndex > 0){
            //PLAY A SECTION OF THE ANIMATION WHEN A NUMBER KEY IS PRESSED [0-9]
            ofLogNotice("OSC") << "KeyboardLaunch: " << "track:" << ofToString(keyIndex);
            
            tracks[keyIndex].keyPressed(key);//pass the key pressed value
            
            tracks[keyIndex].KeyboardLaunch(1, 60, 11, tracks[keyIndex].params.instancePlayingId, false);
            
            //OLD-TBD
            //int VMMnoteID = ofToInt(ofToString(1) + ofToString(60));
            //tracks[keyIndex].noteOn(tracks[keyIndex].params.instancePlayingId, VMMnoteID, 60, 127, 500);
            //tracks[keyIndex].play(tracks[keyIndex].params.instancePlayingId, VMMnoteID, tracks[keyIndex].params.testSpeed, 11);
            //tracks[keyIndex].KeyboardLaunch(11, tracks[keyIndex].params.instancePlayingId);
            
            
            if(modkey){
                //randLocalPosition(<lowRand>,<highRand>,<durration>,<delay>);
                
            }
            if(ctrlKey){
                tracks[keyIndex].clear();
                
            }
        }//end if keyIndex


    }
    
    
    
    
    
    
    switch (key)
    {
        case 'g':
        {
            guiTabBar->toggleVisible();
        }
            break;
        default:
            break;
    }
    
    if(key == ' '){
        //example: go to the center of the boxes.
        //cam.setPosition(myObjSeq.vboMeshSequence1[14].getCentroid());
        
    }
    
    if(key=='s'){
//        settings.serialize(parameters);
//        settings.save("settings.xml");
        
        guiTabBar->saveSettings("settings/", "tab-");
        
    }
    if(key=='l'){
//        settings.load("settings.xml");
//        settings.deserialize(parameters);
        //save an xml per gui.
        guiTabBar->loadSettings("settings/", "tab-");
    }
    
    if(key=='m'){
        if(minimized){
            
            gui.maximizeAll();
            minimized = false;
        } else {
            gui.minimizeAll();
            minimized = true;
        }
        
    }
    

    

    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key & OF_KEY_MODIFIER){
        if(key >= OF_KEY_F1 && key <= OF_KEY_F12){
            
        }else{
            
            switch(key){
                case OF_KEY_LEFT_SUPER:
                    cout << "Left Apple Released" << endl;
                    modkey = false;
                    break;
                case OF_KEY_RIGHT_SUPER:
                    cout << "Right Apple Released" << endl;
                    modkey = false;
                    break;
                case OF_KEY_CONTROL:
                    cout << "Control Released" << endl;
                    ctrlKey = false;
                    break;
                case OF_KEY_RIGHT_ALT:
                    cout << "Right Alt/Opt Released" << endl;
                    rAltKey = false;
                    //tracks[selectedTrack].KeyboardLaunch(1, 60, 11, tracks[selectedTrack].params.instancePlayingId, true);
                    tracks[selectedTrack].noteOff(160, 500);
                    break;
                case OF_KEY_RIGHT_SHIFT:
                    cout << "Right Shift Released" << endl;
                    rShiftKey = false;
                    tracks[selectedTrack].noteOff(262, 500);
                    break;
                case OF_KEY_LEFT_ALT:
                    cout << "Left Alt/Opt Released" << endl;
                    lAltKey = false;
                    break;
                
            }
        }
    } else {

        
        int keyIndex = 0;
        //formatted like this so I don have to write over and over again.
        if(key == '1'){keyIndex = 1;}
        if(key == '2'){keyIndex = 2;}
        if(key == '3'){keyIndex = 3;}
        if(key == '4'){keyIndex = 4;}
        if(key == '5'){keyIndex = 5;}
        if(key == '6'){keyIndex = 6;}
        if(key == '7'){keyIndex = 7;}
        if(key == '8'){keyIndex = 8;}
        if(key == '9'){keyIndex = 9;}
        if(key == '0'){keyIndex = 10;}
        
        
        if(keyIndex > 0){
            tracks[keyIndex].keyReleased(key);//pass the key pressed value
            tracks[keyIndex].noteOff(keyIndex, 1000);
        }//end if keyIndex
        
        
    }//end if
    
    

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    //matCap.loadImage(dragInfo.files[0]);
    //matCap.update();
}

//--------------------------------------------------------------
void ofApp::drawLights(){
    //NOTE: Make sure this after the cam.
    //      Otherwise rotating the cam will
    //      move the lights too.
    
    
    //ofLight light0;
    ofColor ambientColor(200.0f);
    ofColor diffuseColor(130.0f);
    ofColor specularColor(25.0f);
    light0.setPosition(ofGetWidth(), ofGetHeight()/2, 500);
    light0.setAmbientColor(ambientColor);
    light0.setDiffuseColor(diffuseColor);
    light0.setSpecularColor(specularColor);
    light0.setPointLight();
    light0.enable();
    
}

//--------------------------------------------------------------
void ofApp::guiTabEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    string canvasParent = e.widget->getCanvasParent()->getName();

    //if you want to set the highlighted item.
    e.widget->setColorFill(ofColor::yellow);
    
    selectedTrack = currentSelectedTrack(name);
    
    //cout << "selected track: " << ofToString(selectedTrack) << endl;

}


//--------------------------------------------------------------
int ofApp::currentSelectedTrack(string _name){
    
    //get the number from the name.
    string justNumber = _name.substr(5);
    int trackNumber = ofToInt(justNumber);
    
    //set the track
    tracks[trackNumber].params.isSelected = !tracks[trackNumber].params.isSelected;
    
    for(int i=1; i<trackNumber;i++){
        tracks[i].params.isSelected = false;
    }
    for(int j=NUM_TRACKS; j>trackNumber;j--){
        tracks[j].params.isSelected = false;
    }
    
    
    return trackNumber;
}



//--------------------------------------------------------------
void ofApp::OSChandler()
{
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        router.processOSCmessage(m, tracks, NUM_TRACKS);

    }//end while
}
