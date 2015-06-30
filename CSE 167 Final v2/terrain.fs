#version 120
#extension GL_EXT_gpu_shader4 : enable

varying vec4 position;
varying vec3 normal;
varying vec4 vertex;
uniform float waterLevel;
uniform float yellow;
uniform float green;
uniform float grey;
uniform float white;

void main()
{
    //Declare variables for intermediate calculations
    vec4 finalColor;
    vec3 lightDir;
    float attenuation;
    float distance;

    
    
    
    //Declare and initialize variables for storing lighting results
    vec3 finalLighting = vec3(gl_FrontMaterial.emission);
    vec3 ambientReflection = vec3(0.0,0.0,0.0);
    vec3 diffuseReflection = vec3(0.0,0.0,0.0);
    
    vec3 diffuse = vec3(1,1,1);
    vec3 ambient = vec3(.2,.2,.2);
    
    if (vertex.y < waterLevel) {
        diffuse = vec3(0,0,.4);
        //ambient = vec3(0,0,0.2);
    }
    else if (vertex.y < yellow && vertex.y >= waterLevel) {
        diffuse = vec3(.5,.5,0);
        //ambient = vec3(0.2,0.2,0);
    }
    else if(vertex.y < green && vertex.y >= yellow) {
        diffuse = vec3(0,1,0);
        //ambient = vec3(0.2,0.2,0);
    }
    else if(vertex.y < grey && vertex.y >= green) {
        diffuse = vec3(.5,.5,.5);
        //ambient = vec3(0.2,0.2,0.2);
    }
    else if(vertex.y < white && vertex.y >= grey) {
        diffuse = vec3(1,1,1);
        //ambient = vec3(0.2,0.2,0.2);
    }
    
    //Loop through all 8 lights that the OpenGL fixed function pipeline supports
    for (int i = 0; i < 1; ++i)
    {
        //Calculate the light direction
        lightDir = gl_LightSource[i].position.xyz - position.xyz;
        
        //Add the ambient light factor to the ambient accumulator
        ambientReflection += vec3(ambient) * vec3(gl_LightSource[i].ambient);
        
        //If the light is behind the surface, continue
        if(dot(normal, lightDir) < 0.0)
            continue;
        
        //Set the default attenuation to none (by the multiplicative identity, this is 1.0)
        attenuation = 1.0;
        
        //If the light is not a directional light, then apply the appropriate attenuation
        if (0.0 != gl_LightSource[i].position.w)
        {
            distance = length(lightDir);
            attenuation = 1.0 / (gl_LightSource[i].constantAttenuation
                                 + gl_LightSource[i].linearAttenuation * distance
                                 + gl_LightSource[i].quadraticAttenuation * distance * distance);
        }
        
        //Calculate the diffuse reflectance and add it to the diffuse accumulator
        diffuseReflection += attenuation * vec3(gl_LightSource[i].diffuse) * vec3(diffuse) * max(0.0, dot(normal, normalize(lightDir)));
    }
    
    //Sum all of the lighting together
    finalLighting = finalLighting + ambientReflection + diffuseReflection;
    
    //Return the final lighting
   
    gl_FragColor = vec4(finalLighting, 1.0);
    


}
