/*
 * main.cc
 *
 *  Created on: Oct 4, 2016
 *      Author: routerman
 */

#include "othello.h"
Othello *othello;


#ifdef OOP
//static なメンバ関数しか呼び出せない
int main(int argc, char **argv){
	Othello *othelo = new Othello();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	Othello::CreateWindow(0,800,0,600,"othello");

	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(Othello::display);
	glutKeyboardFunc(Othello::key);
	glutPassiveMotionFunc(Othello::mouse);
	glutMouseFunc(Othello::mousebotton);
	glutTimerFunc(0,Othello::timer,100);

	glutMainLoop();
	return 0;
}

#else

void display(void){othello->display();}
void mousebotton(int state ,int button, int cx,int cy){
	othello->mousebotton(state,button,cx,cy);
}
void mouse(int cx,int cy){othello->mouse(cx,cy);}
void key(unsigned char k, int x, int y){othello->key(k,x,y);}
void timer(int dt){
	othello->timer(dt);
	glutTimerFunc(dt,timer,10);
}
void reshape(GLsizei width, GLsizei height){othello->reshape(width,height);}


int main(int argc, char **argv){
	othello = new Othello;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	othello->CreateWindow(0,800,600,0,"othello");
	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mousebotton);
	glutTimerFunc(0,timer,10);

	glutMainLoop();
	delete othello;
	return 0;
}
#endif
