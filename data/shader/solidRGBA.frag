#version 150

uniform float red;
uniform float green;
uniform float blue;
uniform float alpha;

out vec4 OUT;

void main()
{
  OUT = vec4( red, green, blue, alpha );
}
