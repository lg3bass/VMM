varying vec3 N;
varying vec3 v;
#define MAX_LIGHTS 3 // can be something else

void main()
{
    vec3 N = normalize(vN);
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 100.0);
    
    for (int i=0;i<MAX_LIGHTS;i++)
    {
        // get each light position
        vec3 L = normalize(gl_LightSource[i].position.xyz - v);
        vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
        vec3 R = normalize(-reflect(L,N));
        
        //Ambient Term, i.e. the color un-tinted by reflected light
        vec4 Iamb = gl_FrontLightProduct[i].ambient;
        //Diffuse Term i.e. the light partially tinted by reflect light
        vec4 Idiff = gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0);
        Idiff = clamp(Idiff, 0.0, 1.0);
        
        // Specular Term, i.e for the light reflected directly back at the camera
        vec4 Ispec = gl_FrontLightProduct[i].specular
        * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
        Ispec = clamp(Ispec, 0.0, 1.0);
        
        finalColor += Iamb + Idiff + Ispec;  
    }

}