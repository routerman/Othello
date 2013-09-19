#include "Othello.hpp"//hpp�t�@�C���ŃC���N���[�h�����C2146��肪��������B
#include "Machine.hpp"

bool Machine::corner_lose(bool color, int x,int y,Disk disk[][8]){
	bool putable=false;	//�߂�l �����ꍇ:true,����Ȃ��ꍇ;false

	Othello *test = new Othello();


	/*
	//�΁A�F�̏��z����R�s�[����B
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			test->disk[m][n].onboard=disk[m][n].onboard;
			test->disk[m][n].color=disk[m][n].color;
		}
	}*/
	test->cpdisk(disk);
	test->disk[x][y].onboard=true;		//�ꎞ�I�ɒu���Č���B
	test->disk[x][y].color=color;	
	test->reverse(color,x,y);	//�Ђ�����Ԃ�
	test->CanPut(!color);		//�G�̒u����ꏊ���`�F�b�N����
    
	//�p�𒲂ׂ�B
	putable=test->disk[0][0].putable[!color] ||
		    test->disk[0][7].putable[!color] ||
			test->disk[7][0].putable[!color] ||
			test->disk[7][7].putable[!color] ;
	delete test;
	return putable;
}



void Machine::select(I2 *c,Disk disk[][8]){
	static int data[8][8]={
		{9,2,8,5,5,8,2,9},
		{2,1,4,7,7,4,1,2},
		{8,4,6,5,5,6,4,8},
		{5,7,5,0,0,5,7,5},
		{5,7,5,0,0,5,7,5},
		{8,4,6,5,5,6,4,8},
		{2,1,4,7,7,4,1,2},
		{9,2,8,5,5,8,2,9}
	};
    
	int max=0;
	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( ( disk[i][j].putable[color] ) && ( data[i][j] > max ) && ( corner_lose(color,i,j,disk) == false ) ){
				c->x=i;
				c->y=j;
				max=data[i][j];
			}
		}
	}
	
	if(max==0){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if( ( disk[i][j].putable[color] ) && ( data[i][j] > max ) ){
					c->x=i;
					c->y=j;
					max=data[i][j];
				}
			}
		}
	}
}