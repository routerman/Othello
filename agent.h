#pragma once
#include "machine.h"
#include "game.h"

class Agent : public Machine{

public:
	void select(){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if( this->othello_tmp.isPutable(color,I2(i,j)) ){
					cursor.set(i,j);
				}
			}
		}
	}
	Agent(bool color){this->color=color;}
};
