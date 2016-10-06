/*
 * main.cc
 *
 *  Created on: Oct 4, 2016
 *      Author: routerman
 */

#include "game.h"
Game *game;

void display(void){
	game->display();
}

void mouse_click(int state ,int button, int cx,int cy){
	game->mouse_click(state,button,I2(cx,cy));
}

void mouse_motion(int cx,int cy){
	game->mouse_motion(I2(cx,cy));
}

void key(unsigned char k, int x, int y){
	game->key(k,x,y);
}

void timer(int dt){
	game->timer(dt);
	glutTimerFunc(dt,timer,10);
}

void reshape(GLsizei width, GLsizei height){
	game->reshape(width,height);
}

int main(int argc, char **argv){
	game = new Game;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	game->CreateWindow(0,800,600,0,"Othello");
	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutPassiveMotionFunc(mouse_motion);
	glutMouseFunc(mouse_click);
	glutTimerFunc(0,timer,10);

	glutMainLoop();
	delete game;
	return 0;
}
