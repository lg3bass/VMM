// inlets and outlets
inlets = 1;
outlets = 2;

var myval=0;//unused, was from demo

var startTime = 0.0;
var currentTime = 0.0;
var totalTime = 16.0;

var segments = new Object();
var currentSegment = 0;

//file object
var f;

glob = new Global("folderpath");
glob.path = "Macintosh HD:/Users/lg3/Documents/"; //set the default


var path = glob.path;
var filename = "chn_output.chn";
var outfile = glob.path + filename;



if(jsarguments.length>1)
	myval = jsarguments[1];
	
function bang()
{
	//output a list
	outlet(0,"currentTime","is",currentTime);
	
	//send out a console msg.
	post("clear values!!" + "\n");
	
	currentTime = 0;
}

function list()
{

	post("currentSegment: "+currentSegment + "\n");
	
	var a = arrayfromargs(arguments);
	//post(a + "\n");
	
	//silence before note
	var silence = a[1] - currentTime;
	post("silence: " + silence + "(" + currentTime + "-" + a[1] + ")" + "\n");
	
	var data = ["{	 untie  is os ia oa }",silence,"0 0","linear()","silence",a[0]];
	segments[currentSegment] = data;
	
	currentSegment++;

	

	//note
	currentTime = a[1] + a[2];
	post("note: " + a[2] + "(" + a[1] + "-" + currentTime + ")" + "\n");
	
	//new note, new object entry
	var data = ["{	 untie  is os ia oa }",a[2],"0 0","linear()","note",a[0]];
	segments[currentSegment] = data;

	currentSegment++;


}


function anything()
{
	
	var currentSegment;
	var a = arrayfromargs(messagename, arguments);
	

	if(a == "done"){
		//post("received message: " + a + "\n");
	
		
		//do the last silence
		var silence = totalTime - currentTime;
		//output the final silence
		post("silence: " + silence + "(" + currentTime + "-" + totalTime + ")" + "\n");
		var data = ["{	 untie  is os ia oa }",silence,"0 0","linear()","silence",0];
		segments[currentSegment] = data;
		
		//set the filename
		for(i in segments){
			if(segments[i][4] == "note"){
				filename = segments[i][5] + "_output.chn";
			}
		}
		
		//filename = segments[0][5] + "_output.chn";
		
		//setup the outfile
		outfile = glob.path + filename;
		post("writing to outfile: \n" + outfile + "\n");

		
		

		currentSegment = 0;
		writeSegments();
		clear();

	} else if (a == "getPath"){
		post(folderpath.path + "\n");
		post(outfile+"\n");
	}
	//myval = a;
	bang();
}


function writeSegments(){
	
	//create a new file for writing the .chn
	f = new File(outfile, "write", "TEXT");
	
	if(f.isopen) {
        f.eof = 0;//need to do this.
        
		f.writeline("ACHN 2");
		f.writeline("start = 0");
		f.writeline("end = 20.0");
		f.writeline("/obj/null {");
		f.writeline("\t" + "channel null {");
		for(i in segments){
			
			writeSegment(i);
			
		}
		f.writeline("\t"+"}");
		f.writeline("}");

		//post("writing to file: " + filename + "\n");
		
		//close the file for writing
    	f.close();
	} else {
		post("could not write " + filename + "\n");
	}	
	
}

function writeSegment(i){

	if(segments[i][4] == "note"){
				
		//calculate and write ADSR values.
		writeADSR(i);
				
	} else if(segments[i][4] == "silence"){
		
		if(segments[i][1] > 0){
			writeSilence(i);
		} else {
			post("not writing silence"+"\n");
		}
		
			
	} else {
		post("not writeSegment"+"\n");
	}
	
		
				
}



function writeADSR(i){
	
	var len = segments[i][1];
	
	if(len>0.2){
		//write 4 time for ADSR
		
		//Attack
		f.writeline("\t\t" + "segment {");
		f.writeline("\t\t\t" + "options = " + segments[i][0]);
		f.writeline("\t\t\t" + "length = 0.1");
		f.writeline("\t\t\t" + "value = 0 30");
		f.writeline("\t\t\t" + "expr = "+ segments[i][3]);
		f.writeline("\t\t" +"}");
		
		//Decay
		f.writeline("\t\t" + "segment {");
		f.writeline("\t\t\t" + "options = " + segments[i][0]);
		f.writeline("\t\t\t" + "length = 0.1");
		f.writeline("\t\t\t" + "value = 30 60");
		f.writeline("\t\t\t" + "expr = "+ segments[i][3]);
		f.writeline("\t\t" +"}");
		
		//Sustain
		f.writeline("\t\t" + "segment {");
		f.writeline("\t\t\t" + "options = " + segments[i][0]);
		f.writeline("\t\t\t" + "length = " + (len-0.3));
		f.writeline("\t\t\t" + "value = 60 60");
		f.writeline("\t\t\t" + "expr = "+ segments[i][3]);
		f.writeline("\t\t" +"}");
		
		//Release
		f.writeline("\t\t" + "segment {");
		f.writeline("\t\t\t" + "options = " + segments[i][0]);
		f.writeline("\t\t\t" + "length = 0.09");
		f.writeline("\t\t\t" + "value = 60 90");
		f.writeline("\t\t\t" + "expr = "+ segments[i][3]);
		f.writeline("\t\t" +"}");
		
		
	} else {
		//write DR
		
	}
	
	//Zero
		f.writeline("\t\t" + "segment {");
		f.writeline("\t\t\t" + "options = " + segments[i][0]);
		f.writeline("\t\t\t" + "length = 0.01");
		f.writeline("\t\t\t" + "value = 90 0");
		f.writeline("\t\t\t" + "expr = "+ segments[i][3]);
		f.writeline("\t\t" +"}");
	
}




function writeSilence(i){
	
	f.writeline("\t\t" + "segment {");
	f.writeline("\t\t\t" + "options = " + segments[i][0]);
	f.writeline("\t\t\t" + "length = " + segments[i][1]);
	f.writeline("\t\t\t" + "value = " + segments[i][2]);
	f.writeline("\t\t\t" + "expr = "+ segments[i][3]);
	f.writeline("\t\t" +"}");
		
}

function clear(){
	segments = new Object();
    post("\ncleared");
}


autowatch = 1;