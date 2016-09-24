#version 150
uniform sampler2DRect srcSampler;

uniform vec4 colour = vec4( 0.1, 0.2, 0.4, 1.0 );
out vec4 outputColour;

void main()
{
  outputColour = colour;
}
