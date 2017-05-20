Rebuild Steps for OF 9.8
-------------------------------
VMM was developed on OF 8.4.  It was suprisingly easy to upgrade to OF 9.8.

1. Get all the addons
	1. ofxGui (default)
	2. ofxJSON - https://github.com/jeffcrouse/ofxJSON/tree/5934d7044406041d46c763d0509613ac71801256
	3. ofxObjLoader - https://github.com/andreasmuller/ofxObjLoader/tree/fc5bbb1bc7efd396cd46cd6e312669cb4a362ba0
	4. ofxOsc (default)
	5. ofxSyphon - https://github.com/astellato/ofxSyphon/tree/46a27161872124fa7a237a6a9a6dd9ee76e1010a
	6. ofxTween - https://github.com/obviousjim/ofxTween/tree/120757d613b497a7045ee64c1e548abf31ace38e
	7. ofxUI - https://github.com/robksawyer/ofxUI/tree/e79e619e81918f356a0d4c9faf34bb69257a62cc
	8. ofXmlSettings (default)
	9. NOTE: I removed ofxMidi, ofxAutoReloadedShader.
2. Get a copy of the 'bin/data/obj/' folder.  This contains all the obj files. These are ~500mb so I don't keep them on git. Contact me if you want these. rlgw3 - yahoo - com.
3. clone the VMM/OF_9.8/VMM_9-8 project.