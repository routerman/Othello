//hppファイルでインクルードするとC2146問題が発生する。
#include "Othello.hpp"
#include "Routerman.hpp"

/*
一手先を読み、角が取られないかチェックする。
取られる場合はtrue 取られない場合はfalse
*/
bool Routerman::corner_lose(int x,int y,Disk disk[][8]){
	//copy disk
	Othello *test = new Othello(disk);
	test->disk[x][y].onboard=true;//一時的に置いてみる。
	test->disk[x][y].color=color; //自分の石
	test->reverse(color,x,y);	//ひっくり返す
	test->CanPut(!color);		//敵の置ける場所をチェックする
	//戻り値 取られる場合:true,取られない場合;false
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