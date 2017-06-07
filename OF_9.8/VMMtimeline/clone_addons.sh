#!/bin/bash
#20170602
#Dependencies of VMM_timeline
#loosly based on https://github.com/leozimmerman/Sonoscopio

if [ -z $1 ]; then
PREFIX="git clone https://github.com/"
else
PREFIX="git clone git@github.com:"
fi

cd ../../../addons

#ofxAbletonLink------------------------
${PREFIX}comoc/ofxAbletonLink.git
cd ofxAbletonLink
git checkout 54f6483c44e0bf24af3ee1a923533883cab080b5

#readme note to get submodules.  see readme.md
git submodule update --init --recursive
cd ../

#ofxAudioDecoder------------------------
#https://github.com/leozimmerman/ofxAudioDecoder
#70e27952b7133151f6475c8f0f9fb26ae368fa8b
${PREFIX}leozimmerman/ofxAudioDecoder.git

#ofxDatGui------------------------
#https://github.com/leozimmerman/ofxDatGui
#531192bbf5b9f03c6e2b1318dfb69970f35fdaea
${PREFIX}leozimmerman/ofxDatGui.git
cd ofxDatGui
git checkout sonoscopio
cd ../

#ofxMSATimer------------------------
#https://github.com/obviousjim/ofxMSATimer/commits/master
#14e1ff8b0a358151ba13efadac96cf1c50266518
${PREFIX}obviousjim/ofxMSATimer.git
cd ofxMSATimer
git checkout 14e1ff8b0a358151ba13efadac96cf1c50266518
cd ../

#ofxRange------------------------
#github.com/Flightphase/ofxRange/commits/master
#8e232a33a0db5007c425c3d1ebc7f57ffb2232ac
${PREFIX}Flightphase/ofxRange.git
cd ofxRange
git checkout 8e232a33a0db5007c425c3d1ebc7f57ffb2232ac
cd ../

#ofxTextInputField------------------------
#github.com/elliotwoods/ofxTextInputField/commits/master
#e265bee9547cc1790395f9a1b83289e4e11a7624
${PREFIX}elliotwoods/ofxTextInputField.git
cd ofxTextInputField
git checkout e265bee9547cc1790395f9a1b83289e4e11a7624
cd ../

#ofxTimeMeasurements------------------------
#github.com/armadillu/ofxTimeMeasurements/commit/47fd27f73850dcaf27ffb5dcb339cbbc04e1af91
${PREFIX}armadillu/ofxTimeMeasurements.git
cd ofxTimeMeasurements
git checkout 47fd27f73850dcaf27ffb5dcb339cbbc04e1af91
cd ../

#ofxTimecode------------------------
#github.com/YCAMInterlab/ofxTimecode/commit/d8b6b97e1334453753b369ace86e0ce7113946b3
${PREFIX}YCAMInterlab/ofxTimecode.git
cd ofxTimecode
git checkout d8b6b97e1334453753b369ace86e0ce7113946b3
cd ../

#ofxTimeline------------------------
#github.com/lg3bass/ofxTimeline/commit/0121f3440a83d4abb5b06e3370e51643a254a96e
${PREFIX}lg3bass/ofxTimeline.git

#ofxTween------------------------
#github.com/obviousjim/ofxTween/commit/120757d613b497a7045ee64c1e548abf31ace38e
${PREFIX}obviousjim/ofxTween.git
cd ofxTween
git checkout 120757d613b497a7045ee64c1e548abf31ace38e
cd ../




