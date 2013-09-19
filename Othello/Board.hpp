#pragma once
#include "GL.hpp"
#include "I2.hpp"

class Board{
	//disk<map>
public:
	void drow(int mode,int stat,int cpu,unsigned time1){
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
		//stat
		if(stat==POSE )GL::DrawString(600,250,"PAUSE");
		else if(stat==READY )GL::DrawString(600,250,"READY");

		string p1("1P "),p2("2P ");
		if( mode==P2P ){
			p1+="HUMAN";
			p2+="HUMAN";
		}else if( mode==P2M){
			p1+="HUMAN";
			if( cpu==AGENT )p2+="AGENT";
			else if( cpu==ROUTERMAN )p2+="ROUTERMAN";
		}else if( mode==M2P){
			p2+="HUMAN";
			if( cpu==AGENT )p1+="AGENT";
			else if( cpu==ROUTERMAN )p1+="ROUTERMAN";
		}else if( mode==M2M ){
			if( cpu==A2R ){
				p1+="AGENT";
				p2+="ROUTERMAN";
			}else if( cpu==R2A ){
				p1+="ROUTERMAN";
				p2+="AGENT";
			}
		}	
		glColor3f(0,0,0);
		GL::DrawString(580,300,p1);
		glColor3f(1,1,1);
		GL::DrawString(580,330,p2);

		glColor3f(0,0,0);
		//キーマニュアル
		GL::DrawString(580,430,"Pause:-p");
		GL::DrawString(580,460,"Undo:-u");
		GL::DrawString(580,490,"Gamemode:-m");
		GL::DrawString(580,520,"selectCPU:-c");
		GL::DrawString(580,550,"Exit:-Esc");
	}
};