//hppファイルでインクルードするとC2146問題が発生する。
#include "game.h"
#include "routerman.h"

/*
一手先を読み、角が取られないかチェックする。
取られる場合はtrue 取られない場合はfalse
*/
bool Routerman::corner_lose(int x,int y,Disk disk[][8]){
	//copy disk
	I2 temp(x,y);
	Game *test = new Game(disk);
	test->othello->disk[x][y].setOnboard(true);//一時的に置いてみる。
	test->othello->disk[x][y].setColor(color); //自分の石
	test->reverse(color,temp);	//ひっくり返す
	test->ScanPutable(!color);		//敵の置ける場所をチェックする
	//戻り値 取られる場合:true,取られない場合;false
	bool putable=test->othello->disk[0][0].isPutable(!color) ||
			     test->othello->disk[0][7].isPutable(!color) ||
				 test->othello->disk[7][0].isPutable(!color) ||
				 test->othello->disk[7][7].isPutable(!color) ;
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
