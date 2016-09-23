// added
#version 120
#extension GL_EXT_gpu_shader4 : require


//end new


varying vec3 normal;




mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    return mat4(oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s, 0.0,
                oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s, 0.0,
                oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c, 0.0,
                0.0, 0.0, 0.0, 1.0);
}





void main(void) {
    
    
	float iCount = 5;
	
    
    mat4 rotMatrix = rotationMatrix(vec3(0,0,1),0.6*gl_InstanceID);
    
    //what the fuck are you doing?????
    //vec4 scaleMatrix = vec4(gl_InstanceID*0.01,gl_InstanceID*0.01,gl_InstanceID*0.01,1.0);
    
	// when drawing instanced geometry, we can use gl_InstanceID
	// this tells you which primitive we are currently working on
	
	// we would like to spread our primitives out evenly along the x and an y coordinates
	// we calculate an x and an y coordinate value based on the current instance ID
	
	float instanceX = (mod(gl_InstanceID,iCount) - iCount/2.0) / 10.0;
	float instanceY = ((gl_InstanceID/iCount) - iCount/2.0) / 10.0;

	vec4 vPos = gl_Vertex;
	
	// this will distribute our boxes in space,
	vPos = vPos + vec4(instanceX*5.0*2.0+5.0,instanceY*5.0*2.0+5.0, gl_InstanceID*2.0,0.0);
    //vPos = vPos + vec4((iCount*rotation)*vPos);

 	normal = normalize(gl_NormalMatrix * gl_Normal).xyz;
    //gl_Position = ftransform();
    //gl_Position = gl_ModelViewProjectionMatrix * rotMatrix * vPos * scaleMatrix;
    gl_Position = gl_ModelViewProjectionMatrix * rotMatrix * vPos;
}