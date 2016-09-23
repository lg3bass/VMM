//
//  oscRouter.cpp
//  ofxObjLoader_test10
//
//  Created by bob white III on 4/28/16.
//
//

#include "oscRouter.h"

//--------------------------------------------------------------
oscRouter::oscRouter(){
    
    
}

//--------------------------------------------------------------
void oscRouter::processOSCmessage(ofxOscMessage &m, vector<vboMeshObj> &tracks, int num_tracks){
    
    //what channel/track
    idx = m.getArgAsInt32(0);
    
    
    if (m.getAddress() == "/noteOn"){
        //cout << "----------------------------------------------------------------" << endl;
        //the message sets the buffer, and general data on the notes.
        
        //VMMnoteID = <string>+<midiNote>;
        VMMnoteID = ofToInt(ofToString(m.getArgAsInt32(2)) + ofToString(m.getArgAsInt32(4)));
        //ofLogNotice("OSC") << "VMMnoteID(ON)------------------------------: " << VMMnoteID;
        
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
        
        //----------noteOn(_buffer           |VMMnoteID|_midiNote         |_velocity         |_delta )
        tracks[idx].noteOn(m.getArgAsInt32(1),VMMnoteID,m.getArgAsInt32(4),m.getArgAsInt32(5),m.getArgAsInt32(7));
        
    } else if (m.getAddress() == "/play"){
        
        VMMnoteID = ofToInt(ofToString(m.getArgAsInt32(2)) + ofToString(m.getArgAsInt32(4)));
        
        //This message launches the animation clip and adds
        //the segment to play(coming soon), durration, and tweentype.
        ofLogVerbose("OSC") << ">>>>---->" << m.getAddress() <<
        " [track:" << m.getArgAsInt32(0) <<
        ", buffer:" << m.getArgAsInt32(1) <<
        ", string:" << m.getArgAsInt32(2) <<
        ", noteId:" << m.getArgAsInt32(3) <<
        ", midiNote:" << m.getArgAsInt32(4) <<
        ", duration:" << m.getArgAsInt32(5) <<
        ", cue:" << m.getArgAsInt32(6) <<
        ", tween:" << m.getArgAsInt32(7) <<
        "]";
        
        //----------play(_buffer           | VMMnoteID| _duration         | _tweenType)
        tracks[idx].play(m.getArgAsInt32(1), VMMnoteID, m.getArgAsInt32(5), m.getArgAsInt32(7));
        
    } else if (m.getAddress() == "/noteOff"){
        
        ofLogVerbose("OSC") << "-------->" << m.getAddress() <<
        " [track:" << m.getArgAsInt32(0) <<
        ", string:" << m.getArgAsInt32(1) <<
        ", noteId:" << m.getArgAsInt32(2) <<
        ", midiNote:" << m.getArgAsInt32(3) <<
        ", velocity:" << m.getArgAsInt32(4) <<
        ", real-duration:" << m.getArgAsInt32(5) <<
        ", delta:" << m.getArgAsInt32(6) <<
        ", note On|Off:" << m.getArgAsInt32(7) <<
        "]";
        
        VMMnoteID = ofToInt(ofToString(m.getArgAsInt32(1)) + ofToString(m.getArgAsInt32(3)));
        //ofLogNotice("OSC") << "------------------------------VMMnoteID(OFF): " << VMMnoteID;
        
        //----------noteOff(VMMnoteId| _durration)
        tracks[idx].noteOff(VMMnoteID, m.getArgAsInt32(5));
        
    } else if (m.getAddress() == "/clear"){
        
        ofLogVerbose("OSC") << m.getAddress() << endl << "track:" << m.getArgAsInt32(0);
        
        //int idx = m.getArgAsInt32(0);
        tracks[idx].clear();
    
    } else if (m.getAddress() == "/OSCsetMatCap"){
    
        ofLogVerbose("OSC") << m.getAddress() << endl << "/OSCsetMatCap " << m.getArgAsInt32(0);
        tracks[idx].matcapIndex = m.getArgAsInt32(1);
        tracks[idx].setMatCap(m.getArgAsInt32(1));
        
    } else if (m.getAddress() == "/OSCsetTrack"){
        ofLogVerbose("OSC") << m.getAddress() << endl << "/OSCsetTrack " << m.getArgAsInt32(0);
        tracks[idx].objSeqIndex = m.getArgAsInt32(1);
        tracks[idx].setTrack(m.getArgAsInt32(1));
        
    } else if (m.getAddress() == "/butter"){
        tracks[idx].trackParameters.setOSCtoggle(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
        tracks[idx].loadTrack();
        
    } else if (m.getAddress() == "/still"){
        tracks[idx].trackParameters.setOSCtoggle(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
    } else if (m.getAddress() == "/playNoteOff"){
        tracks[idx].trackParameters.setOSCtoggle(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
    } else if (m.getAddress() == "/playAll"){
        tracks[idx].trackParameters.setOSCtoggle(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
    } else if (m.getAddress() == "/finalize"){
        tracks[idx].trackParameters.setOSCtoggle(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
    } else if (m.getAddress() == "/mirror"){
        tracks[idx].trackParameters.setOSCtoggle(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
    } else if (m.getAddress() == "/mirrorX"){
        tracks[idx].trackParameters.setOSCtoggle(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
    } else if (m.getAddress() == "/mirrorY"){
        tracks[idx].trackParameters.setOSCtoggle(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
    } else if (m.getAddress() == "/mirrorZ"){
        tracks[idx].trackParameters.setOSCtoggle(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
    
    
    } else if (m.getAddress() == "/mirrorDistance"){        
        tracks[idx].trackParameters.setOSCdial(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
        
    } else if (m.getAddress() == "/localCopies"){
        //ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1);
        //tracks[idx].setLocalCopies(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCdial(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
        
    } else if (m.getAddress() == "/localSlices"){
        tracks[idx].trackParameters.setOSCdial(tracks[idx].params, m.getAddress(), m.getArgAsInt32(1));
        
    } else if (m.getAddress() == "/localScale"){
        tracks[idx].trackParameters.setOSCdial(tracks[idx].params, m.getAddress(), m.getArgAsFloat(1));

        
        // GLOBAL ROTATE --------------------------------------
    } else if (m.getAddress() == "/randGlobalRotX" || m.getAddress() == "/tweenGlobalRotX"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomGlobalRotX, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/randGlobalRotY" || m.getAddress() == "/tweenGlobalRotY"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomGlobalRotY, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/randGlobalRotZ" || m.getAddress() == "/tweenGlobalRotZ"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomGlobalRotZ, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/setGlobalRotX" || m.getAddress() == "/setGlobalRotY" || m.getAddress() == "/setGlobalRotZ"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCdial(tracks[idx].params, m.getAddress(), float(m.getArgAsInt32(1)));
        
        
        
        // GLOBAL TRANSLATE --------------------------------------
    } else if (m.getAddress() == "/randGlobalTransX" || m.getAddress() == "/tweenGlobalTransX"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomGlobalX, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/randGlobalTransY" || m.getAddress() == "/tweenGlobalTransY"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomGlobalY, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/randGlobalTransZ" || m.getAddress() == "/tweenGlobalTransZ"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomGlobalZ, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/setGlobalTransX" || m.getAddress() == "/setGlobalTransY" || m.getAddress() == "/setGlobalTransZ"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCdial(tracks[idx].params, m.getAddress(), float(m.getArgAsInt32(1)));
        
        
        
        
    // LOCAL ROTATE --------------------------------------
    } else if (m.getAddress() == "/randLocalRotX" || m.getAddress() == "/tweenLocalRotX"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomLocalRotX, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);

    } else if (m.getAddress() == "/randLocalRotY" || m.getAddress() == "/tweenLocalRotY"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomLocalRotY, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/randLocalRotZ" || m.getAddress() == "/tweenLocalRotZ"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomLocalRotZ, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/setLocalRotX" || m.getAddress() == "/setLocalRotY" || m.getAddress() == "/setLocalRotZ"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCdial(tracks[idx].params, m.getAddress(), float(m.getArgAsInt32(1)));
    
    
        
    // LOCAL TRANSLATE --------------------------------------    
    } else if (m.getAddress() == "/randLocalTransX" || m.getAddress() == "/tweenLocalTransX"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomLocalX, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/randLocalTransY" || m.getAddress() == "/tweenLocalTransY"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomLocalY, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);

    } else if (m.getAddress() == "/randLocalTransZ" || m.getAddress() == "/tweenLocalTransZ"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomLocalZ, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/setLocalTransX" || m.getAddress() == "/setLocalTransY" || m.getAddress() == "/setLocalTransZ"){
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCdial(tracks[idx].params, m.getAddress(), float(m.getArgAsInt32(1)));
        
        
    // OBJECT ROTATE --------------------------------------
    } else if (m.getAddress() == "/randObjRotX" || m.getAddress() == "/tweenObjRotX") {
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomObjRotX, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/randObjRotY" || m.getAddress() == "/tweenObjRotY") {
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomObjRotY, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/randObjRotZ" || m.getAddress() == "/tweenObjRotZ") {
        
        ofLogVerbose("OSC") << m.getAddress() << " " << m.getArgAsInt32(0) << " " << float(m.getArgAsInt32(1));
        tracks[idx].trackParameters.setOSCtween(tracks[idx].params, tracks[idx].posRandomObjRotZ, m.getAddress(), tracks[idx].easingquad, float(m.getArgAsInt32(1)), 1000.0);
        
    } else if (m.getAddress() == "/setObjRotX" || m.getAddress() == "/setObjRotY" || m.getAddress() == "/setObjRotZ") {
        tracks[idx].trackParameters.setOSCdial(tracks[idx].params, m.getAddress(), float(m.getArgAsInt32(1)));
        
    
    // BASS CONTROL ---------------------------------------
    } else if (m.getAddress() == "/bass"){
        //this mesage streams in a amplitude
        //data from an envelop filter in MAX/LIVE
        
        //m.getArgAsInt32(0) = value from REF filter.
        //m.getArgAsString(1) = note length(sampling rate of Envelope filter)
        
        amplitude = (float)m.getArgAsInt32(0);
        
        noteLength = 4;
        
        /*
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
         */
        
        //pass in the data from the bass osc stream.  We only want to pull this in once. Only send if it's loaded
        for(int t=1; t<num_tracks;t++){
            if(tracks[t].params.isLoaded){tracks[t].bassControl(amplitude, noteLength);}
        }
        
    }
    
    
}