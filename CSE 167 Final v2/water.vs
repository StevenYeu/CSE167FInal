

varying vec4 position;
varying vec3 normal;
varying vec4 vertex;
uniform float waterLevel;
uniform float yellow;
uniform float green;
uniform float grey;
uniform float white;

void main(void)
{
    //Transform the normal into world coordinates
    normal = normalize(gl_NormalMatrix * gl_Normal);
    
    position = gl_Vertex;
    vertex = gl_Vertex;
    
    if (position.y < waterLevel) {
        position.y = waterLevel;
        normal = vec3(0.0,1.0,0.0);
    }
    
    //Transform the vertex into world coordinates
    position = gl_ModelViewMatrix * position;
    
    
    
    //Set the gl position of this vertex
    gl_Position = gl_ProjectionMatrix * position;
    
}