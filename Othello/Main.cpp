///////////////////////////////////////////////////////////////////
//                                                               //
//         �I�Z���Q�[���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@            //
//                                                               //
///////////////////////////////////////////////////////////////////
/*
 V�p���������̎���
 V�p�u����邩�Z���T
 V�`�F�b�N�̓��ꉻ
 V���Z�b�g�{�^��->�udelete�{�^���v
 V�{�^���ɂ��Z���N�^���K�v
 V�΂��g�������s����
 v�v�l����
 
 �ł���΂�΂�ɂ���
 ��ʃT�C�Y
 �҂���
 ��,�R���s���[�^�\����
 ��x�����\�����镔��
 �����ɔz��|�C���^
 �ϐ��̐���
 �J�[�\���ŃR���s���[�^�̃��x����I��
 �ł����ꏊ�����ׂċL�����A�Č�����
 �I�u�W�F�N�g�w����
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

#include "Othello.hpp"


#define GLUT_CURSOR_RIGHT_ARROW 0


Othello othello;


//�A�i���O���v��`���֐�
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
	glClearColor( 0 , 0.7, 0, 1);	//�I�Z���Ղ̐F
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
