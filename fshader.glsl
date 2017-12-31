// fshader.glsl
#version 330

uniform float uTime;
uniform float uSize;
uniform int uDiv;

in float height;
in vec4 fragPos;
in vec4 color;
out vec4 fcolor;

void main()
{
	
	fcolor = color;
	
	vec4 color2 = color;

	// ���̰� ������ ���� ��Ȳ���� ������, ������ ���� �Ķ����� ������ �ϱ� ����
	color2.r = color2.r + height*3;
	color2.b = color2.b - height*3;

	fcolor = color2;

}