#include "Othello.hpp"
#include "Agent.hpp"

/*
Disk::

*/


void Agent::select(){
	//���������ǂ��Ă��������B
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( disk[i][j].isPutable(color)){
				cursor.set(i,j);
			}
		}
	}
}