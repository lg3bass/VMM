#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetLogLevel("OSC",OF_LOG_VERBOSE);
    
    ofSetVerticalSync(true);
    
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
    mouseX = 0;
    mouseY = 0;
    mouseButtonState = "";

    
    
    unsigned delay = 2000;
    unsigned duration = 4000;
    tweenback.setParameters(1,easingback,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenbounce.setParameters(2,easingbounce,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweencirc.setParameters(3,easingcirc,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweencubic.setParameters(4,easingcubic,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenelastic.setParameters(5,easingelastic,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenexpo.setParameters(6,easingexpo,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenlinear.setParameters(7,easinglinear,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenquad.setParameters(8,easingquad,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenquart.setParameters(9,easingquart,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenquint.setParameters(10,easingquint,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweensine.setParameters(10,easingsine,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    
    // if you setup different tweens to control several parameters,
    // they don't end exactly at the same time
    // by adding values you get only 1 tween that controls several parameters
    // totally synchronized
    multitween.setParameters(easingquart,ofxTween::easeInOut,0,ofGetWidth()-100,duration,delay);
    multitween.addValue(0,ofGetWidth()-120);
    multitween.addValue(0,ofGetWidth()-140);
    multitween.addValue(0,ofGetWidth()-160);
    multitween.addValue(0,ofGetWidth()-180);
    multitween.addValue(0,ofGetWidth()-200);
    multitween.start(); //dont forget to call start to sync all the tweens
    
    ofBackground(255,255,255);
    ofSetColor(0,0,0);
    ofNoFill();

}

//--------------------------------------------------------------
void ofApp::update(){
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        
        int VMMnoteID = 0;
        
        
        
        // check for mouse moved message
        if(m.getAddress() == "/mouse/position"){
            // both the arguments are int32's
            mouseX = m.getArgAsInt32(0);
            mouseY = m.getArgAsInt32(1);
        }
        if (m.getAddress() == "/noteOn"){
            cout << "----------------------------------------------------------------" << endl;

            VMMnoteID = ofToInt(ofToString(m.getArgAsInt32(2)) + ofToString(m.getArgAsInt32(4)));
            
            ofLogVerbose("OSC") << "-------->" << m.getAddress() <<
            " [track:" << m.getArgAsInt32(0) <<
            ", buffer:" << m.getArgAsInt32(1) <<
            ", string:" << m.getArgAsInt32(2) <<
            ", noteId:" << m.getArgAsInt32(3) <<
            ", midiNote:" << m.getArgAsInt32(4) <<
            ", velocity:" << m.getArgAsInt32(5) <<
            ", durration(last):" << m.getArgAsInt32(6) <<
            ", delta:" << m.getArgAsInt32(7) <<
            ", noteOn|Off:" << m.getArgAsInt32(8) <<
            "]";
            
            string msg_string;
            msg_string = "----------------------------------------------------------------\r";
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 10.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
            
            
            msg_string = m.getAddress();
            msg_string += "VMMnoteID: "+ofToString(VMMnoteID);
            msg_string += " [track:"+ofToString(m.getArgAsInt32(0));
            msg_string += ", buffer:"+ofToString(m.getArgAsInt32(1));
            msg_string += ", string:"+ofToString(m.getArgAsInt32(2));
            msg_string += ", noteId:"+ofToString(m.getArgAsInt32(3));
            msg_string += ", midiNote:"+ofToString(m.getArgAsInt32(4));
            msg_string += ", velocity:"+ofToString(m.getArgAsInt32(5));
            msg_string += ", durration(last):"+ofToString(m.getArgAsInt32(6));
            msg_string += ", delta:"+ofToString(m.getArgAsInt32(7));
            msg_string += ", noteOn|Off:"+ofToString(m.getArgAsInt32(8))+"]";
            
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 10.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
            
            
        } else if(m.getAddress() == "/play") {
            
            VMMnoteID = ofToInt(ofToString(m.getArgAsInt32(2)) + ofToString(m.getArgAsInt32(4)));
            
            ofLogVerbose("OSC") << ">>>>---->" << m.getAddress() <<
            " [track:" << m.getArgAsInt32(0) <<
            ", buffer:" << m.getArgAsInt32(1) <<
            ", string:" << m.getArgAsInt32(2) <<
            ", noteId:" << m.getArgAsInt32(3) <<
            ", midiNote:" << m.getArgAsInt32(4) <<
            ", cue:" << m.getArgAsInt32(5) <<
            ", duration:" << m.getArgAsInt32(6) <<
            ", tween:" << m.getArgAsInt32(7) <<
            "]";
            
            string msg_string;
            msg_string = m.getAddress();
            msg_string += "VMMnoteID: "+ofToString(VMMnoteID);
            msg_string += " [track:"+ofToString(m.getArgAsInt32(0));
            msg_string += ", buffer:"+ofToString(m.getArgAsInt32(1));
            msg_string += ", string:"+ofToString(m.getArgAsInt32(2));
            msg_string += ", noteId:"+ofToString(m.getArgAsInt32(3));
            msg_string += ", midiNote:"+ofToString(m.getArgAsInt32(4));
            msg_string += ", cue:"+ofToString(m.getArgAsInt32(5));
            msg_string += ", duration:"+ofToString(m.getArgAsInt32(6));
            msg_string += ", tween:"+ofToString(m.getArgAsInt32(6))+"]";
            
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 10.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
            
            //Launch from OSC on durration
            OSClaunch(m.getArgAsInt32(6));
            
        } else if (m.getAddress() == "/noteOff"){
            
            VMMnoteID = ofToInt(ofToString(m.getArgAsInt32(1)) + ofToString(m.getArgAsInt32(3)));
            
            ofLogVerbose("OSC") << "-------->" << m.getAddress() <<
            " [track:" << m.getArgAsInt32(0) <<
            ", string:" << m.getArgAsInt32(1) <<
            ", noteId:" << m.getArgAsInt32(2) <<
            ", midiNote:" << m.getArgAsInt32(3) <<
            ", velocity:" << m.getArgAsInt32(4) <<
            ", durration(last):" << m.getArgAsInt32(5) <<
            ", delta:" << m.getArgAsInt32(6) <<
            ", note On|Off:" << m.getArgAsInt32(7) <<
            "]";

            string msg_string;
            msg_string = m.getAddress();
            msg_string += "VMMnoteID: "+ofToString(VMMnoteID);
            msg_string += " [track:"+ofToString(m.getArgAsInt32(0));
            msg_string += ", string:"+ofToString(m.getArgAsInt32(1));
            msg_string += ", noteId:"+ofToString(m.getArgAsInt32(2));
            msg_string += ", midiNote:"+ofToString(m.getArgAsInt32(3));
            msg_string += ", velocity:"+ofToString(m.getArgAsInt32(4));
            msg_string += ", durration(last):"+ofToString(m.getArgAsInt32(5));
            msg_string += ", delta:"+ofToString(m.getArgAsInt32(6));
            msg_string += ", noteOn|Off:"+ofToString(m.getArgAsInt32(7))+"]";

            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 10.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
            
            
        } else if(m.getAddress() == "/follow") {
            
            int noteLength = 4;
            
            
            if(m.getArgAsString(1) == "4n"){
                noteLength = 4;
            } else if (m.getArgAsString(1) == "8n"){
                noteLength = 8;
            } else if (m.getArgAsString(1) == "16n"){
                noteLength = 16;
            } else if (m.getArgAsString(1) == "32n"){
                noteLength = 32;
            } else if (m.getArgAsString(1) == "64n"){
                noteLength = 64;
            } else if (m.getArgAsString(1) == "128n"){
                noteLength = 128;
            } else {
               noteLength = 4;
            }
        
            DrawCircle(m.getArgAsInt32(0), noteLength, 40);
            
            ofPushStyle();
            ofFill();
            ofSetColor(255, 0, 0);
            ofPopStyle();
           
            string msg_string;
            msg_string = m.getAddress();
            //msg_string += "follow:"+ofToString(m.getArgAsInt32(0));
            
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 10.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
        }
        else{
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofRectangle(20,50,tweenback.update(),20);
    ofRectangle(20,80,tweenbounce.update(),20);
    ofRectangle(20,110,tweencirc.update(),20);
    ofRectangle(20,140,tweencubic.update(),20);
    ofRectangle(20,170,tweenelastic.update(),20);
    ofRectangle(20,200,tweenexpo.update(),20);
    
    ofPushStyle();
        ofFill();
        ofSetColor(0, 0, 255,150);
        ofRectangle(20,230,tweenlinear.update(),20);
    ofPopStyle();

    ofRectangle(20,260,tweenquad.update(),20);
    ofRectangle(20,290,tweenquart.update(),20);
    ofRectangle(20,320,tweenquint.update(),20);
    ofRectangle(20,350,tweensine.update(),20);
    
    // in sync multitween
//    ofRectangle(20,400,multitween.update(),20);
//    ofRectangle(20,430,multitween.getTarget(1),20);
//    ofRectangle(20,460,multitween.getTarget(2),20);
//    ofRectangle(20,490,multitween.getTarget(3),20);
//    ofRectangle(20,520,multitween.getTarget(4),20);
//    ofRectangle(20,550,multitween.getTarget(5),20);
    
    ofDrawBitmapString("back: "+ofToString(int(tweenback.update())),30,65);
    ofDrawBitmapString("bounce:"+ofToString(int(tweenbounce.update())),30,95);
    ofDrawBitmapString("circ:"+ofToString(int(tweencirc.update())),30,125);
    ofDrawBitmapString("cubic:"+ofToString(int(tweencubic.update())),30,155);
    ofDrawBitmapString("elastic:"+ofToString(int(tweenelastic.update())),30,185);
    ofDrawBitmapString("expo:"+ofToString(int(tweenexpo.update())),30,215);
    ofDrawBitmapString("linear:"+ofToString(int(tweenlinear.update())),30,245);
    ofDrawBitmapString("quad:"+ofToString(int(tweenquad.update())),30,275);
    ofDrawBitmapString("quart:"+ofToString(int(tweenquart.update())),30,305);
    ofDrawBitmapString("quint:"+ofToString(int(tweenquint.update())),30,335);
    ofDrawBitmapString("sine:"+ofToString(int(tweensine.update())),30,365);
    
    // in sync multitween
//    ofDrawBitmapString("multitween",30,415);
//    ofDrawBitmapString("multitween",30,445);
//    ofDrawBitmapString("multitween",30,475);
//    ofDrawBitmapString("multitween",30,505);
//    ofDrawBitmapString("multitween",30,535);
//    ofDrawBitmapString("multitween",30,565);
    
    
    
    //OSC
    string buf;
    buf = "listening for osc messages on port" + ofToString(PORT);
    ofDrawBitmapString(buf, 10, 10);
   
    ofCircle(myCircle.x, myCircle.height, myCircle.radius);
   
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        ofDrawBitmapString(msg_strings[i], 10, 415 + 15 * i);
    }
}


//--------------------------------------------------------------
void ofApp::OSClaunch(int _durration){
    unsigned delay = 0;
    unsigned duration = _durration;
    cout << "current durration: " << duration << endl;
    tweenback.setParameters(1,easingback,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenbounce.setParameters(2,easingbounce,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweencirc.setParameters(3,easingcirc,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweencubic.setParameters(4,easingcubic,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenelastic.setParameters(5,easingelastic,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenexpo.setParameters(6,easingexpo,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenlinear.setParameters(7,easinglinear,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenquad.setParameters(8,easingquad,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenquart.setParameters(9,easingquart,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenquint.setParameters(10,easingquint,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweensine.setParameters(10,easingsine,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    
    multitween.setParameters(easingquart,ofxTween::easeInOut,0,ofGetWidth()-100,duration,delay);
    multitween.addValue(0,ofGetWidth()-120);
    multitween.addValue(0,ofGetWidth()-140);
    multitween.addValue(0,ofGetWidth()-160);
    multitween.addValue(0,ofGetWidth()-180);
    multitween.addValue(0,ofGetWidth()-200);
    multitween.start(); //dont forget to call start to sync all the tweens
    
}

//--------------------------------------------------------------
void ofApp::DrawCircle(int y, int m, int r){
    myCircle.unit = (ofGetWidth()-100)/m;
    myCircle.height = 600-y*2;
    myCircle.radius = r-(y/6);
    
    //draw myCircle
    myCircle.x += myCircle.unit;
    if(myCircle.x > (ofGetWidth()-100)){
        myCircle.x = 0;
    }
    
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    unsigned delay = 0;
    unsigned duration = ofRandom(200,4000);
    cout << "current durration: " << duration << endl;
    tweenback.setParameters(1,easingback,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenbounce.setParameters(2,easingbounce,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweencirc.setParameters(3,easingcirc,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweencubic.setParameters(4,easingcubic,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenelastic.setParameters(5,easingelastic,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenexpo.setParameters(6,easingexpo,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenlinear.setParameters(7,easinglinear,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenquad.setParameters(8,easingquad,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenquart.setParameters(9,easingquart,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweenquint.setParameters(10,easingquint,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    tweensine.setParameters(10,easingsine,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    
    multitween.setParameters(easingquart,ofxTween::easeInOut,0,ofGetWidth()-100,duration,delay);
    multitween.addValue(0,ofGetWidth()-120);
    multitween.addValue(0,ofGetWidth()-140);
    multitween.addValue(0,ofGetWidth()-160);
    multitween.addValue(0,ofGetWidth()-180);
    multitween.addValue(0,ofGetWidth()-200);
    multitween.start(); //dont forget to call start to sync all the tweens

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

}
