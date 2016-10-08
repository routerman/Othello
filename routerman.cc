//hppファイルでインクルードするとC2146問題が発生する。
#include "othello.h"
#include "routerman.h"

/*
一手先を読み、角が取られないかチェックする。
取られる場合はtrue 取られない場合はfalse
*/
bool Routerman::corner_flag(Othello tmp, I2 test){
	tmp.put_disk(color,test);

	return tmp.isPutable(!color,I2(0,0)) ||
			tmp.isPutable(!color,I2(0,7)) ||
			tmp.isPutable(!color,I2(7,0)) ||
			tmp.isPutable(!color,I2(7,7)) ;
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


int Routerman::score(Othello tmp, I2 test){
    //double score;
	I2 result;
    tmp.put_disk(color,test);
	//tmp.reverse(color,test);

	//tmp.updateDisk(!color);
	/*
    if( tmp.isAnyPutable(!color) ) {
        bool flag1 = false;
        bool flag2 = false;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if( tmp.isPutable(!color,I2(i,j)) ){
                    flag1 = true;
                    Othello tmp2 = tmp;
                    tmp2.put(!color,I(i,j));
                    tmp2.reverse(!color,I(i,j));

                    tmp2.updateDisk(color);
                    if( tmp2.isAnyPutable(color) ) {
                        for(int k=0;k<8;k++){
                            for(int l=0;l<8;l++){
                                if( tmp2.isPutable(!color,I2(k,l)) ){
                                    flag2 = true;
                                    score(tmp2,I(k,l));
                                }
                            }
                        }
                    }
                }
            }
        }
    }else{

    }
    */

    result = tmp.judge();
    //score = result.x * 100
    if( color == BLACK )return result.x;
    if( color == WHITE )return result.y;
    return 1;
}



Routerman::Routerman(bool color){
	this->color=color;
	int init[8][8]={
		{9,2,8,5,5,8,2,9},
		{2,1,4,7,7,4,1,2},
		{8,4,6,5,5,6,4,8},
		{5,7,5,0,0,5,7,5},
		{5,7,5,0,0,5,7,5},
		{8,4,6,5,5,6,4,8},
		{2,1,4,7,7,4,1,2},
		{9,2,8,5,5,8,2,9}
	};
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			weight[i][j]=init[i][j];
		}
	}
}
