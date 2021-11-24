# VMM

## LATEST
[20211124 - commit old code](https://github.com/lg3bass/VMM/commit/0253084b35bd25025af850689c01ee10f73fcf68)

This project is a set of tools to animate .obj sequence files.  The idea behind this project is to use M4L to send note data to VMM (OF application) to make .obj sequences dance. 

The last song I used this on was [https://github.com/lg3bass/20190416_improv-001](https://github.com/lg3bass/20190416_improv-001). This song was published 5/23/2019.  The general feeling was while I got the entire workflow working it was still a lot of clean up work.  After this project I shifted my efforts to a MAX/M4L (only) solution using GLSL shaders. 

1. [https://github.com/lg3bass/ADSR-JXS](https://github.com/lg3bass/ADSR-JXS)
2. [https://github.com/lg3bass/ADSR](https://github.com/lg3bass/ADSR)
3. [https://github.com/lg3bass/ADSR-automation](https://github.com/lg3bass/ADSR-automation)
4. [https://github.com/lg3bass/ADSR-sound](https://github.com/lg3bass/ADSR-sound)
5. [https://github.com/lg3bass/ADSR_ISF](https://github.com/lg3bass/ADSR_ISF)
6. [https://github.com/lg3bass/ADSR-world-out](https://github.com/lg3bass/ADSR-world-out)



## There are 4 main folders in the project

### LIVE 
- contains a collection of M4L devices that send and receive data to VMM.
- see the [LIVE/README.md](LIVE/README.md)

### MAX
- I have forgotten what these do but they seem like a collection of MAX patches to receive note information from my GR-55 Guitar to Midi system.  Looks like they separate the data by string.
- see the [MAX/MAX_README.md](MAX/MAX_README.md)


### OF_8.4
- I started this project in OF 8.4 and this is the code from that.

### OF_9.8
- This is the latest version of the VMM application. Within are 3 notable applications.
	- /VMM/OF_9.8/VMM_9-8/bin/VMM_9-8.app (not included)
		- This is a tool to trigger .obj sequence files.
	- /VMM/OF_9.8/VMM_recieveOSC_TEST/bin/VMM_recieveOSC_TEST.app (not included)
		- This is a tester if data is being received from LIVE
	- /VMM/OF_9.8/VMMtimeline_9-8/bin/VMMtimeline_9-8.app (not included)
		- This is a external timeline application that uses Ableton Link keep in sync with LIVE.
		- For the most part this application drives the translation and params of the VMM_9-8.app
		
## Future Plans

This application developed with OF 9.8 5 years ago.  If any new development will be done first I will need port the code to the latest version OF. The .obj sequence code needs to be spun off to a new ofAddon and I will ditch the VMMtimeline_9-8.app in favor of using MAX/M4L to control.  