#include "Othello.hpp"
#include "Agent.hpp"


void Agent::select(I2 &cursor,Disk disk[][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( disk[i][j].putable[color]){
				cursor.set(i,j);
			}
		}
	}
}