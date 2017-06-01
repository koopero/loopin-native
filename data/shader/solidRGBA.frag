#version 150

uniform float red = 0.1;
uniform float green = 0.1;
uniform float blue = 0.1;
uniform float alpha = 1.0;

out vec4 outputColour;

void main()
{
  outputColour = vec4( red, green, blue, alpha );
}
