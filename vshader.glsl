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
	
	mat4 move = mat4(1.0); // 각 점마다 y축으로 평행이동 하기 위한 행렬
	
	float h = (uSize - abs(vPosition.x)) * (uSize - abs(vPosition.z)); // 중심에서 멀어질 수록 값이 작아지는 높이 가중치

	float distance = abs(sqrt((vPosition.x * vPosition.x) + (vPosition.z * vPosition.z)))*20; // 중심(0,0)과의 거리

	move[3][1] = sin(8*3.141592 - distance + uTime*6)/4 * h; // 평행이동해야할 y축 값 계산[(기준 주기 - 거리에 따른 주기 변화 + 시간에 따른 주기 변화)/(진폭조정)*(높이 가중치)]

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

	// waving이 on일 때와 off일 때를 처리하기 위함
	if(uIsShowWaving) M = move * xRotate * m;
	else M = xRotate * m;

	gl_Position = M*vPosition;

	// fshader를 위해 높이 값을 전달
	if(uIsShowWaving) height = (move * vPosition).y;
	else height = 0;

	color = vColor;
	fragPos = vPosition;
}