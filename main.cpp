

#include <vgl.h>
#include "MyPlain.h"

MyPlain plain;

float time=0;
bool isRotate = false;

void myInit()
{
	plain.init(30);
}


void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	plain.draw(time);
	
	glFlush();
	glutSwapBuffers();
}
void myIdle()
{
	if (isRotate) // rotate on/off
		time += 0.016;

	Sleep(16);
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y){

	switch(key){
	case ' ':
		isRotate = !isRotate; // rotate on/off
		break;
	case '1':
		plain.decreaseDiv();
		break;
	case '2':
		plain.increaseDiv();
		break;
	case 'w':
	case 'W':
		plain.controlWaving(); // wave on/off
		break;
	case 'q':
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}

}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutCreateWindow("13011187 Taewoo You HW1");

	glewExperimental = true;
	glewInit();

	myInit();
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();

	return 0;
}