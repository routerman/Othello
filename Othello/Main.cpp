///////////////////////////////////////////////////////////////////
//                                                               //
//         オセロゲーム　　　　　　　　　　　　　　　            //
//                                                               //
///////////////////////////////////////////////////////////////////
/*
 V角ちぇえくの実装
 V角置かれるかセンサ
 Vチェックの統一化
 Vリセットボタン->「deleteボタン」
 Vボタンにもセレクタが必要
 V石を使った勝敗結果
 v思考時間
 
 打つ手をばらばらにする
 画面サイズ
 待った
 石,コンピュータ構造体
 一度だけ表示する部分
 引数に配列ポインタ
 変数の整理
 カーソルでコンピュータのレベルを選ぶ
 打った場所をすべて記憶し、再現する
 オブジェクト指向化
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

#include "Othello.hpp"


#define GLUT_CURSOR_RIGHT_ARROW 0


Othello othello;


//アナログ時計を描く関数
void DrawWatch(int x,int y,float t){
	GLint x1, y1, i;
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0; i<360; i+=20){
		x1=x+80*sin(M_PI*i/180);
		y1=y+80*cos(M_PI*i/180);
		glVertex2d((GLint)x1,(GLint)y1);
	}
	glEnd();
    
	glColor3f(0,0,0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(x,y);
	glVertex2f(x+70*sin(t*3.14/30),y-70*cos(t*3.14/30));
	glEnd();
    
}

//////////////////////////////
/* OpenGL */
//////////////////////////////


void mousebotton(int state ,int button, int cx,int cy){
	othello.mousebotton(state,button,cx,cy);
}

void mouse(int cx,int cy){
	othello.mouse(cx,cy);
}
void key(unsigned char k, int x, int y){
	othello.key(k,x,y);
}

void display(void){
	othello.display();
}

void timer(int dt){
	othello.timer(dt);
	glutTimerFunc(dt,timer,10);

}

int main(void){
	othello.InitGame();
    
	int i=1;
	char *cv[1]={"SD"};
	glutInit(&i, cv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("OCERO");
	glClearColor( 0 , 0.7, 0, 1);	//オセロ盤の色
	gluOrtho2D(0, 800, 600,0);
	glutSetCursor(GLUT_CURSOR_HELP);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mousebotton);
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glutTimerFunc(0,timer,100);
    
	glutMainLoop();
	return 0;
}
