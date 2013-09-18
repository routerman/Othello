
#include "Machine.hpp"

/*
bool Machine::corner_lose(bool color, int y,int x){
	bool putable=false;	//戻り値 取られる場合:true,取られない場合;false
	bool buf_isi[8][8];
	bool buf_wb[8][8];
    
	//石があればアウト
	//if(stone[y][x])return true;//要らないんじゃない？
	//石が無くても置けなければアウト。
	//if( (ww[y][x]==0 && color==true) || (bb[y][x]==0 && color==false) )return true;
    
	//石、色の情報配列をコピーする。
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			buf_isi[m][n]=s[m][n].put;
			buf_wb[m][n]=s[m][n].color;
		}
	}
    
	s[y][x].put=true;		//一時的に置いて見る。
	s[y][x].color=color;
	s[0][0].reverse(color,y,x);	//ひっくり返す
	f.CanPut(!color);		//敵の置ける場所をチェックする
    
	//角を調べる。
	if(color){
		putable=s[0][0].Canput_black || s[0][7].Canput_black || s[7][0].Canput_black || s[7][7].Canput_black;	//敵が角を置けるかどうかを調べる
	}else{
		putable=s[0][0].Canput_white || s[0][7].Canput_white || s[7][0].Canput_white || s[7][7].Canput_white;
	}
    
	//コピーした情報を基に元に戻す
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			s[m][n].put = buf_isi[m][n];
			s[m][n].color = buf_wb[m][n];
		}
	}
	f.CanPut(!color);	//チェックしなおす
	return putable;
}
*/

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
/*	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( ( ( data[i][j]*s[i][j].Canput_white > max  && turn==WHITE ) || ( data[i][j]*s[i][j].Canput_black > max && turn==BLACK ) ) && corner_lose(turn,i,j) == false ){
				m=i;
				n=j;
				max=data[i][j];
			}
		}
	}
	*/
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
