/*
 * main.cc
 *
 *  Created on: Oct 4, 2016
 *      Author: routerman
 */

#include "game.h"
Game *game;


#ifdef OOP
//static なメンバ関数しか呼び出せない
int main(int argc, char **argv){
	Game *othelo = new Game();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	Game::CreateWindow(0,800,0,600,"othello");

	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(Game::display);
	glutKeyboardFunc(Game::key);
	glutPassiveMotionFunc(Game::mouse);
	glutMouseFunc(Game::mousebotton);
	glutTimerFunc(0,Game::timer,100);

	glutMainLoop();
	return 0;
}

#else

void display(void){game->display();}
void mousebotton(int state ,int button, int cx,int cy){
	game->mousebotton(state,button,cx,cy);
}
void mouse(int cx,int cy){game->mouse(cx,cy);}
void key(unsigned char k, int x, int y){game->key(k,x,y);}
void timer(int dt){
	game->timer(dt);
	glutTimerFunc(dt,timer,10);
}
void reshape(GLsizei width, GLsizei height){game->reshape(width,height);}


int main(int argc, char **argv){
	game = new Game;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	game->CreateWindow(0,800,600,0,"othello");
	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mousebotton);
	glutTimerFunc(0,timer,10);

	glutMainLoop();
	delete game;
	return 0;
}
#endif
