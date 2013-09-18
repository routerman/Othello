#pragma once
#include "GL.hpp"
class Disk{
public:
	char x,y;
	bool onboard;			//Šù‚É’u‚¢‚Ä‚ ‚é‚©‚Ç‚¤‚©
	bool color;			//F
	bool putable[2];
	void place(bool color){
		onboard=true;
		this->color=color;
	}
	void drow(bool turn){
			if( onboard ){
				if( color )glColor3f(1,1,1);
				else glColor3f(0,0,0);
				GL::DrawCircle(90+60*x,90+60*y);
			}
			if( putable[turn] ){
				glColor3f(0,1,0.1);
				GL::DrawSquare(60+60*x,60+60*y);
			}
	}
	bool isOnboard(){return onboard;}
	Disk(){
		onboard=false;
	}
};
