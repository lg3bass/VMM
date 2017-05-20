#version 120
#extension GL_EXT_gpu_shader4 : require 

uniform int playInstance;

uniform mat4 transformMatrix[6];//was 200
uniform mat4 rotationMatrix2[6];//was 200
uniform vec3 position[6];//was 200

//send these to the fragment shader.
varying vec3 vertex_light_position;
varying vec3 vertex_normal;

varying vec2 instanceNum;


 
void main(){

  

  //send the instance number and which one our want to play to the frag shader.
  instanceNum = vec2(gl_InstanceID,playInstance);
    
    
  //set the global scale
  vec3 scaleFactor = vec3(1.0);//20 at 640,360. Use 50 for 1024
    
  // Calculate the normal value for this vertex, in world coordinates 
  // (multiply by gl_NormalMatrix and transformation matrix)
  vertex_normal = normalize( mat3(transformMatrix[gl_InstanceID] ) * gl_NormalMatrix * gl_Normal);
	
  // Calculate the light position for this vertex
  vertex_light_position = normalize( gl_LightSource[0].position.xyz );
	
  // Set the front color to the color passed through with glColor
  gl_FrontColor = gl_Color;
  gl_BackColor = gl_Color;
    
  // Multiply the shape coordinates by the transformation matrix by the scale matrix.
  // Offset by the position -- Original Code
  //vec4 vPos = vec4( ((position[gl_InstanceID], 0 ) + ( transformMatrix[gl_InstanceID] *  gl_Vertex))  * vec4(scaleFactor,1.0) );
  
    // THIS IS IT (transMatrix * verts * scale * position)
    // If I wanted to add values.
    //vec4 vPos = vec4( transformMatrix[gl_InstanceID] * gl_Vertex * vec4(scaleFactor,1.0) + vec4(position[gl_InstanceID],0.0) );

    // TEST 3 // right now position is not being calculated.
    //vec4 vPos = vec4( transformMatrix[gl_InstanceID] * gl_Vertex);
                     
    vec4 vPos = vec4( transformMatrix[gl_InstanceID] * gl_Vertex) + vec4(position[gl_InstanceID],0.0);
    
    //vPos = matrix from openFrameworks
    //gl_ProjectionMatris =  built-in.
    //gl_ModelViewMatrix = built-in
   
    //works
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vPos;
  
    

  
}