#include "Othello.hpp"
#include "Agent.hpp"


void Agent::select(Disk disk[][8]){
	//ここを改良してください。
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( disk[i][j].isPutable(color)){
				cursor.set(i,j);
			}
		}
	}
}