//hpp�t�@�C���ŃC���N���[�h�����C2146��肪��������B
#include "Othello.hpp"
#include "Routerman.hpp"

/*
�����ǂ݁A�p������Ȃ����`�F�b�N����B
�����ꍇ��true ����Ȃ��ꍇ��false
*/
bool Routerman::corner_lose(int x,int y,Disk disk[][8]){
	//copy disk
	Othello *test = new Othello(disk);
	test->disk[x][y].onboard=true;//�ꎞ�I�ɒu���Ă݂�B
	test->disk[x][y].color=color; //�����̐�
	test->reverse(color,x,y);	//�Ђ�����Ԃ�
	test->CanPut(!color);		//�G�̒u����ꏊ���`�F�b�N����
	//�߂�l �����ꍇ:true,����Ȃ��ꍇ;false
	bool putable=test->disk[0][0].putable[!color] ||
			     test->disk[0][7].putable[!color] ||
				 test->disk[7][0].putable[!color] ||
				 test->disk[7][7].putable[!color] ;
	delete test;
	return putable;
}

void Routerman::select(I2 &cursor,Disk disk[][8]){
	int max=0;	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( ( disk[i][j].putable[color] ) && ( weight[i][j] > max ) && ( corner_lose(i,j,disk) == false ) ){
				cursor.set(i,j);
				max=weight[i][j];
			}
		}
	}
	if(max==0){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if( ( disk[i][j].putable[color] ) && ( weight[i][j] > max ) ){
					cursor.set(i,j);
					max=weight[i][j];
				}
			}
		}
	}
}