#pragma once

#include <vgl.h>

class MyPlain
{
public:
	MyPlain();
	~MyPlain();

	float size; // 가로, 세로 길이의 반
	int m_division; // 몇 개를 나눌지
	int m_numVertices; // 몇 개를 만들지
	bool isShowWaving; // waving을 할지
	bool bInitialized;

	GLuint vao;
	GLuint buffer;
	GLuint program;

	void init(int div);
	void draw(float time);
	void increaseDiv();
	void decreaseDiv();
	void initVertexArray();
	void controlWaving();

	int getDivision();
	int getNumOfTriangles();
	int getNumOfVertices();

	void printCurrentStatus();
};

