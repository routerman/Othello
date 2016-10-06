#pragma once
#include "disk.h"
#include "i2.h"

class Othello{
private:
	Disk disk[8][8];

public:

	void draw_disks(bool turn){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				disk[i][j].draw(turn);
			}
		}
	}

	void put(bool color, I2 r){
		disk[r.x][r.y].place(color);
	}

	void turn(bool color, I2 r){
		disk[r.x][r.y].setColor(color);
	}

	bool isOnboard(I2 r){
		return disk[r.x][r.y].isOnboard();
	}

	bool getColor(I2 r){
		return disk[r.x][r.y].getColor();
	}

	bool isPutable(bool color, I2 r){
		return disk[r.x][r.y].isPutable(color);
	}

	void reverseLine(bool color,I2 r,I2 d){
	    do{
			r+=d;
			turn(color,r);
		}while(getColor(r+d)!=color && r.isOnboard() );
	}

	void reverse(bool color,I2 position){
	    if( checkLine(color,position,I2( 0, 1)) ) reverseLine(color,position,I2( 0, 1));
	    if( checkLine(color,position,I2( 1, 1)) ) reverseLine(color,position,I2( 1, 1));
	    if( checkLine(color,position,I2( 1, 0)) ) reverseLine(color,position,I2( 1, 0));
	    if( checkLine(color,position,I2( 1,-1)) ) reverseLine(color,position,I2( 1,-1));
	    if( checkLine(color,position,I2( 0,-1)) ) reverseLine(color,position,I2( 0,-1));
	    if( checkLine(color,position,I2(-1,-1)) ) reverseLine(color,position,I2(-1,-1));
	    if( checkLine(color,position,I2(-1, 0)) ) reverseLine(color,position,I2(-1, 0));
	    if( checkLine(color,position,I2(-1, 1)) ) reverseLine(color,position,I2(-1, 1));
	}


	/* Is there any square to place? */
	bool isAnyPutable(bool color){
		for(int x=0;x<8;x++){
			for(int y=0;y<8;y++){
				if( isPutable(color,I2(x,y)) )return true;
			}
		}
		return false;
	}

	/* その方向に対してリバースできるか */
	bool checkLine(bool color,I2 r,I2 d){
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
	bool checkPutable(bool color,I2 position){
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

	/* Check all square in board, and set putable value each square. */
	void updateDisk(bool color){
		for(int x=0;x<8;x++){
			for(int y=0;y<8;y++){
				disk[x][y].setPutable(color, checkPutable(color,I2(x,y)) );
			}
		}
	}

	I2 judge(){
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


	/* Construct with coping all disks infomation */
	Othello(){
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
		updateDisk(BLACK);
		updateDisk(WHITE);
	}

	Othello( Disk disk[][8] ){
		for(int m=0;m<8;m++){
			for(int n=0;n<8;n++){
				this->disk[m][n]=disk[m][n];
			}
		}
	}
};

