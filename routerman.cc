//hppファイルでインクルードするとC2146問題が発生する。
#include "othello.h"
#include "routerman.h"

/*
一手先を読み、角が取られないかチェックする。
取られる場合はtrue 取られない場合はfalse
*/
bool Routerman::corner_flag(Othello tmp, I2 test){
	tmp.put(color,test);
	tmp.reverse(color,test);
	tmp.updateDisk(!color);		//敵の置ける場所をチェックする
	//戻り値 取られる場合:true,取られない場合;false
	bool putable=tmp.isPutable(!color,I2(0,0)) ||
			     tmp.isPutable(!color,I2(0,7)) ||
				 tmp.isPutable(!color,I2(7,0)) ||
				 tmp.isPutable(!color,I2(7,7)) ;
	return putable;
}

void Routerman::select(){
	int max=0;	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( ( othello_tmp.isPutable(color,I2(i,j)) ) && ( weight[i][j] > max ) && ( corner_flag(othello_tmp,I2(i,j)) == false ) ){
				cursor.set(i,j);
				max=weight[i][j];
			}
		}
	}
	if(max==0){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if( ( othello_tmp.isPutable(color,I2(i,j)) ) && ( weight[i][j] > max ) ){
					cursor.set(i,j);
					max=weight[i][j];
				}
			}
		}
	}
}
