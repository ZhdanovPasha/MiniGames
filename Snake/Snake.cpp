#include <time.h>
#include <glut.h>
#include <stdlib.h>

// field size
int N = 40, M = 20;
int Scale = 25;
// window size
int w = Scale * N;
int h = Scale * M;

//dir - direction(from 0 to 4)
//num - current snake length
int dir, num = 4;

//snake struct
struct {
	int x;
	int y;
} s[100];

class  Fructs
{
public:
	int x, y;
	void New(){
		x = rand() % N;
		y = rand() % M;
	}
	void drawApple() {
		glColor3f(1.0, 0.0, 0.0);
		glRectf(x*Scale, y*Scale, (x + 1)*Scale, (y + 1)*Scale);
	}
} m[10]; 


// function for drawing cells
void DrawField(){
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);

	for (int i = 0; i < w; i += Scale) {
		glVertex2f(i, 0);
		glVertex2f(i, h);
	}
	for (int i = 0; i < h; i += Scale) {
		glVertex2f(0, i);
		glVertex2f(w, i);
	}
	glEnd();
}

//function for moving snake
void Tick() {

	for (int i = num; i > 0; --i) {
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0) s[0].y+=1;
	if (dir == 1) s[0].x-=1;
	if (dir == 2) s[0].x+=1;
	if (dir == 3) s[0].y-=1;

	for (int i = 0; i < 10; i++) {
		if ((s[0].x == m[i].x) && (s[0].y == m[i].y)) {
			num++;
			m[i].New();
		}
	}

	if (s[0].x > N) dir = 1;
	if (s[0].x < 0) dir = 2;
	if (s[0].y > M) dir = 3;
	if (s[0].y < 0) dir = 0;

	for (int i = 1; i < num; ++i) {
		if (s[0].x == s[i].x && s[0].y == s[i].y) {
			num = i;
		}
	}
}

void DrawSnake() {
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < num; ++i) {
		glRectf(s[i].x*Scale, s[i].y*Scale,
			(s[i].x + 1)*Scale, (s[i].y + 1)*Scale);
	}
}

void myKeyboard(int key, int a, int b) {
	switch (key)
	{
	case 101:
		dir = 0;
		break;
	case 102:
		dir = 2;
		break;
	case 100:
		dir = 1;
		break;
	case 103:
		dir = 3;
		break;
	default:
		break;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	DrawField();
	for (int i = 0; i < 10; i++) {
		m[i].drawApple();
	}
	DrawSnake();
	
	glFlush();
}

void timer(int = 0){
	display();
	Tick();
	glutTimerFunc(100, timer, 0);
}

int main(int argc, char** argv) {

	for (int i = 0; i < 10; i++)
		m[i].New();

	//initial pos for snake
	s[0].x = 10;
	s[0].y = 10;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutCreateWindow("Test");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	

	glutDisplayFunc(display);
	// 50 - delay in ms
	glutTimerFunc(50, timer, 0);
	glutSpecialFunc(myKeyboard);

	glutMainLoop();

	return 0;
}