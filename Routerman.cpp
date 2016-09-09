//hpp�t�@�C���ŃC���N���[�h�����C2146��肪��������B
#include "Othello.hpp"
#include "Routerman.hpp"

/*
�����ǂ݁A�p������Ȃ����`�F�b�N����B
�����ꍇ��true ����Ȃ��ꍇ��false
*/
bool Routerman::corner_lose(int x,int y,Disk disk[][8]){
	//copy disk
	I2 temp(x,y);
	Othello *test = new Othello(disk);
	test->disk[x][y].setOnboard(true);//�ꎞ�I�ɒu���Ă݂�B
	test->disk[x][y].setColor(color); //�����̐�
	test->reverse(color,temp);	//�Ђ�����Ԃ�
	test->ScanPutable(!color);		//�G�̒u����ꏊ���`�F�b�N����
	//�߂�l �����ꍇ:true,����Ȃ��ꍇ;false
	bool putable=test->disk[0][0].isPutable(!color) ||
			     test->disk[0][7].isPutable(!color) ||
				 test->disk[7][0].isPutable(!color) ||
				 test->disk[7][7].isPutable(!color) ;
	delete test;
	return putable;
}

void Routerman::select(){
	int max=0;	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( ( disk[i][j].isPutable(color) ) && ( weight[i][j] > max ) && ( corner_lose(i,j,disk) == false ) ){
				cursor.set(i,j);
				max=weight[i][j];
			}
		}
	}
	if(max==0){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if( ( disk[i][j].isPutable(color) ) && ( weight[i][j] > max ) ){
					cursor.set(i,j);
					max=weight[i][j];
				}
			}
		}
	}
}