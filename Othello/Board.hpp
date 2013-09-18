#pragma once
#include "GL.hpp"
class Board{
	//disk<map>
public:
	void drow(int player,int stat){
		/* ƒIƒZƒƒ‰ƒCƒ“ */
		glColor3f(0,0,0);
		for(int i=1;i<=9;i++){
			GL::DrawLine(2,60*i,60,60*i,540);//c
			GL::DrawLine(2,60,60*i,540,60*i);//‰¡
		}
		GL::DrawPoint(8,180,180);
		GL::DrawPoint(8,180,420);
		GL::DrawPoint(8,420,180);
		GL::DrawPoint(8,420,420);
		
		GL::DrawString(580,500,"p:POSE");
		GL::DrawString(580,530,"backspace:BACK");
		GL::DrawString(580,560,"m:PLAYMODE");
		GL::DrawString(580,590,"esc:EXIT");
    
		glLineWidth(7);
		glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2i(570,0);
    
		glColor3f(1,1,1);
		glVertex2i(570,600);
		glEnd();


		if(player<=2)GL::DrawString(600,410,"1P YOU");
		else GL::DrawString(600,410,"1P COMPUTER");
		if(player%2)GL::DrawString(600,440,"2P YOU");
		else GL::DrawString(600,440,"2P COMPUTER");
		//if(stat==STAT_POSE)GL::DrawString(600,300,"POSE");
		    
		GL::DrawWatch(700,100,0);
	}
};