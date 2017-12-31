// vshader.glsl
#version 330

uniform float uTime;
uniform float uSize;
uniform int uDiv;
uniform bool uIsShowWaving;

in vec4 vPosition;
in vec4 vColor;

out vec4 color;
out vec4 fragPos;
out float height;

void main()
{
	
	mat4 move = mat4(1.0); // �� ������ y������ �����̵� �ϱ� ���� ���
	
	float h = (uSize - abs(vPosition.x)) * (uSize - abs(vPosition.z)); // �߽ɿ��� �־��� ���� ���� �۾����� ���� ����ġ

	float distance = abs(sqrt((vPosition.x * vPosition.x) + (vPosition.z * vPosition.z)))*20; // �߽�(0,0)���� �Ÿ�

	move[3][1] = sin(8*3.141592 - distance + uTime*6)/4 * h; // �����̵��ؾ��� y�� �� ���[(���� �ֱ� - �Ÿ��� ���� �ֱ� ��ȭ + �ð��� ���� �ֱ� ��ȭ)/(��������)*(���� ����ġ)]

	float xAngle = -45;
	float xRad = xAngle/180.0*3.141592;
	mat4 xRotate = mat4(1.0);
	xRotate[1][1] = cos(xRad);	xRotate[2][1] = -sin(xRad);
	xRotate[1][2] = sin(xRad);	xRotate[2][2] = cos(xRad);

	float angle = -45*uTime;
	float r = angle/180.0*3.141592;
	mat4 m = mat4(1.0);
	m[0][0] = cos(r);	m[2][0] = sin(r);
	m[0][2] = -sin(r);	m[2][2] = cos(r);

	mat4 M;

	// waving�� on�� ���� off�� ���� ó���ϱ� ����
	if(uIsShowWaving) M = move * xRotate * m;
	else M = xRotate * m;

	gl_Position = M*vPosition;

	// fshader�� ���� ���� ���� ����
	if(uIsShowWaving) height = (move * vPosition).y;
	else height = 0;

	color = vColor;
	fragPos = vPosition;
}