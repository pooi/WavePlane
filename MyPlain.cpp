#define _CRT_SECURE_NO_DEPRECATE
#include "MyPlain.h"
#include<vec.h>
#include<InitShader.h>

struct MyCylinderVertex {
	vec4 pos;
	vec4 color;
};

MyPlain::MyPlain()
{
	size = 0.8;
	m_division = 0;
	m_numVertices = 0;
	isShowWaving = false;
}


MyPlain::~MyPlain()
{
}

void MyPlain::init(int div) {

	m_division = div;
	initVertexArray();

	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(MyCylinderVertex), BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(MyCylinderVertex), BUFFER_OFFSET(sizeof(vec4)));

	GLuint uSize = glGetUniformLocation(program, "uSize");
	glUniform1f(uSize, size);

	GLuint uDiv = glGetUniformLocation(program, "uDiv");
	glUniform1f(uDiv, m_division);

	printf("A Waving Color Plain\n");
	printf("Programming Assignment #1 for Computer Graphics 2\n");
	printf("Department of Digital Contents, Sejong University\n");
	printf("13011187 - Taewoo You\n\n");
	printf("-----------------------------------------------------------\n");
	printf("'1' key: Decreasing the Number of Division\n");
	printf("'2' key: Increasing the Number of Division\n");
	printf("'w' key: Showing/hiding the waving pattern\n");
	printf("Spacebar: Starting/stoping rotating and waving\n\n");
	printf("'Q' key: Exit the program.\n");
	printf("-----------------------------------------------------------\n\n");

	printCurrentStatus();

}

void MyPlain::draw(float time) {

	glBindVertexArray(vao);
	glUseProgram(program);

	GLuint uTime = glGetUniformLocation(program, "uTime");
	glUniform1f(uTime, time);

	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);

}

void MyPlain::increaseDiv() {

	m_division++;
	GLuint uDiv = glGetUniformLocation(program, "uDiv");
	glUniform1f(uDiv, m_division);
	initVertexArray();

	printCurrentStatus();

}

void MyPlain::decreaseDiv() {

	if (m_division > 2) {
		m_division--;
		GLuint uDiv = glGetUniformLocation(program, "uDiv");
		glUniform1f(uDiv, m_division);
		initVertexArray();
	}

	printCurrentStatus();

}

void MyPlain::initVertexArray() {

	//m_numVertices = m_division * 2 * 3 + m_division * 3 * 2; // 사각형 개수 * 삼각형 개수 * 점의 개수 + 뚜껑
	m_numVertices = 6 * m_division * m_division; // division * division(사각형 개수) * 2(삼각형 개수) * 3(점의 개수)

	MyCylinderVertex * vertex = new MyCylinderVertex[m_numVertices];

	float w = size * 2 / m_division; // 나뉜 사각형의 한변의 길이
	int ind = 0;
	for (int i = 0; i < m_division; i++) {
		for (int j = 0; j < m_division; j++) {
			float x = i * w - size; // 0,0을 기준으로 실좌표계로 변환
			float z = j * w - size;

			vec4 color;
			if ((i + j) % 2 == 0) // 체크무늬를 주기 위함
				color = vec4(0.4, 0.4, 0.4, 1);
			else
				color = vec4(0.5, 0.5, 0.5, 1);

			// 1번째 삼각형 생성
			vertex[ind].pos = vec4(x, 0, z, 1);
			vertex[ind].color = color;
			ind++;

			vertex[ind].pos = vec4(x, 0, z+w, 1);
			vertex[ind].color = color;
			ind++;

			vertex[ind].pos = vec4(x+w, 0, z+w, 1);
			vertex[ind].color = color;
			ind++;

			// 2번째 삼각형 생성
			vertex[ind].pos = vec4(x + w, 0, z, 1);
			vertex[ind].color = color;
			ind++;

			vertex[ind].pos = vec4(x, 0, z, 1);
			vertex[ind].color = color;
			ind++;

			vertex[ind].pos = vec4(x+w, 0, z+w, 1);
			vertex[ind].color = color;
			ind++;

		}
	}

	// GPU
	if (bInitialized == false)
		glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	if (bInitialized == false)
		glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyCylinderVertex)*m_numVertices, vertex, GL_STATIC_DRAW);

	bInitialized = true;

	delete[] vertex;

}

void MyPlain::controlWaving()
{
	isShowWaving = !isShowWaving;

	GLuint uIsShowWaving = glGetUniformLocation(program, "uIsShowWaving");
	glUniform1i(uIsShowWaving, isShowWaving);

	glutPostRedisplay();
}

int MyPlain::getDivision()
{
	return m_division;
}

int MyPlain::getNumOfTriangles()
{
	return m_division * m_division * 2;
}

int MyPlain::getNumOfVertices()
{
	return getNumOfTriangles() * 3;
}

void MyPlain::printCurrentStatus()
{
	printf("Division: %d, Num.of Triangles: %d, Num.of Vertices: %d\n", getDivision(), getNumOfTriangles(), getNumOfVertices());
}
