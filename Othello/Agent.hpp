#pragma once
#include "Machine.hpp"
#include "Othello.hpp"

class Agent : public Machine{

public:
	void select(){
		//‚±‚±‚ğ‰ü—Ç‚µ‚Ä‚­‚¾‚³‚¢B
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if( disk[i][j].isPutable(color)){
					cursor.set(i,j);
				}
			}
		}
	}
	Agent(bool color){this->color=color;}
};