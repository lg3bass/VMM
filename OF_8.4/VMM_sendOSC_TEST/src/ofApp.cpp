#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(40, 100, 40);

	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
    
    singleKeyDown = true;
    
    //displayable messages on screen
    current_msg_string = 0;
    
    bufferCounter = -1;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

	// display instructions
	string buf;
	buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
	ofDrawBitmapString("1: single note (track 4)", 10, 50);
	ofDrawBitmapString("2: 3 notes (track 4)", 10, 65);
    ofDrawBitmapString("press to send the OSC midi messages to VMM", 10, 75);
    
    //draw the message strings
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        ofDrawBitmapString(msg_strings[i], 10, 90 + 15 * i);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'a' || key == 'A'){
		ofxOscMessage m;
		m.setAddress("/test");
		m.addIntArg(1);
		m.addFloatArg(3.5f);
		m.addStringArg("hello");
		m.addFloatArg(ofGetElapsedTimef());
		sender.sendMessage(m);
	}
    
    if(key == '1'){
        
        if(bufferCounter < 11){
            bufferCounter++;
        } else {
            bufferCounter = 0;
        }
        
        string msg_string;
        msg_string += ofToString(bufferCounter);
        updateMessages(msg_string);
        
        //1. capture the note and place in buffer(instance object)
        if(singleKeyDown){
            ///noteOn [track:4, buffer:1, string:1, noteId:4, midiNote:60, velocity:63, durration(last):1000, delta:26422, noteOn|Off:1]
            noteOn(4,bufferCounter,1,4,62,127,1000,26422,1);
            
            //play [track:4, buffer:1, string:1, noteId:4, midiNote:60, cue:1, duration:601, tween:11]
            play(4,bufferCounter,1,4,62,1,601,11);
        }
    }
    
    if(key == '2'){
        if(singleKeyDown){
            noteOn(4,2,1,4,45,127,1000,26422,1);
            noteOn(4,3,1,5,55,127,1000,26422,1);
            noteOn(4,4,1,6,65,127,1000,26422,1);
            //play(4,4,20,500,11);
        }
    }
    if(key == '3'){
        
    }
    if(key == '4'){

    }
    if(key == '5'){
        
    }
    if(key == ' '){
        ofxOscMessage m;
        m.setAddress("/clear");
        m.addIntArg(4);
        sender.sendMessage(m);
        
        string msg_string;
        msg_string = m.getAddress();
        msg_string += " "+ofToString(4);
        updateMessages(msg_string);
        
        bufferCounter = -1;
    }

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    //noteOff <track><noteID><real-durration>
    
    if(key == '1'){
        //noteOff [track:4, string:1, noteId:4, midiNote:60, velocity:0, real-duration:1000, delta:26422, note On|Off:0]
        noteOff(4, 1, 4, 62, 0, 1000, 26422, 0);
    }
    if(key == '2'){
        //noteOff(4, 2, 700);
        //noteOff(4, 3, 700);
        //noteOff(4, 4, 700);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	
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
    
}

//--------------------------------------------------------------
void ofApp::noteOn(int track, int buffer, int string, int noteID, int midiNote, int velocity, int duration, int delta, int noteOnOff){
    //noteOn [track:4, buffer:1, string:1, noteId:4, midiNote:60, velocity:63, durration(last):1000, delta:26422, noteOn|Off:1]
    
    
    ofxOscMessage m;
    m.setAddress("/noteOn");
    m.addIntArg(track);//track
    m.addIntArg(buffer);//buffer
    m.addIntArg(string);//string
    m.addIntArg(noteID);//noteID
    m.addIntArg(midiNote);//midi Note number
    m.addIntArg(velocity);//midi velocity
    m.addIntArg(duration);//duration
    m.addIntArg(delta);//delta
    m.addIntArg(noteOnOff);
    sender.sendMessage(m);
    
    singleKeyDown = false;
    
    
    tempString = "";
    tempString += "//noteOn [track:"+ofToString(track)+
    ", buffer:"+ofToString(buffer)+
    ", string:"+ofToString(string)+
    ", noteId:"+ofToString(noteID)+
    ", midiNote:"+ofToString(midiNote)+
    ", velocity:"+ofToString(velocity)+
    ", durration(last):"+ofToString(duration)+
    ", delta:"+ofToString(delta)+
    ", noteOn|Off:"+ofToString(noteOnOff)+
    "]";
    updateMessages(tempString);
    
    
}

//--------------------------------------------------------------
void ofApp::play(int track, int buffer, int string, int noteId, int midiNote, int cue, int duration, int tween){
    //play [track:4, buffer:1, string:1, noteId:4, midiNote:60, cue:1, duration:601, tween:11]
    
    ofxOscMessage m;
    m.setAddress("/play");
    m.addIntArg(track);//track
    m.addIntArg(buffer);//buffer
    m.addIntArg(string);
    m.addIntArg(noteId);
    m.addIntArg(midiNote);
    m.addIntArg(cue);//target frame
    m.addIntArg(duration);//durration
    m.addIntArg(tween);//tween
    sender.sendMessage(m);
    
    singleKeyDown = false;
    

    tempString = "";
    tempString += "//play [track:" + ofToString(track) +
    ", buffer:" + ofToString(buffer) +
    ", string:"+ ofToString(string) +
    ", noteId:"+ ofToString(noteId) +
    ", midiNote:"+ ofToString(midiNote) +
    ", cue:"+ ofToString(cue) +
    ", duration:"+ ofToString(duration) +
    ", tween:"+ ofToString(tween) +
    "]";
    updateMessages(tempString);

    
}

//--------------------------------------------------------------
void ofApp::noteOff(int track, int string, int noteID, int midiNote, int velocity, int duration, int delta, int noteOnOff){
    //noteOff [track:4, string:1, noteId:4, midiNote:60, velocity:0, real-duration:1000, delta:26422, note On|Off:0]
    
    ofxOscMessage m;
    m.setAddress("/noteOff");
    m.addIntArg(track);//track
    m.addIntArg(string);
    m.addIntArg(noteID);//noteID
    m.addIntArg(midiNote);
    m.addIntArg(velocity);
    m.addIntArg(duration);//real durration
    m.addIntArg(delta);
    m.addIntArg(noteOnOff);
    sender.sendMessage(m);
    
    singleKeyDown = true;

    tempString = "";
    tempString += "//noteOff [track:"+ofToString(track)+
    ", string:"+ofToString(string)+
    ", noteId:"+ofToString(noteID)+
    ", midiNote:"+ofToString(midiNote)+
    ", velocity:"+ofToString(velocity)+
    ", real-duration:"+ofToString(duration)+
    ", delta:"+ofToString(delta)+
    ", note On|Off:"+ofToString(noteOnOff)+
    "]";
    updateMessages(tempString);
}

//--------------------------------------------------------------
void ofApp::updateMessages(string msg){
    // add to the list of strings to display
    msg_strings[current_msg_string] = msg;
    timers[current_msg_string] = ofGetElapsedTimef() + 20.0f;
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
}

