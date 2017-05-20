#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    //setup a custom window.
    ofGLFWWindowSettings settings;
    
    
    settings.width = 1024;
    settings.height = 768;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    shared_ptr<ofApp> mainApp(new ofApp());
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();

}
