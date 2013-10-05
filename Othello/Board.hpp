#pragma once
#include "GL.hpp"
#include "I2.hpp"
#include "Button.hpp"
//#include "Othello.hpp"

//extern Othello *othello;

class Board{
	
	//disk<map>
public:
	Button reset,undo,play;
	Button player[2];

	void button_proc(Stat stat,I2 cursor){
		if( play.isPushed(cursor) ){
			if( stat == READY )stat=PLAY;
			else if( stat == PLAY )stat=PAUSE;
			else if( stat == PAUSE )stat=PLAY;
			play.selectLabel(stat);
			if( stat == READY )reset.setActive(true);
			else reset.setActive(false);
		}
	}

	void drow(unsigned time1){
		/* オセロライン */
		glColor3f(0,0,0);
		for(int i=1;i<=9;i++){
			GL::DrawLine(2,60*i,60,60*i,540);//縦
			GL::DrawLine(2,60,60*i,540,60*i);//横
		}
		GL::DrawPoint(8,180,180);
		GL::DrawPoint(8,180,420);
		GL::DrawPoint(8,420,180);
		GL::DrawPoint(8,420,420);
		/* ガジェット */
		//Line
		glLineWidth(7);
		glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2i(570,0);  
		glColor3f(1,1,1);
		glVertex2i(570,600);
		glEnd();
		//時計
		GL::DrawWatch(700,100,time1/60);  

	}
};