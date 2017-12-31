#pragma once

#include <vgl.h>

class MyPlain
{
public:
	MyPlain();
	~MyPlain();

	float size; // ����, ���� ������ ��
	int m_division; // �� ���� ������
	int m_numVertices; // �� ���� ������
	bool isShowWaving; // waving�� ����
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

