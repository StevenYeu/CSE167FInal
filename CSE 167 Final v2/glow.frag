uniform sampler2D glowTex;

varying vec2 vTexCoord;

uniform float pixelWidth;
uniform float pixelHeight;

void main()
{
    vec2 texel = gl_TexCoord[0].st;
    vec4 pixel = texture2D(glowTex, texel);
    
    float glow = 4.0 * ((pixelWidth + pixelHeight) / 2.0);
    
    vec4 bloom = vec4(0);
    
    int count = 0;
    for(float x = texel.x - glow; x < texel.x + glow; x += pixelWidth)
    {
        for(float y = texel.y - glow; y < texel.y + glow; y += pixelHeight)
        {
            bloom += (texture2D(glowTex, vec2(x, y)) - 0.4) * 30.0;
            count++;
        }
    }
    
    
    float c = float(count);
    float x = clamp(bloom.x/c*30.0,0.0,1.0);
    float y = clamp(bloom.y/c*30.0,0.0,1.0);
    float z = clamp(bloom.z/c*30.0,0.0,1.0);
    float w = clamp(bloom.w/c*30.0,0.0,1.0);
    
    bloom = vec4(x,y,z,w);
    
    gl_FragColor = pixel + bloom*.50;
}