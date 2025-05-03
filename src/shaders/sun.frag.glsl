
#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D emission;
uniform vec4 colDiffuse;
uniform vec3 viewPos;

// Output fragment color
out vec4 finalColor;

// NOTE: Add your custom variables here

// Input lighting values

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec4 emissionColor = texture(emission, fragTexCoord);

    //TODO: might be good to put a camera in and fade on dot
    
    float pdot = pow(dot(normalize(fragPosition), normalize(viewPos)),4);
    vec4 tint = colDiffuse * fragColor * (1-pdot);
    vec4 emissionTint = emissionColor * pdot;

    // NOTE: Implement here your fragment shader code

    finalColor = texelColor*(tint+emissionTint);

    // Gamma correction
    finalColor = pow(finalColor, vec4(1.0/2.2));
}
