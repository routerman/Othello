#include "othello.h"

/* Check all square in board, and set putable value each square. */
void Othello::updateDisk(){
	for(int x=0;x<8;x++){
		for(int y=0;y<8;y++){
			disk[x][y].setPutable(WHITE, checkPutable(WHITE,I2(x,y)) );
			disk[x][y].setPutable(BLACK, checkPutable(BLACK,I2(x,y)) );
		}
	}
}

void Othello::reverseLine(bool color,I2 r,I2 d){
	do{
		r+=d;
		turn_disk(color,r);
	}while(getColor(r+d)!=color && r.isOnboard() );
}

void Othello::reverse(bool color,I2 position){
	if( checkLine(color,position,I2( 0, 1)) ) reverseLine(color,position,I2( 0, 1));
	if( checkLine(color,position,I2( 1, 1)) ) reverseLine(color,position,I2( 1, 1));
	if( checkLine(color,position,I2( 1, 0)) ) reverseLine(color,position,I2( 1, 0));
	if( checkLine(color,position,I2( 1,-1)) ) reverseLine(color,position,I2( 1,-1));
	if( checkLine(color,position,I2( 0,-1)) ) reverseLine(color,position,I2( 0,-1));
	if( checkLine(color,position,I2(-1,-1)) ) reverseLine(color,position,I2(-1,-1));
	if( checkLine(color,position,I2(-1, 0)) ) reverseLine(color,position,I2(-1, 0));
	if( checkLine(color,position,I2(-1, 1)) ) reverseLine(color,position,I2(-1, 1));
}

void Othello::turn_disk(bool color, I2 r){
	disk[r.x][r.y].setColor(color);
}

/* その方向に対してリバースできるか */
bool Othello::checkLine(bool color,I2 r,I2 d){
	if( d.x==0 && d.y==0 )return false;
	r+=d;
	//while(異色の石が存在 && 盤内)
	while(  getColor(r) != color && isOnboard(r) && r.isOnboard() ){
		r+=d;
		if( getColor(r) == color && isOnboard(r) && r.isOnboard() )return true;
	}
	return false;
}

/* Analyze a square which can be putable. */
bool Othello::checkPutable(bool color,I2 position){
	if( isOnboard(position) )return false;
	if( checkLine(color,position,I2( 0, 1)) ) return true;
	if( checkLine(color,position,I2( 1, 1)) ) return true;
	if( checkLine(color,position,I2( 1, 0)) ) return true;
	if( checkLine(color,position,I2( 1,-1)) ) return true;
	if( checkLine(color,position,I2( 0,-1)) ) return true;
	if( checkLine(color,position,I2(-1,-1)) ) return true;
	if( checkLine(color,position,I2(-1, 0)) ) return true;
	if( checkLine(color,position,I2(-1, 1)) ) return true;
	return false;
}

I2 Othello::judge(){
	I2 count(0,0);
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( isOnboard(I2(i,j)) ){
				if( getColor(I2(i,j)) == BLACK )count.x++;
				if( getColor(I2(i,j)) == WHITE )count.y++;
			}
		}
	}
	return count;
}

/* Is there any square to place? */
bool Othello::isAnyPutable(bool color){
	for(int x=0;x<8;x++){
		for(int y=0;y<8;y++){
			if( isPutable(color,I2(x,y)) )return true;
		}
	}
	return false;
}

void Othello::put_disk(bool color, I2 r){
	disk[r.x][r.y].place(color);
	reverse(color,r);
	updateDisk();
}


void Othello::draw_disks(bool turn){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			disk[i][j].draw(turn);
		}
	}
}


bool Othello::isOnboard(I2 r){
	return disk[r.x][r.y].isOnboard();
}

bool Othello::getColor(I2 r){
	return disk[r.x][r.y].getColor();
}

bool Othello::isPutable(bool color, I2 r){
	return disk[r.x][r.y].isPutable(color);
}

/* Construct with coping all disks infomation */
Othello::Othello(){
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			disk[m][n].init_postion(m,n);
			disk[m][n].setOnboard(false);
			disk[m][n].setColor(BLACK);
		}
	}
	disk[3][3].place(BLACK);
	disk[4][3].place(WHITE);
	disk[3][4].place(WHITE);
	disk[4][4].place(BLACK);
	updateDisk();
}
