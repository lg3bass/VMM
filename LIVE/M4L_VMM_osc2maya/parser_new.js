var myval=0;

if (jsarguments.length>1)
	myval = jsarguments[1];
	
	
function bang()
{
	//outlet(0,"OSC: ","is",myval);
}

function header(){
	outlet(0,"OSC msg\t\ttrack\tbuffer\tstring\tnoteID\tnote\tvelocity\tlastDur\tonOff\tDUR\tseg\tcurve\tdelta\t\n");

}
	

function noteOn(message)
{
	//post("note on: " + message[0] + "\ttrack: " + message[1] + "\n");
	

	outlet(0,	message[0] + "\t" + //osc message
				message[1] + "\t\t" + //track
				message[2] + "\t\t" + //buffer
				message[3] + "\t\t" + //string
				message[4] + "\t" + //noteID
				message[5] + "\t\t" + //midi note
				message[6] + "\t\t\t" + //velocity as read from midi clip
				message[7] + "\t\t" + //last Durration
				message[9] + "\t\t\t\t\t\t" + //midi note On|Off state
				message[8] + "\n"); //delta from last note
	
}

function play(message)
{
	//post("play: " + message[0] + "\ttrack: " + message[1] + "\n");
	

	outlet(0,	message[0] + "\t\t" + //osc message
				message[1] + "\t\t" + //track
				message[2] + "\t\t" + //buffer
				message[3] + "\t\t" + //string
				message[4] + "\t" + //noteID
				message[5] + "\t\t\t\t\t\t\t\t\t" + //midi note
				message[6] + "\t" + //DURRATION knob
				message[7] + "\t" + //segment
				message[8] + "\n"); //animation curve
	
}




function list(){
	
}

function anything()
{
	var a = arrayfromargs(messagename, arguments);
	
	if(a[0] == "/noteOn"){
		noteOn(a);
	}
	if(a[0] == "/play"){
		play(a);
	}
	post("received message " + a + "\n");
	myval = a;
	bang();
}