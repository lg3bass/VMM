#version 120
#extension GL_EXT_gpu_shader4 : require 




uniform int playInstance;

uniform mat4 transformMatrix[6];
uniform mat4 rotationMatrix2[6];
uniform vec3 position[6];

//send these to the fragment shader.
varying vec3 vertex_light_position;
varying vec3 vertex_normal;

varying vec2 instanceNum;


 
void main(){

    
  // Calculate the normal value for this vertex, in world coordinates 
  // (multiply by gl_NormalMatrix and transformation matrix)
  vertex_normal = normalize( gl_NormalMatrix * gl_Normal);
    v = vec3(gl_ModelViewMatrix * gl_Vertex);
  // Calculate the light position for this vertex
  //vertex_light_position = normalize( gl_LightSource[0].position.xyz );
	
  // Set the front color to the color passed through with glColor
  //gl_FrontColor = gl_Color;
  //gl_BackColor = gl_Color;
    
  // Multiply the shape coordinates by the transformation matrix by the scale matrix.
  // Offset by the position -- Original Code
  //vec4 vPos = vec4( ((position[gl_InstanceID], 0 ) + ( transformMatrix[gl_InstanceID] *  gl_Vertex))  * vec4(scaleFactor,1.0) );
  
    // THIS IS IT (transMatrix * verts * scale * position)
    // If I wanted to add values.
    //vec4 vPos = vec4( transformMatrix[gl_InstanceID] * gl_Vertex * vec4(scaleFactor,1.0) + vec4(position[gl_InstanceID],0.0) );

    // TEST 3 // right now position is not being calculated.
    //vec4 vPos = vec4( transformMatrix[gl_InstanceID] * gl_Vertex);
    
    //THIS IS MY FINAL
    //vec4 vPos = vec4( transformMatrix[gl_InstanceID] * gl_Vertex) + vec4(position[gl_InstanceID],0.0);
    
    //DEFINITIONS
    //vPos = matrix from openFrameworks
    //gl_ProjectionMatris =  built-in.
    //gl_ModelViewMatrix = built-in
   
    //works -- THIS IS MY FINAL
    //gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vPos;
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix;
    

  
}