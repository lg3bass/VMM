var myval=0;

if (jsarguments.length>1)
	myval = jsarguments[1];
	
	
function bang()
{
	//outlet(0,"OSC: ","is",myval);
}

	

function noteOn(message)
{
	
	post("note on: " + message[0] + "\ttrack: " + message[1] + "\n");
	outlet(1,"note on: " + message[0] + "\ttrack: " + message[1] + "\n"); 	
}

function anything()
{
	var a = arrayfromargs(messagename, arguments);
	
	if(a[0] == "/noteOn"){
		noteOn(a);
	}
	post("received message " + a + "\n");
	myval = a;
	bang();
}