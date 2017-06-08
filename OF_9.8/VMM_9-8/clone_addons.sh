#!/bin/bash
#20170606
#Dependencies of VMM_9-8

if [ -z $1 ]; then
PREFIX="git clone https://github.com/"
else
PREFIX="git clone git@github.com:"
fi

cd ../../../addons

#ofxJSON--------------------------------
#https://github.com/jeffcrouse/ofxJSON/tree/5934d7044406041d46c763d0509613ac71801256
${PREFIX}jeffcrouse/ofxJSON.git

#ofxObjLoader---------------------------
#https://github.com/andreasmuller/ofxObjLoader/commit/fc5bbb1bc7efd396cd46cd6e312669cb4a362ba0
${PREFIX}andreasmuller/ofxObjLoader.git

#ofxSyphon------------------------------
#https://github.com/astellato/ofxSyphon/commit/46a27161872124fa7a237a6a9a6dd9ee76e1010a
${PREFIX}astellato/ofxSyphon.git

#ofxUI----------------------------------
#https://github.com/robksawyer/ofxUI/commit/e79e619e81918f356a0d4c9faf34bb69257a62cc
${PREFIX}robksawyer/ofxUI.git


#REQUIRED.  Included in OF release. /of_v0.9.8_osx_release/addons/ofxXmlSettings
#ofxXmlSettings
#ofxOsc
#ofxTween




