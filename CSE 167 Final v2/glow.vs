

uniform sampler2D glowTex;
uniform float pixelWidth;
uniform float pixelHeight;

attribute vec2 TexCoord;
attribute vec4 Color;

//"out" varyings to our fragment shader
varying vec2 vTexCoord;

vec4 position;
void main(void)
{
    //position = gl_Vertex;
    
    //Transform the vertex into world coordinates
    //position = gl_ModelViewMatrix * position;
    
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    //vTexCoord = TexCoord;
    
    //Set the gl position of this vertex
    //gl_Position = gl_ProjectionMatrix * position;
    gl_Position = ftransform();
}