## **M4L DEVICES**

#### M4L\_VMM\_ASD\_trigger


**Current trigger device** to run VMM animation.  I had initially tired to run a line object from within max but I noticed that after a while of repetitive play the line object crapped out.  So now I send a single line command over to VMM which then runs a tween.

	/VMM/LIVE/M4L_VMM_ASDR_trigger/

| STATUS | FILE | CHANGELOG |
| --- | :--- | :--- |
| OLD | vmm\_adsr\_trigger\_1.0.amxd | 20190127 - Create a new device 1.0. Buffers set /localCopies. |
| CURRENT | vmm\_adsr\_trigger\_1.1.amxd | 20190127 - v1.1 |

#### M4L\_VMM\_clip\_launch\_timeline

This device will launch tracks in my VMM_timeline app.  It listens to the Ableton timeline using clip launch observer objects for trigger events in arrangement view and launches the corresponding clip in VMM Timeline.

_**NOTE**: Always place the clip\_launch\_timeline device AFTER all the other M4L devices like vmm\_asdr\_trigger.amxd.  There is not MIDI-IN/MIDI-OUT on this device._

	/VMM/LIVE/M4L_VMM_clip_launch_timeline/

| STATUS | FILE | CHANGELOG |
| --- | :--- | :--- |
| Current | vmm\_clip\_launch\_timeline\_0.3.amxd | 20190127 - cleaned up presentation mode, added title. |
| Current | vmm\_clip\_launch\_timeline\_0.2.amxd | 20181012 - filtered out duplicate play messages. removed midi in. |
| OLD | vmm\_clip\_launch\_timeline\_0.1.amxd | |

#### M4L\_VMM\_manager
* vmm\_manager\_1.0
	* MVL\_vmm\_manager\_1.amxd
* vmm\_manager\_1.3
	* MVL\_vmm\_manager\_1.3.amxd

#### M4L\_VMM\_OSC
* vmm\_osc\_dispatcher\_1.0
	* M4L\_vmm\_OSC\_Dispatcher.amxd
* vmm\_osc\_dispatcher\_1.1
	* M4L\_vmm\_OSC\_Dispatcher\_1-1.amxd

#### M4L\_VMM\_osc2maya

#### M4L\_VMM\_position
* vmm\_position\_global\_0.1
* vmm\_position\_local\_0.1

#### M4L\_VMM\_string
* vmm\_string\_1.0
* vmm\_string\_1.1
* vmm\_string\_1.2
	*  //here I started to work with ADSR param
		*  M4L_vmm_string.amxd
		*  M4L_vmm_string_1.2.amxd, M4L_vmm_string_1.2a.amxd, M4L_vmm_string_1.2b.amxd, M4L_vmm_string_1.2c.amxd, M4L_vmm_string_1.3.amxd
		*  M4L_vmm_string_1.3.1.amxd (CURRENT)
		
#### M4L\_VMM\_track
* vmm\_track\_1.3
* vmm\_track\_2.0

